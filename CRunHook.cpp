#pragma once
#include "CRunHook.h"
#include "TAS.h"

int CRunHook::f_GameLoop()
{
    // Create TAS Thread
    if (!TAS::running)
    {
        std::thread t(TAS::Run);
        t.detach();
    }

    RunHeader* runHeader = GetRunHeader();
    if (TAS::oldLoopCount != runHeader->LoopCount)
    {
        if (TAS::moveUp > 0)
            TAS::moveUp--;
        if (TAS::moveDown > 0)
            TAS::moveDown--;
        if (TAS::moveLeft > 0)
            TAS::moveLeft--;
        if (TAS::moveRight > 0)
            TAS::moveRight--;
        if (TAS::waitTimer > 0)
            TAS::waitTimer--;
        TAS::oldLoopCount = runHeader->LoopCount;
    }

    return CRUN_f_GameLoop();
}