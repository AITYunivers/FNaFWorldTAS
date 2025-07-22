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
            case TAS::Stage::FREDDY_LV_4:
            case TAS::Stage::BB_UNLOCK:
            case TAS::Stage::PHANTOM_FREDDY_UNLOCK:
            case TAS::Stage::PHANTOM_CHICA_UNLOCK:
            case TAS::Stage::PHANTOM_BB_UNLOCK:
            case TAS::Stage::PHANTOM_FOXY_UNLOCK:
            case TAS::Stage::PHANTOM_MANGLE_UNLOCK:
            case TAS::Stage::WITHERED_BONNIE_UNLOCK:
            case TAS::Stage::JACK_O_BONNIE_UNLOCK:
            case TAS::Stage::JACK_O_CHICA_UNLOCK:
            case TAS::Stage::NIGHTMARE_BB_UNLOCK:
            case TAS::Stage::NIGHTMARIONNE_UNLOCK:
            case TAS::Stage::COFFEE_UNLOCK:
            case TAS::Stage::PURPLE_GUY_UNLOCK:
            case TAS::Stage::ENDO_01_UNLOCK:
            case TAS::Stage::ENDO_02_UNLOCK:
            case TAS::Stage::PLUSHTRAP_UNLOCK:
            case TAS::Stage::ENDOPLUSH_UNLOCK:
            case TAS::Stage::SPRINGTRAP_UNLOCK:
            case TAS::Stage::RXQ_UNLOCK:
            case TAS::Stage::CRYING_CHILD_UNLOCK:
            case TAS::Stage::FUNTIME_FOXY_UNLOCK:
            case TAS::Stage::NIGHTMARE_FREDBEAR_UNLOCK:
            case TAS::Stage::NIGHTMARE_UNLOCK:
            case TAS::Stage::FREDBEAR_UNLOCK:
            case TAS::Stage::SPRING_BONNIE_UNLOCK:
            case TAS::Stage::WITHERED_CHICA_UNLOCK:
            case TAS::Stage::WITHERED_FREDDY_UNLOCK:
            case TAS::Stage::WITHERED_FOXY_UNLOCK:
            case TAS::Stage::NIGHTMARE_FREDDY_UNLOCK:
            case TAS::Stage::NIGHTMARE_BONNIE_UNLOCK:
            case TAS::Stage::NIGHTMARE_CHICA_UNLOCK:
            case TAS::Stage::NIGHTMARE_FOXY_UNLOCK:
            case TAS::Stage::SHADOW_FREDDY_UNLOCK:
            case TAS::Stage::MARIONETTE_UNLOCK:
            case TAS::Stage::PHANTOM_MARIONETTE_UNLOCK:
            case TAS::Stage::GOLDEN_FREDDY_UNLOCK:
            case TAS::Stage::PAPERPALS_UNLOCK:
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
            case TAS::Stage::FREDDY_LV_4:
                YuniUtil::SetReturnInt(2); // Gearrat
                return;
            default:
                YuniUtil::SetReturnInt(0); // Fastest EXP
                return;
        }
    }
    // Enemy Count
    else if (runHeader->App->nCurrentFrame == 5 && eventIndex == 944)
    {
        switch (TAS::stage)
        {
            case TAS::Stage::FREDDY_LV_4:
                YuniUtil::SetReturnInt(3); // 4 Gearrats
                return;
        }
    }
    // Encounter Chance
    else if (runHeader->App->nCurrentFrame == 5 && eventIndex == 941)
    {
        switch (TAS::stage)
        {
            case TAS::Stage::FREDDY_LV_4:
            case TAS::Stage::BB_UNLOCK:
            case TAS::Stage::PHANTOM_FREDDY_UNLOCK:
            case TAS::Stage::PHANTOM_CHICA_UNLOCK:
            case TAS::Stage::PHANTOM_BB_UNLOCK:
            case TAS::Stage::PHANTOM_FOXY_UNLOCK:
            case TAS::Stage::PHANTOM_MANGLE_UNLOCK:
            case TAS::Stage::WITHERED_BONNIE_UNLOCK:
            case TAS::Stage::JACK_O_BONNIE_UNLOCK:
            case TAS::Stage::JACK_O_CHICA_UNLOCK:
            case TAS::Stage::NIGHTMARE_BB_UNLOCK:
            case TAS::Stage::NIGHTMARIONNE_UNLOCK:
            case TAS::Stage::COFFEE_UNLOCK:
            case TAS::Stage::PURPLE_GUY_UNLOCK:
            case TAS::Stage::ENDO_01_UNLOCK:
            case TAS::Stage::ENDO_02_UNLOCK:
            case TAS::Stage::PLUSHTRAP_UNLOCK:
            case TAS::Stage::ENDOPLUSH_UNLOCK:
            case TAS::Stage::SPRINGTRAP_UNLOCK:
            case TAS::Stage::RXQ_UNLOCK:
            case TAS::Stage::CRYING_CHILD_UNLOCK:
            case TAS::Stage::FUNTIME_FOXY_UNLOCK:
            case TAS::Stage::NIGHTMARE_FREDBEAR_UNLOCK:
            case TAS::Stage::NIGHTMARE_UNLOCK:
            case TAS::Stage::FREDBEAR_UNLOCK:
            case TAS::Stage::SPRING_BONNIE_UNLOCK:
            case TAS::Stage::WITHERED_CHICA_UNLOCK:
            case TAS::Stage::WITHERED_FREDDY_UNLOCK:
            case TAS::Stage::WITHERED_FOXY_UNLOCK:
            case TAS::Stage::NIGHTMARE_FREDDY_UNLOCK:
            case TAS::Stage::NIGHTMARE_BONNIE_UNLOCK:
            case TAS::Stage::NIGHTMARE_CHICA_UNLOCK:
            case TAS::Stage::NIGHTMARE_FOXY_UNLOCK:
            case TAS::Stage::SHADOW_FREDDY_UNLOCK:
            case TAS::Stage::MARIONETTE_UNLOCK:
            case TAS::Stage::PHANTOM_MARIONETTE_UNLOCK:
            case TAS::Stage::GOLDEN_FREDDY_UNLOCK:
            case TAS::Stage::PAPERPALS_UNLOCK:
                YuniUtil::SetReturnInt(0); // Give encounter
                return;
            default:
                YuniUtil::SetReturnInt(1); // Do not give encounter
                return;
        }
    }
    // Encounter
    else if (runHeader->App->nCurrentFrame == 5 && eventIndex == 1620)
    {
        // 9 + Random(value("area") + 3) + ((Random(3) / 2) * (Random(3) + 1))
        switch (TAS::stage)
        {
            case TAS::Stage::FREDDY_LV_4:
                if (expIndex == 1)
                {
                    YuniUtil::SetReturnInt(1); // JJ
                    return;
                }
                break;
            case TAS::Stage::BB_UNLOCK:
                YuniUtil::SetReturnInt(0); // BB
                return;
            case TAS::Stage::PHANTOM_FREDDY_UNLOCK:
                if (expIndex == 1)
                {
                    YuniUtil::SetReturnInt(2); // Phantom Freddy
                    return;
                }
                break;
            case TAS::Stage::PHANTOM_CHICA_UNLOCK:
                switch (expIndex)
                {
                    case 1:
                        YuniUtil::SetReturnInt(2); // Area Max
                        break;
                    case 2:
                        YuniUtil::SetReturnInt(2); // +1 (Phantom Chica)
                        break;
                    case 3:
                        YuniUtil::SetReturnInt(0); // +0
                        break;
                }
                return;
            case TAS::Stage::PHANTOM_BB_UNLOCK:
                switch (expIndex)
                {
                    case 1:
                        YuniUtil::SetReturnInt(2); // Area Max
                        break;
                    case 2:
                        YuniUtil::SetReturnInt(2); // +1
                        break;
                    case 3:
                        YuniUtil::SetReturnInt(1); // +1 (Phantom BB)
                        break;
                }
                return;
            case TAS::Stage::PHANTOM_FOXY_UNLOCK:
                switch (expIndex)
                {
                    case 1:
                        YuniUtil::SetReturnInt(2); // Area Max
                        break;
                    case 2:
                        YuniUtil::SetReturnInt(2); // +1
                        break;
                    case 3:
                        YuniUtil::SetReturnInt(2); // +2 (Phantom Foxy)
                        break;
                }
                return;
            case TAS::Stage::PHANTOM_MANGLE_UNLOCK:
                switch (expIndex)
                {
                    case 1:
                        YuniUtil::SetReturnInt(4); // Area Max
                        break;
                    case 2:
                        YuniUtil::SetReturnInt(2); // +1
                        break;
                    case 3:
                        YuniUtil::SetReturnInt(1); // +1 (Phantom Mangle)
                        break;
                }
                return;
            case TAS::Stage::WITHERED_BONNIE_UNLOCK:
                switch (expIndex)
                {
                    case 1:
                        YuniUtil::SetReturnInt(4); // Area Max
                        break;
                    case 2:
                        YuniUtil::SetReturnInt(2); // +1
                        break;
                    case 3:
                        YuniUtil::SetReturnInt(2); // +2 (Withered Bonnie)
                        break;
                }
                return;
            case TAS::Stage::JACK_O_BONNIE_UNLOCK:
                if (expIndex == 1)
                {
                    YuniUtil::SetReturnInt(32); // Jack-O-Bonnie
                    return;
                }
                break;
            case TAS::Stage::JACK_O_CHICA_UNLOCK:
                if (expIndex == 1)
                {
                    YuniUtil::SetReturnInt(33); // Jack-O-Chica
                    return;
                }
                break;
            case TAS::Stage::NIGHTMARE_BB_UNLOCK:
                if (expIndex == 1)
                {
                    YuniUtil::SetReturnInt(36); // Nightmare BB
                    return;
                }
                break;
            case TAS::Stage::NIGHTMARIONNE_UNLOCK:
                if (expIndex == 1)
                {
                    YuniUtil::SetReturnInt(37); // Nightmarionne
                    return;
                }
                break;
            case TAS::Stage::COFFEE_UNLOCK:
                if (expIndex == 1)
                {
                    YuniUtil::SetReturnInt(38); // Coffee
                    return;
                }
                break;
            case TAS::Stage::PURPLE_GUY_UNLOCK:
                if (expIndex == 1)
                {
                    YuniUtil::SetReturnInt(39); // Purple Guy
                    return;
                }
                break;
            case TAS::Stage::ENDO_01_UNLOCK:
                if (expIndex == 1)
                {
                    YuniUtil::SetReturnInt(20); // Endo-01
                    return;
                }
                break;
            case TAS::Stage::ENDO_02_UNLOCK:
                if (expIndex == 1)
                {
                    YuniUtil::SetReturnInt(21); // Endo-02
                    return;
                }
                break;
            case TAS::Stage::PLUSHTRAP_UNLOCK:
                if (expIndex == 1)
                {
                    YuniUtil::SetReturnInt(22); // Plushtrap
                    return;
                }
                break;
            case TAS::Stage::ENDOPLUSH_UNLOCK:
                if (expIndex == 1)
                {
                    YuniUtil::SetReturnInt(23); // Endoplush
                    return;
                }
                break;
            case TAS::Stage::SPRINGTRAP_UNLOCK:
                if (expIndex == 1)
                {
                    YuniUtil::SetReturnInt(24); // Springtrap
                    return;
                }
                break;
            case TAS::Stage::RXQ_UNLOCK:
                if (expIndex == 1)
                {
                    YuniUtil::SetReturnInt(25); // RXQ
                    return;
                }
                break;
            case TAS::Stage::CRYING_CHILD_UNLOCK:
                if (expIndex == 1)
                {
                    YuniUtil::SetReturnInt(26); // Crying Child
                    return;
                }
                break;
            case TAS::Stage::FUNTIME_FOXY_UNLOCK:
                if (expIndex == 1)
                {
                    YuniUtil::SetReturnInt(27); // Funtime Foxy
                    return;
                }
                break;
            case TAS::Stage::NIGHTMARE_FREDBEAR_UNLOCK:
                if (expIndex == 1)
                {
                    YuniUtil::SetReturnInt(28); // Nightmare Fredbear
                    return;
                }
                break;
            case TAS::Stage::NIGHTMARE_UNLOCK:
                switch (expIndex)
                {
                    case 1:
                        YuniUtil::SetReturnInt(28); // Area Max
                        break;
                    case 2:
                        YuniUtil::SetReturnInt(2); // +1 (Nightmare)
                        break;
                    case 3:
                        YuniUtil::SetReturnInt(0); // +0
                        break;
                }
                return;
            case TAS::Stage::FREDBEAR_UNLOCK:
                switch (expIndex)
                {
                    case 1:
                        YuniUtil::SetReturnInt(28); // Area Max
                        break;
                    case 2:
                        YuniUtil::SetReturnInt(2); // +1
                        break;
                    case 3:
                        YuniUtil::SetReturnInt(1); // +1 (Fredbear)
                        break;
                }
                return;
            case TAS::Stage::SPRING_BONNIE_UNLOCK:
                switch (expIndex)
                {
                    case 1:
                        YuniUtil::SetReturnInt(28); // Area Max
                        break;
                    case 2:
                        YuniUtil::SetReturnInt(2); // +1
                        break;
                    case 3:
                        YuniUtil::SetReturnInt(2); // +2 (Spring Bonnie)
                        break;
                }
                return;
            case TAS::Stage::WITHERED_CHICA_UNLOCK:
                switch (expIndex)
                {
                    case 1:
                        YuniUtil::SetReturnInt(7); // Area Max
                        break;
                    case 2:
                        YuniUtil::SetReturnInt(2); // +1 (Withered Chica)
                        break;
                    case 3:
                        YuniUtil::SetReturnInt(0); // +0
                        break;
                }
                return;
            case TAS::Stage::WITHERED_FREDDY_UNLOCK:
                switch (expIndex)
                {
                    case 1:
                        YuniUtil::SetReturnInt(7); // Area Max
                        break;
                    case 2:
                        YuniUtil::SetReturnInt(2); // +1
                        break;
                    case 3:
                        YuniUtil::SetReturnInt(1); // +1 (Withered Freddy)
                        break;
                }
                return;
            case TAS::Stage::WITHERED_FOXY_UNLOCK:
                switch (expIndex)
                {
                    case 1:
                        YuniUtil::SetReturnInt(7); // Area Max
                        break;
                    case 2:
                        YuniUtil::SetReturnInt(2); // +1
                        break;
                    case 3:
                        YuniUtil::SetReturnInt(2); // +2 (Withered Foxy)
                        break;
                }
                return;
            case TAS::Stage::NIGHTMARE_FREDDY_UNLOCK:
                if (expIndex == 1)
                {
                    YuniUtil::SetReturnInt(16); // Nightmare Freddy
                    return;
                }
                break;
            case TAS::Stage::NIGHTMARE_BONNIE_UNLOCK:
                switch (expIndex)
                {
                    case 1:
                        YuniUtil::SetReturnInt(16); // Area Max
                        break;
                    case 2:
                        YuniUtil::SetReturnInt(2); // +1 (Nightmare Bonnie)
                        break;
                    case 3:
                        YuniUtil::SetReturnInt(0); // +0
                        break;
                }
                return;
            case TAS::Stage::NIGHTMARE_CHICA_UNLOCK:
                switch (expIndex)
                {
                    case 1:
                        YuniUtil::SetReturnInt(16); // Area Max
                        break;
                    case 2:
                        YuniUtil::SetReturnInt(2); // +1
                        break;
                    case 3:
                        YuniUtil::SetReturnInt(1); // +1 (Nightmare Chica)
                        break;
                }
                return;
            case TAS::Stage::NIGHTMARE_FOXY_UNLOCK:
                switch (expIndex)
                {
                    case 1:
                        YuniUtil::SetReturnInt(16); // Area Max
                        break;
                    case 2:
                        YuniUtil::SetReturnInt(2); // +1
                        break;
                    case 3:
                        YuniUtil::SetReturnInt(2); // +2 (Nightmare Foxy)
                        break;
                }
                return;
            case TAS::Stage::SHADOW_FREDDY_UNLOCK:
                if (expIndex == 1)
                {
                    YuniUtil::SetReturnInt(11); // Shadow Freddy
                    return;
                }
                break;
            case TAS::Stage::MARIONETTE_UNLOCK:
                if (expIndex == 1)
                {
                    YuniUtil::SetReturnInt(12); // Marionette
                    return;
                }
                break;
            case TAS::Stage::PHANTOM_MARIONETTE_UNLOCK:
                if (expIndex == 1)
                {
                    YuniUtil::SetReturnInt(13); // Phantom Marionette
                    return;
                }
                break;
            case TAS::Stage::GOLDEN_FREDDY_UNLOCK:
                if (expIndex == 1)
                {
                    YuniUtil::SetReturnInt(14); // Golden Freddy
                    return;
                }
                break;
            case TAS::Stage::PAPERPALS_UNLOCK:
                if (expIndex == 1)
                {
                    YuniUtil::SetReturnInt(15); // Paperpals
                    return;
                }
                break;
        }
        YuniUtil::SetReturnInt(0);
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
            case TAS::Stage::FREDDY_LV_4:
            case TAS::Stage::JJ_UNLOCK:
            case TAS::Stage::BB_UNLOCK:
            case TAS::Stage::PHANTOM_FREDDY_UNLOCK:
            case TAS::Stage::PHANTOM_CHICA_UNLOCK:
            case TAS::Stage::PHANTOM_BB_UNLOCK:
            case TAS::Stage::PHANTOM_FOXY_UNLOCK:
            case TAS::Stage::PHANTOM_MANGLE_UNLOCK:
            case TAS::Stage::WITHERED_BONNIE_UNLOCK:
            case TAS::Stage::JACK_O_BONNIE_UNLOCK:
            case TAS::Stage::JACK_O_CHICA_UNLOCK:
            case TAS::Stage::NIGHTMARE_BB_UNLOCK:
            case TAS::Stage::NIGHTMARIONNE_UNLOCK:
            case TAS::Stage::COFFEE_UNLOCK:
            case TAS::Stage::PURPLE_GUY_UNLOCK:
            case TAS::Stage::GOLD_ENDO_GRIND:
            case TAS::Stage::ENDO_01_UNLOCK:
            case TAS::Stage::ENDO_02_UNLOCK:
            case TAS::Stage::PLUSHTRAP_UNLOCK:
            case TAS::Stage::ENDOPLUSH_UNLOCK:
            case TAS::Stage::SPRINGTRAP_UNLOCK:
            case TAS::Stage::RXQ_UNLOCK:
            case TAS::Stage::CRYING_CHILD_UNLOCK:
            case TAS::Stage::FUNTIME_FOXY_UNLOCK:
            case TAS::Stage::NIGHTMARE_FREDBEAR_UNLOCK:
            case TAS::Stage::NIGHTMARE_UNLOCK:
            case TAS::Stage::FREDBEAR_UNLOCK:
            case TAS::Stage::SPRING_BONNIE_UNLOCK:
            case TAS::Stage::AUTO_CHIPPER:
            case TAS::Stage::WITHERED_CHICA_UNLOCK:
            case TAS::Stage::WITHERED_FREDDY_UNLOCK:
            case TAS::Stage::WITHERED_FOXY_UNLOCK:
                if (expIndex == 2) // Mangle or JJ
                    YuniUtil::SetReturnInt(4); // No Delay
                else
                    YuniUtil::SetReturnInt(0); // Max Delay
                return;
            case TAS::Stage::MAGICAL_PAINBOW:
                YuniUtil::SetReturnInt(4); // No Delay
                return;
        }
    }
    // Party Charge
    else if (runHeader->App->nCurrentFrame == 5 && eventIndex == 1603)
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
    // Run Chance
    else if (runHeader->App->nCurrentFrame == 5 && (eventIndex == 1605 || eventIndex == 1606))
    {
        switch (TAS::stage)
        {
            case TAS::Stage::BB_UNLOCK:
            case TAS::Stage::PHANTOM_FREDDY_UNLOCK:
            case TAS::Stage::PHANTOM_CHICA_UNLOCK:
            case TAS::Stage::PHANTOM_BB_UNLOCK:
            case TAS::Stage::PHANTOM_FOXY_UNLOCK:
            case TAS::Stage::PHANTOM_MANGLE_UNLOCK:
            case TAS::Stage::WITHERED_BONNIE_UNLOCK:
            case TAS::Stage::JACK_O_BONNIE_UNLOCK:
            case TAS::Stage::JACK_O_CHICA_UNLOCK:
            case TAS::Stage::NIGHTMARE_BB_UNLOCK:
            case TAS::Stage::NIGHTMARIONNE_UNLOCK:
            case TAS::Stage::COFFEE_UNLOCK:
            case TAS::Stage::PURPLE_GUY_UNLOCK:
            case TAS::Stage::ENDO_01_UNLOCK:
            case TAS::Stage::ENDO_02_UNLOCK:
            case TAS::Stage::PLUSHTRAP_UNLOCK:
            case TAS::Stage::ENDOPLUSH_UNLOCK:
            case TAS::Stage::SPRINGTRAP_UNLOCK:
            case TAS::Stage::RXQ_UNLOCK:
            case TAS::Stage::CRYING_CHILD_UNLOCK:
            case TAS::Stage::FUNTIME_FOXY_UNLOCK:
            case TAS::Stage::NIGHTMARE_FREDBEAR_UNLOCK:
            case TAS::Stage::NIGHTMARE_UNLOCK:
            case TAS::Stage::FREDBEAR_UNLOCK:
            case TAS::Stage::SPRING_BONNIE_UNLOCK:
            case TAS::Stage::WITHERED_CHICA_UNLOCK:
            case TAS::Stage::WITHERED_FREDDY_UNLOCK:
            case TAS::Stage::WITHERED_FOXY_UNLOCK:
            case TAS::Stage::NIGHTMARE_FREDDY_UNLOCK:
            case TAS::Stage::NIGHTMARE_BONNIE_UNLOCK:
            case TAS::Stage::NIGHTMARE_CHICA_UNLOCK:
            case TAS::Stage::NIGHTMARE_FOXY_UNLOCK:
            case TAS::Stage::SHADOW_FREDDY_UNLOCK:
            case TAS::Stage::MARIONETTE_UNLOCK:
            case TAS::Stage::PHANTOM_MARIONETTE_UNLOCK:
            case TAS::Stage::GOLDEN_FREDDY_UNLOCK:
            case TAS::Stage::PAPERPALS_UNLOCK:
                YuniUtil::SetReturnInt(1); // Pls run
                return;
        }
        YuniUtil::SetReturnInt(0); // Pls don't run
        return;
    }
    // Unscrew Timer
    else if (runHeader->App->nCurrentFrame == 5 && (eventIndex == 668 || eventIndex == 669))
    {
        YuniUtil::SetReturnInt(0); // Quickest Unscrew
        return;
    }
    // Unscrew Chance
    else if (runHeader->App->nCurrentFrame == 5 && eventIndex >= 737 && eventIndex <= 740)
    {
        YuniUtil::SetReturnInt(0); // Always Unscrew
        return;
    }
    // Token Count
    else if (runHeader->App->nCurrentFrame == 5 && eventIndex == 1078)
    {
        // ((Alterable Value S("make character") * value("area")) + ((Random(11) / 10) * 10) + Random(6))
        YuniUtil::SetReturnInt(0); // As little tokens as possible
        return;
    }
    // Gold Endo Chance
    else if (runHeader->App->nCurrentFrame == 5 && eventIndex == 1863)
    {
        if (TAS::stage == TAS::Stage::GOLD_ENDO_GRIND)
            YuniUtil::SetReturnInt(1); // Always give Gold Endo
        else
            YuniUtil::SetReturnInt(0); // Don't give Gold Endo
        return;
    }
    // X-Reaper Chance
    else if (runHeader->App->nCurrentFrame == 5 && eventIndex == 1740)
    {
        YuniUtil::SetReturnInt(1); // Always throw scythe
        return;
    }
    // Scythe Kill Chance
    else if (runHeader->App->nCurrentFrame == 5 && eventIndex >= 1744 && eventIndex <= 1745)
    {
        YuniUtil::SetReturnInt(1); // Always kill
        return;
    }
    // Slasher Kill Chance
    else if (runHeader->App->nCurrentFrame == 5 && eventIndex == 2051)
    {
        YuniUtil::SetReturnInt(0); // Always kill
        return;
    }
    // Party Charge (idc what for)
    else if (runHeader->App->nCurrentFrame == 5 && eventIndex == 1378)
    {
        if (TAS::stage >= TAS::Stage::MAGICAL_PAINBOW)
        {
            YuniUtil::SetReturnInt(4); // No delay
            return;
        }
    }
    // Party Charge (idc what for)
    else if (runHeader->App->nCurrentFrame == 5 && eventIndex == 1517)
    {
        if (TAS::stage >= TAS::Stage::MAGICAL_PAINBOW)
        {
            YuniUtil::SetReturnInt(1); // No delay
            return;
        }
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