#pragma once
#include "HookHelper.h"
#include "MMFGlobals.h"

CREATE_FUNC(CNDL_MCLICK_evaluate, 0x0a130, bool, event2* ace);

class CNDL_MCLICKHook
{
public:
	// Hooks
	static bool evaluate(event2* ace);
};