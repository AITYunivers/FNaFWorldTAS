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
        switch (TAS::stage)
        {
            case TAS::Stage::JJ_UNLOCK:
                YuniUtil::SetReturnInt(1);
                break;
            default:
                YuniUtil::SetReturnInt(0);
                break;
        }
        return;
    }
    // Enemy Type
    else if (runHeader->App->nCurrentFrame == 5 && eventIndex == 940)
    {
        switch (TAS::stage)
        {
            case TAS::Stage::JJ_UNLOCK:
                YuniUtil::SetReturnInt(2); // Gearrat
                return;
        }
        return;
    }
    // Enemy Count
    else if (runHeader->App->nCurrentFrame == 5 && eventIndex == 944)
    {
        switch (TAS::stage)
        {
            case TAS::Stage::JJ_UNLOCK:
                YuniUtil::SetReturnInt(3); // 4 Gearrats
                return;
        }
        return;
    }
    // Encounter Chance
    else if (runHeader->App->nCurrentFrame == 5 && eventIndex == 941)
    {
        switch (TAS::stage)
        {
            case TAS::Stage::JJ_UNLOCK:
                YuniUtil::SetReturnInt(0); // Give encounter
                return;
            default:
                YuniUtil::SetReturnInt(1); // Do not give encounter
                return;
        }
        return;
    }
    // Encounter
    else if (runHeader->App->nCurrentFrame == 5 && eventIndex == 1620)
    {
        // 9 + Random(value("area") + 3) + ((Random(3) / 2) * (Random(3) + 1))
        switch (TAS::stage)
        {
            case TAS::Stage::JJ_UNLOCK:
                switch (expIndex)
                {
                    case 1: // Random(value("area") + 3)
                        YuniUtil::SetReturnInt(1); // JJ
                        break;
                    case 2: // (Random(3) / 2)
                    case 3: // (Random(3) + 1)
                        YuniUtil::SetReturnInt(0);
                        break;
                }
                return;
        }
        return;
    }
    // Wasp Stinger Damage
    else if (runHeader->App->nCurrentFrame == 5 && eventIndex == 485)
    {
        YuniUtil::SetReturnInt(9); // Max Damage
        return;
    }
    // Wasp Attack Chance
    else if (runHeader->App->nCurrentFrame == 5 && eventIndex >= 1735 && eventIndex <= 1737)
    {
        YuniUtil::SetReturnInt(1); // Always Attack
        return;
    }
    // Bash Jam Damage
    else if (runHeader->App->nCurrentFrame == 5 && eventIndex == 473 && expIndex == 1)
    {
        YuniUtil::SetReturnInt(19); // Max Damage
        return;
    }
    // Bash Jam Damage
    else if (runHeader->App->nCurrentFrame == 5 && eventIndex == 563)
    {
        YuniUtil::SetReturnInt(5); // Max Damage
        return;
    }
    // Party Charge
    else if (runHeader->App->nCurrentFrame == 5 && eventIndex == 108)
    {
        switch (TAS::stage)
        {
            case TAS::Stage::JJ_UNLOCK:
                if (expIndex == 2 || expIndex == 3) // Mangle and Toy Chica
                    YuniUtil::SetReturnInt(4); // No Delay
                else
                    YuniUtil::SetReturnInt(0); // Max Delay
                return;
        }
        return;
    }
    // Prize Ball Poppers
    else if (runHeader->App->nCurrentFrame == 5 && eventIndex == 693)
    {
        YuniUtil::SetReturnInt(0); // Poppers
        return;
    }
    // Prize Ball Poppers Damage
    else if (runHeader->App->nCurrentFrame == 5 && eventIndex == 699)
    {
        YuniUtil::SetReturnInt(98); // Max Damage
        return;
    }
    // Deedee's Fishing Hole Fish Speed
    else if (runHeader->App->nCurrentFrame == 19 && eventIndex == 2)
    {
        event2* ace = YuniUtil::GetACE(runHeader->EventGroup, 1); // Action 0
        RunObject* obj = CEventProgramHook::get_CurrentObject((unsigned int)ace->evtOiList, (BOOL*)&ace);
        if (obj->rHo.HFII == 58) // Pearl
            YuniUtil::SetReturnInt(0);
        else
            YuniUtil::SetReturnInt(9);
        return;
    }

    // Advance the seed
    runHeader->rh3.Graine = runHeader->rh3.Graine * 0x7ab7 + 1;

    // Calculate and return the result
    YuniUtil::SetReturnInt(runHeader->rh3.Graine * (max & 0xffff) >> 0x10);
}