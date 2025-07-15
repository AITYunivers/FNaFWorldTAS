#pragma once
#include "HookHelper.h"
#include "MMFGlobals.h"

CREATE_FUNC(CND_KBPRESSKEY_evaluate, 0x0a020, bool, event2* ace);

class CND_KBPRESSKEYHook
{
public:
	// Hooks
	static bool evaluate(event2* ace);
};