#pragma once
#include "HookHelper.h"
#include "MMFGlobals.h"

CREATE_FUNC(CRUN_getExpression, 0x1f6f0, CValueMultiPlat*);

class CRunHook
{
public:
	// Callbacks
	static CValueMultiPlat* getExpression()
	{
		return CRUN_getExpression();
	};
};