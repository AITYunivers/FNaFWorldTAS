#pragma once
#include "CND_TIMERSUPHook.h"
#include "CRunHook.h"
#include "YuniUtil.h"

BOOL __cdecl CND_TIMERSUPHook::evaluate(event2* ace)
{
	RunHeader* runHeader = GetRunHeader();
	unsigned int stableTimer = (1.0 / 60.0) / 0.001 * (runHeader->LoopCount + 1);

	EventParam* param = YuniUtil::GetEventParam(ace, 0);
	if (param->Code != 0x16)
	{
		ParamTime* timeParam = (ParamTime*)YuniUtil::GetParam(ace, 0);
		return timeParam->Timer < stableTimer;
	}
	ParamExpression* expParam = (ParamExpression*)YuniUtil::GetParam(ace, 0);
	runHeader->rh4.ExpToken = expParam->Token;
	CValueMultiPlat* expValue = CRunHook::getExpression();
	switch (expValue->m_type)
	{
		case 0:
			return expValue->m_long < stableTimer;
		case 1:
			return stableTimer != 0;
		case 2:
			return (unsigned int)expValue->m_double < stableTimer;
	}
}