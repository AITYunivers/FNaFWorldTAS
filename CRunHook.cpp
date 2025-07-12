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

    return CRUN_f_GameLoop();
}