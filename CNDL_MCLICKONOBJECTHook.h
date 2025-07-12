#pragma once
#include "HookHelper.h"
#include "MMFGlobals.h"

CREATE_FUNC(CNDL_MCLICKONOBJECT_evaluate, 0x0a480, BOOL, event2* ace);

class CNDL_MCLICKONOBJECTHook
{
public:
	// Hooks
	static BOOL evaluate(event2* ace);
};