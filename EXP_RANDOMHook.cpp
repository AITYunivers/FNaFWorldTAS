#pragma once
#include "EXP_RANDOMHook.h"
#include "CRunHook.h"
#include "YuniUtil.h"

void EXP_RANDOMHook::evaluate()
{
    RunHeader* runHeader = GetRunHeader();

    // Advance the expression token
    YuniUtil::AdvanceExpToken();

    // Custom handling for specific events
    int eventIndex = YuniUtil::GetEventIndex();

    // Encounter RNG
    if (runHeader->App->nCurrentFrame == 5 && eventIndex == 1134)
    {
        YuniUtil::SetReturnInt(0);
        if (YuniUtil::IsKeyDown('E'))
            YuniUtil::SetReturnInt(1);
    }
    else
    {
        // Read the expression as a uint
        unsigned int max = CRunHook::getExpression()->getInt();

        // Advance the seed
        runHeader->rh3.Graine = runHeader->rh3.Graine * 0x7ab7 + 1;

        // Calculate and return the result
        YuniUtil::SetReturnInt(runHeader->rh3.Graine * (max & 0xffff) >> 0x10);
    }
}