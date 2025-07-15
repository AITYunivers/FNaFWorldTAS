#pragma once
#include "CND_KBPRESSKEYHook.h"
#include "CRunHook.h"
#include "YuniUtil.h"

bool CND_KBPRESSKEYHook::evaluate(event2* ace)
{
    RunHeader* runHeader = GetRunHeader();
    ParamKey* param = (ParamKey*)YuniUtil::GetParam(ace, 0);

    if (YuniUtil::IsKeyDown(param->VK_Code))
        return ~ace->evtFlags2 & EVFLAG2_NOT;
    return ace->evtFlags2 & EVFLAG2_NOT;
}