#pragma once
#include "CND_EXTCHOOSEHook.h"
#include "CRunHook.h"
#include "YuniUtil.h"

BOOL CND_EXTCHOOSEHook::evaluate(event2* ace)
{
    RunHeader* runHeader = GetRunHeader();

    // Custom handling for specific events
    int eventIndex = YuniUtil::GetEventIndex();

    if (runHeader->App->nCurrentFrame == 19 && eventIndex >= 12 && eventIndex <= 23)
    {
        unsigned int oil = (unsigned int)ace->evtOiList;
        int stop = 0;
        switch (eventIndex - 12)
        {
            case 0:
                stop = 2;
                break;
            case 1:
                stop = 19;
                break;
            case 2:
            case 3:
            case 4:
            case 5:
            case 6:
                stop = eventIndex - 9; // 5 -> 9
                break;
            case 7:
            case 8:
            case 9:
                stop = eventIndex - 5; // 12 -> 14
                break;
            case 10:
                stop = 22;
                break;
        }
        RunObject* obj = CEventProgramHook::count_ObjectsFromOiList(oil, stop, (int*)&ace);
        CEventProgramHook::evt_ForceOneObject(oil, obj);
    }
    else
    {
        event2* aceStored = ace;
        CEventProgramHook::count_ObjectsFromOiList(ace->evtOiList, -1, (int*)&ace);
        if (ace == 0) // Found no objects
            return FALSE;

        runHeader->rh3.Graine = runHeader->rh3.Graine * 0x7ab7 + 1;
        unsigned int oil = (unsigned int)aceStored->evtOiList;
        int stop = (int)(short)((unsigned int)runHeader->rh3.Graine * ((unsigned int)ace & 0xffff) >> 0x10);
        RunObject* obj = CEventProgramHook::count_ObjectsFromOiList(oil, stop, (int*)&ace);
        CEventProgramHook::evt_ForceOneObject(oil, obj);
    }
    return TRUE;
}