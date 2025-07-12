#pragma once
#include "HookHelper.h"
#include "MMFGlobals.h"

CREATE_FUNC(EXP_RANDOM_evaluate, 0x11b90, void);

class EXP_RANDOMHook
{
public:
	// Hooks
	static void evaluate();
};