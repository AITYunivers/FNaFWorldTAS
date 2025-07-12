#pragma once
#include <Windows.h>
#include <detours.h>
#include <string.h>
#include "CRunHook.h"
#include "YuniUtil.h"

#include <thread>
#include <chrono>

void CRunHook::random()
{
    RunHeader* runHeader = *GlobalRunHeaderPtr;

    // Advance the expression token
    YuniUtil::AdvanceExpToken();

    // Custom handling for specific events
    int eventIndex = YuniUtil::GetEventIndex();

    // Encounter RNG
    if (eventIndex == 1134)
    {
        YuniUtil::SetReturnInt(0);
        if (YuniUtil::IsKeyDown('E'))
            YuniUtil::SetReturnInt(1);
    }
    else
    {
        // Read the expression as a uint
        unsigned int max = getExpression()->getInt();

        // Advance the seed
        runHeader->rh3.Graine = runHeader->rh3.Graine * 0x7ab7 + 1;

        // Calculate and return the result
        YuniUtil::SetReturnInt(runHeader->rh3.Graine * (max & 0xffff) >> 0x10);
    }
}