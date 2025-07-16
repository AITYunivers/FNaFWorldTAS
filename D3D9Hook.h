#pragma once
#include "HookHelper.h"
#include "MMFGlobals.h"
#include "d3d9.h"
#include "d3dx9.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx9.h"

extern int(__stdcall* D3D9_EndScene)(LPDIRECT3DDEVICE9);

class D3D9Hook
{
public:
	// Static
	static WNDPROC oWndProc;

	// Hooks
	static int __stdcall EndScene(LPDIRECT3DDEVICE9 pDevice);
	static LRESULT APIENTRY WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};