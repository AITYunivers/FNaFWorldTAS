#pragma once
#include "HookHelper.h"
#include "MMFGlobals.h"

CREATE_FUNC(CND_EXTCHOOSE_evaluate, 0x16e00, BOOL, event2* ace);

class CND_EXTCHOOSEHook
{
public:
	// Hooks
	static BOOL evaluate(event2* ace);
};