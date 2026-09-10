#pragma once
#include "CRunHook.h"
#include "TAS.h"

int CRunHook::f_GameLoop()
{
    RunHeader* runHeader = GetRunHeader();

    // Create TAS Thread
    if (!TAS::running)
    {
        std::thread t(TAS::Run);
        t.detach();
    }

    TAS::TickQueue();

    return CRUN_f_GameLoop();
}

int CRunHook::prepareFrame()
{
    // Disable Timer-Based Movements
    RunHeader* runHeader = GetRunHeader();
    runHeader->Frame->hdr.Flags &= ~LTIMEDMVTS;

    return CRUN_prepareFrame();
}

void CRunHook::joyTest()
{
    RunHeader* runHeader = GetRunHeader();
    runHeader->TimerDelta = (unsigned int)(1 / 60.0f * 1000);
    runHeader->rh4.mvtTimerCoef = ((double)runHeader->TimerDelta) * ((double)runHeader->Frame->MvtTimerBase) / 1000.0;

    return CRUN_joyTest();
}