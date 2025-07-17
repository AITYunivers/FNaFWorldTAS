#pragma once
#include "HookHelper.h"
#include "MMFGlobals.h"
#include "imgui_impl_win32.h"
#include "imgui_impl_dx9.h"
#include "Debug.h"
#include <d3d9.h>

extern int(__stdcall* D3D9_EndScene)(LPDIRECT3DDEVICE9);
extern int(__stdcall* D3D9_Reset)(LPDIRECT3DDEVICE9,D3DPRESENT_PARAMETERS*);

class D3D9Hook
{
public:
	// Static
	static WNDPROC oWndProc;

	// Hooks
	static int __stdcall EndScene(LPDIRECT3DDEVICE9 pDevice);
	static int __stdcall Reset(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters);
	static LRESULT APIENTRY WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
};