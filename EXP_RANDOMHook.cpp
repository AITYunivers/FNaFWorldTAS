#pragma once
#include "EXP_RANDOMHook.h"
#include "CRunHook.h"
#include "YuniUtil.h"
#include <iostream>

int EXP_RANDOMHook::expIndex = 0;
int EXP_RANDOMHook::expEvent = 0;

void EXP_RANDOMHook::evaluate()
{
    RunHeader* runHeader = GetRunHeader();

    // Advance the expression token
    YuniUtil::AdvanceExpToken();

    // Read the expression as a uint
    unsigned int max = CRunHook::getExpression()->getInt();

    // Custom handling for specific events
    int eventIndex = YuniUtil::GetEventIndex();

    // Keep track of the expression index manually
    if (expEvent != eventIndex)
        expIndex = 0;
    expEvent = eventIndex;

    expIndex++;

    // Encounter RNG
    if (runHeader->App->nCurrentFrame == 5 && eventIndex == 1134)
    {
        YuniUtil::SetReturnInt(0);
        return;
    }

    // Advance the seed
    runHeader->rh3.Graine = runHeader->rh3.Graine * 0x7ab7 + 1;

    // Calculate and return the result
    YuniUtil::SetReturnInt(runHeader->rh3.Graine * (max & 0xffff) >> 0x10);
}