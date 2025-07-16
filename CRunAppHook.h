#pragma once
#include "HookHelper.h"
#include "MMFGlobals.h"

CREATE_FUNC(CRUNAPP_playApplication, 0x05730, bool, CRunApp*, int);

class CRunAppHook
{
public:
	// Hooks
	static bool __fastcall playApplication(CRunApp* app, int param2);
};