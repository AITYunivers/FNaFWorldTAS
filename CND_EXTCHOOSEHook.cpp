#pragma once
#include "CND_EXTCHOOSEHook.h"
#include "CRunHook.h"
#include "YuniUtil.h"
#include <iostream>

BOOL __cdecl CND_EXTCHOOSEHook::evaluate(event2* ace)
{
    RunHeader* runHeader = GetRunHeader();

    // Custom handling for specific events
    int eventIndex = YuniUtil::GetEventIndex();

    if (runHeader->App->nCurrentFrame == 5 && eventIndex == 1851 && TAS::stage == TAS::Stage::PEARL_CHEST)
    {
        unsigned int oil = (unsigned int)ace->evtOiList;
        RunObject* obj = CEventProgramHook::count_ObjectsFromOiList(oil, 28 - 3, new int(0));
        CEventProgramHook::evt_ForceOneObject(oil, obj);
    }
    else if (runHeader->App->nCurrentFrame == 19 && eventIndex >= 12 && eventIndex <= 23)
    {
        unsigned int oil = (unsigned int)ace->evtOiList;
        int stop = 0;
        switch (eventIndex - 12)
        {
            case 0:
                stop = 10;
                break;
            case 1:
                stop = 19;
                break;
            case 2:
            case 3:
            case 4:
                stop = eventIndex - 9; // 5 -> 7
                break;
            case 5:
                stop = 26; // Pearl
                break;
            case 6:
                stop = 9;
                break;
            case 7:
            case 8:
            case 9:
                stop = eventIndex - 7; // 12 -> 14
                break;
            case 10:
                stop = 24;
                break;
            case 11:
                stop = 1;
                break;
        }
        RunObject* obj = CEventProgramHook::count_ObjectsFromOiList(oil, 27 - stop, new int(0));
        CEventProgramHook::evt_ForceOneObject(oil, obj);
    }
    else if (runHeader->App->nCurrentFrame == 19 && eventIndex == 40)
    {
        unsigned int oil = (unsigned int)ace->evtOiList;
        RunObject* obj = CEventProgramHook::count_ObjectsFromOiList(oil, 5 - 2, new int(0));
        CEventProgramHook::evt_ForceOneObject(oil, obj);
    }
    else
    {
        int* count(0);
        CEventProgramHook::count_ObjectsFromOiList(ace->evtOiList, -1, (int*)&count);
        if (count == 0) // Found no objects
            return FALSE;

        runHeader->rh3.Graine = runHeader->rh3.Graine * 0x7ab7 + 1;
        unsigned int oil = (unsigned int)ace->evtOiList;
        int stop = (int)(short)((unsigned int)runHeader->rh3.Graine * ((unsigned int)count & 0xffff) >> 0x10);
        RunObject* obj = CEventProgramHook::count_ObjectsFromOiList(oil, stop, new int(0));
        CEventProgramHook::evt_ForceOneObject(oil, obj);
    }
    return TRUE;
}