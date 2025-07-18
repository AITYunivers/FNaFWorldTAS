#pragma once
#include "CRunHook.h"
#include "TAS.h"
#include "CEventProgramHook.h"
#include "YuniUtil.h"
#include "EXP_RANDOMHook.h"
#include "Debug.h"
#include "WindowsHook.h"

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

    EXP_RANDOMHook::expIndex = 0;
    EXP_RANDOMHook::expEvent = -1;

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

    // Disable Timer-Based Movements
    runHeader->Frame->hdr.Flags &= ~LTIMEDMVTS;

    // Random Calc
    WindowsHook::totalLoops++;

    return CRUN_prepareFrame();
}

int CRunHook::createFrameObjects(BOOL fade)
{
    int ret = CRUN_createFrameObjects(fade);
    Debug::UpdateObjPointers();
    return ret;
}

void CRunHook::joyTest()
{
    RunHeader* runHeader = GetRunHeader();
    runHeader->TimerDelta = (unsigned int)(1 / 60.0f * 1000);
    runHeader->rh4.mvtTimerCoef = ((double)runHeader->TimerDelta) * ((double)runHeader->Frame->MvtTimerBase) / 1000.0;

    return CRUN_joyTest();
}

int CRunHook::allocRunHeader()
{
    WindowsHook::calledFromAlloc = true;
    return CRUN_allocRunHeader();
}