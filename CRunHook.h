#pragma once
#include "HookHelper.h"
#include "MMFGlobals.h"

CREATE_FUNC(CRUN_f_GameLoop, 0x29f40, int);
CREATE_FUNC(CRUN_calcMouseClientPos, 0x2a610, void);
CREATE_FUNC(CRUN_getExpression, 0x1f6f0, CValueMultiPlat*);
CREATE_FUNC(CRUN_prepareFrame, 0x459b0, int);

class CRunHook
{
public:
	// Hooks
	static int __fastcall f_GameLoop();
	static void __fastcall calcMouseClientPos();
	static int __fastcall prepareFrame();

	// Callbacks
	static CValueMultiPlat* getExpression()
	{
		return CRUN_getExpression();
	};
};