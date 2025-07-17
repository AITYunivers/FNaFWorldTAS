#pragma once
#include "CRunAppHook.h"
#include "D3D9Hook.h"

bool CRunAppHook::playApplication(CRunApp* app, int param2)
{
    // Les do sm temp bs
    {
        CRunApp* app = GetCRunApp();
        //app->hdr.Flags = app->hdr.Flags & ~GA_MAXIMISE;
    }

    static bool init = false;
    if (!init)
    {
        init = true;
        void* d3d9Device[119];

        IDirect3D9* pD3D = Direct3DCreate9(D3D_SDK_VERSION);
        if (!pD3D)
            throw;

        D3DPRESENT_PARAMETERS d3dpp = { 0 };
        d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
        d3dpp.hDeviceWindow = GetForegroundWindow();
        d3dpp.Windowed = true;//((GetWindowLong(d3dpp.hDeviceWindow, GWL_STYLE) & WS_POPUP) != 0) ? FALSE : TRUE;;

        IDirect3DDevice9* pDummyDevice = nullptr;
        HRESULT create_device_ret = pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
            d3dpp.hDeviceWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &pDummyDevice);
        if (!pDummyDevice || FAILED(create_device_ret))
        {
            pD3D->Release();
            throw;
        }

        memcpy(d3d9Device, *reinterpret_cast<void***>(pDummyDevice), sizeof(d3d9Device));

        pDummyDevice->Release();
        pD3D->Release();

        D3D9_EndScene = reinterpret_cast<int(__stdcall*)(LPDIRECT3DDEVICE9)>((uintptr_t)d3d9Device[42]);
        registerHook(&(PVOID&)D3D9_EndScene, &D3D9Hook::EndScene);
        
        D3D9_Reset = reinterpret_cast<int(__stdcall*)(LPDIRECT3DDEVICE9,D3DPRESENT_PARAMETERS*)>((uintptr_t)d3d9Device[16]);
        registerHook(&(PVOID&)D3D9_Reset, &D3D9Hook::Reset);

    }
    return CRUNAPP_playApplication(app, param2);
}