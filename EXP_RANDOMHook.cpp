#pragma once
#include "EXP_RANDOMHook.h"
#include "CRunHook.h"
#include "YuniUtil.h"
#include <iostream>

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
    else if (runHeader->App->nCurrentFrame == 19 && eventIndex == 2)
    {
        event2* ace = YuniUtil::GetACE(runHeader->EventGroup, 1); // Action 0
        RunObject* obj = CEventProgramHook::get_CurrentObject((unsigned int)ace->evtOiList, (BOOL*)&ace);
        if (obj->rHo.Oi == 956)
            switch (obj->rHo.HFII)
            {
                case 3:
                case 22:
                case 47:
                    YuniUtil::SetReturnInt(0);
                    break;
                default:
                    YuniUtil::SetReturnInt(9);
                    break;
            }
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