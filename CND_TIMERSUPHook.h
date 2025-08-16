#pragma once
#include "HookHelper.h"
#include "MMFGlobals.h"

CREATE_FUNC_THISCALL(CND_TIMERSUP_evaluate, 0x0a8d0, BOOL, event2* ace);

class CND_TIMERSUPHook
{
public:
	// Hooks
	static BOOL __cdecl evaluate(event2* ace);
};