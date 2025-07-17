#include "Drawing.h"
#include "D3D9Hook.h"

BOOL Drawing::bInit = FALSE; // Status of the initialization of ImGui.
bool Drawing::bDisplay = true; // Status of the menu display.
bool Drawing::bSetPos = false; // Status to update ImGui window size / position.
ImVec2 Drawing::vWindowPos = { 0, 0 }; // Last ImGui window position.
ImVec2 Drawing::vWindowSize = { 0, 0 }; // Last ImGui window size.

/**
	@brief : Hook of the EndScene function.
	@param  D3D9Device : Current Direct3D9 Device Object.
	@retval : Result of the original EndScene function.
**/
HRESULT Drawing::hkEndScene(const LPDIRECT3DDEVICE9 D3D9Device)
{
	if (!D3D9Hook::pDevice)
		D3D9Hook::pDevice = D3D9Device;

	if (!bInit)
		InitImGui(D3D9Device);

	if (GetAsyncKeyState(VK_INSERT) & 1)
		bDisplay = !bDisplay;

	if (GetAsyncKeyState(VK_END) & 1)
	{
		D3D9Hook::UnHookDirectX();
		CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)FreeLibrary, D3D9Hook::hDDLModule, 0, nullptr);
		return D3D9_EndScene(D3D9Device);
	}

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	if (bDisplay)
	{
		ImGui::Begin("Menu Window Title", &bDisplay);
		{
			ImGui::SetWindowSize({ 500, 300 }, ImGuiCond_Once);

			if (vWindowPos.x != 0.0f && vWindowPos.y != 0.0f && vWindowSize.x != 0.0f && vWindowSize.y != 0.0f && bSetPos)
			{
				ImGui::SetWindowPos(vWindowPos);
				ImGui::SetWindowSize(vWindowSize);
				bSetPos = false;
			}

			if (bSetPos == false)
			{
				vWindowPos = { ImGui::GetWindowPos().x, ImGui::GetWindowPos().y };
				vWindowSize = { ImGui::GetWindowSize().x, ImGui::GetWindowSize().y };
			}

			ImGui::Text("Draw your menu here.");
		}
		ImGui::End();
	}

	ImGui::EndFrame();
	ImGui::Render();
	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());

	return D3D9_EndScene(D3D9Device);
}

/**
	@brief : function that init ImGui for rendering.
	@param pDevice : Current Direct3D9 Device Object given by the hooked function.
**/
void Drawing::InitImGui(const LPDIRECT3DDEVICE9 pDevice)
{
	IM_ASSERT(ImGui::GetCurrentContext() == nullptr && "ImGui context already exists!");
	printf("InitImGui called.");

	D3DDEVICE_CREATION_PARAMETERS CP;
	pDevice->GetCreationParameters(&CP);
	D3D9Hook::window = CP.hFocusWindow;
	D3D9Hook::HookWindow();

	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.IniFilename = nullptr;
	io.Fonts->AddFontDefault();

	ImGui::StyleColorsDark();

	ImGui_ImplWin32_Init(D3D9Hook::window);
	ImGui_ImplDX9_Init(pDevice);

	ImGui_ImplDX9_CreateDeviceObjects();  // Re-upload texture to GPU

	bInit = TRUE;
}