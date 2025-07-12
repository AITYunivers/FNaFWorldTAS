#pragma once
#include "HookHelper.h"
#include "MMFGlobals.h"

class ExternalHooks
{
public:
	// USER32.DLL
	static BOOL __stdcall GetCursorPosHook(LPPOINT lpPoint);
};