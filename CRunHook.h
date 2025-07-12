#pragma once
#include "HookHelper.h"
#include "MMFGlobals.h"

CREATE_FUNC(CRUN_f_GameLoop, 0x29f40, int);
CREATE_FUNC(CRUN_getExpression, 0x1f6f0, CValueMultiPlat*);

class CRunHook
{
public:
	// Hooks
	static int __fastcall f_GameLoop();

	// Callbacks
	static CValueMultiPlat* getExpression()
	{
		return CRUN_getExpression();
	};
};