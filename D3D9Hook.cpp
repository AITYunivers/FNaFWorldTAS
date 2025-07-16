#pragma once
#include "D3D9Hook.h"

int(__stdcall* D3D9_EndScene)(LPDIRECT3DDEVICE9) = nullptr;
WNDPROC D3D9Hook::oWndProc;

int __stdcall D3D9Hook::EndScene(LPDIRECT3DDEVICE9 pDevice)
{
	static bool init = true;
	if (init)
	{
		init = false;
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		D3DDEVICE_CREATION_PARAMETERS params;
		pDevice->GetCreationParameters(&params);
		HWND window = params.hFocusWindow;
		printf("Hooking WndProc\n");
		oWndProc = (WNDPROC)SetWindowLongPtr(window, GWLP_WNDPROC, (LONG_PTR)WndProc);
		printf("Hooked WndProc\n");

		ImGui_ImplWin32_Init(window);
		ImGui_ImplDX9_Init(pDevice);
	}

	ImGui_ImplDX9_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();
	ImGui::ShowDemoWindow();

	ImGui::EndFrame();
	ImGui::Render();

	ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
	return D3D9_EndScene(pDevice);
}

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT APIENTRY D3D9Hook::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	ImGui::GetIO().MouseDown[0] = ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) != 0);
	ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);
	return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
}