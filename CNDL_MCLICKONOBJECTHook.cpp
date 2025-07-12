#pragma once
#include "CNDL_MCLICKONOBJECTHook.h"
#include "CRunHook.h"
#include "YuniUtil.h"
#include "CEventProgramHook.h"

BOOL CNDL_MCLICKONOBJECTHook::evaluate(event2* ace)
{
    RunHeader* runHeader = GetRunHeader();
    ParamKey* paramKey = (ParamKey*)YuniUtil::GetParam(ace, 0);
    ParamObject* paramObj = (ParamObject*)YuniUtil::GetParam(ace, 1);

    if (runHeader->CurParam[0] != paramKey->VK_Code)
        return FALSE;

    unsigned short clickedObj = runHeader->CurParam[1];
    if (clickedObj == paramObj->Number)
    {
        CEventProgramHook::evt_AddCurrentObject(runHeader->rh4._2ndObject);
        return TRUE;
    }

    unsigned short qualifier = paramObj->OffsetListOI;
    if ((short)qualifier < 0)
    {
        short* qualifierList = (short*)((qualifier & 0x7fff) + 0x16 + (int)runHeader->QualToOiList);
        short objectInList = *qualifierList;
        while (-1 < objectInList)
        {
            if (objectInList == clickedObj)
            {
                CEventProgramHook::evt_AddCurrentQualifier(qualifier);
                CEventProgramHook::evt_AddCurrentObject(runHeader->rh4._2ndObject);
                return TRUE;
            }

            qualifierList = qualifierList + 2;
            objectInList = *qualifierList;
        }
    }
    return FALSE;
}