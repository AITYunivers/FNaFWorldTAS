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
    int* count(0);
    CEventProgramHook::count_ObjectsFromOiList(ace->evtOiList, -1, (int*)&count);
    if (count == 0) // Found no objects
        return FALSE;

    runHeader->rh3.Graine = runHeader->rh3.Graine * 0x7ab7 + 1;
    unsigned int oil = (unsigned int)ace->evtOiList;
    int stop = (int)(short)((unsigned int)runHeader->rh3.Graine * ((unsigned int)count & 0xffff) >> 0x10);
    RunObject* obj = CEventProgramHook::count_ObjectsFromOiList(oil, stop, new int(0));
    CEventProgramHook::evt_ForceOneObject(oil, obj);
    return TRUE;
}