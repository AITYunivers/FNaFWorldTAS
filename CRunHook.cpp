#pragma once
#include "CRunHook.h"
#include "TAS.h"
#include "CEventProgramHook.h"
#include "YuniUtil.h"

int CRunHook::f_GameLoop()
{
    // Create TAS Thread
    if (!TAS::running)
    {
        std::thread t(TAS::Run);
        t.detach();
    }

    TAS::TickQueue();

    return CRUN_f_GameLoop();
}

void CRunHook::calcMouseClientPos()
{
    if (TAS::mousePos != nullptr)
    {
        RunHeader* runHeader = GetRunHeader();
        runHeader->rh2.MouseClient.x = TAS::mousePos->x;
        runHeader->rh2.MouseClient.y = TAS::mousePos->y;
        runHeader->rh2.Mouse.x = runHeader->rh2.MouseClient.x + runHeader->WindowX;
        runHeader->rh2.Mouse.y = runHeader->rh2.MouseClient.y + runHeader->WindowY;
    }
    else
        CRUN_calcMouseClientPos();
}

int CRunHook::prepareFrame()
{
    // Fade Skip
    RunHeader* runHeader = GetRunHeader();
    if (runHeader->Frame->fadeOut != nullptr)
    {
        std::string type((char*)runHeader->Frame->fadeOut, 8);
        if (type == "STDTFADE")
            runHeader->Frame->fadeOut = nullptr;
    }

    return CRUN_prepareFrame();
}