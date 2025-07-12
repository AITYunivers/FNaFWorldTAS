#pragma once
#include "HookHelper.h"
#include "MMFGlobals.h"

CREATE_FUNC(CND_KEYDEPRESSED_evaluate, 0x0a0c0, bool, event2* ace);

class CND_KEYDEPRESSEDHook
{
public:
	// Hooks
	static bool evaluate(event2* ace);
};