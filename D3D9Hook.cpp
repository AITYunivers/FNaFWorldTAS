#pragma once
#include "D3D9Hook.h"

int(__stdcall* D3D9_EndScene)(LPDIRECT3DDEVICE9) = nullptr;
int(__stdcall* D3D9_Reset)(LPDIRECT3DDEVICE9,D3DPRESENT_PARAMETERS*) = nullptr;
WNDPROC D3D9Hook::oWndProc;

static bool reset = false;
static bool init = false;

void initImgui(LPDIRECT3DDEVICE9 pDevice)
{
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	D3DDEVICE_CREATION_PARAMETERS params;
	pDevice->GetCreationParameters(&params);
	HWND window = params.hFocusWindow;
	printf("Hooking WndProc\n");
	D3D9Hook::oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)D3D9Hook::WndProc);
	printf("Hooked WndProc\n");

	ImGui_ImplWin32_Init(window);
	ImGui_ImplDX9_Init(pDevice);
	init = true;
}

int __stdcall D3D9Hook::Reset(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters)
{
	int val = D3D9_Reset(pDevice, pPresentationParameters);

	if (init)
	{
		D3DDEVICE_CREATION_PARAMETERS params;
		pDevice->GetCreationParameters(&params);
		HWND window = params.hFocusWindow;

		ImGui_ImplDX9_Shutdown();
		ImGui_ImplWin32_Shutdown();
		ImGui::DestroyContext();

		ImGui::CreateContext();

		ImGui_ImplDX9_Init(pDevice);
		ImGui_ImplWin32_Init(window);
		reset = true;
	}

	return val;
}
int __stdcall D3D9Hook::EndScene(LPDIRECT3DDEVICE9 pDevice)
{
	if (init)
	{
		if (reset)
			reset = false;
		else
		{
			ImGui_ImplDX9_NewFrame();
			ImGui_ImplWin32_NewFrame();
			ImGui::NewFrame();
			Debug::Render();
			ImGui::EndFrame();
			ImGui::Render();

			ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
		}
		
	}
	else
		initImgui(pDevice);
	return D3D9_EndScene(pDevice);
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT APIENTRY D3D9Hook::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	ImGui::GetIO().MouseDown[0] = ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0);
	ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}