#pragma once
#include "CNDL_MCLICKHook.h"
#include "CRunHook.h"
#include "YuniUtil.h"

bool CNDL_MCLICKHook::evaluate(event2* ace)
{
    RunHeader* runHeader = GetRunHeader();
    ParamKey* param = (ParamKey*)YuniUtil::GetParam(ace, 0);
    return param->VK_Code == runHeader->CurParam[0];
}