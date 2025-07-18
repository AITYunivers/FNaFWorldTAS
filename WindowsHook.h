#pragma once
#include "HookHelper.h"
#include "MMFGlobals.h"

extern DWORD(__stdcall* WNDS_timeGetTime)();

class WindowsHook
{
public:
	// Statics
	static unsigned int oldLoopCount;
	static int totalLoops;
	static bool calledFromAlloc;

	// Hooks
	static DWORD __stdcall timeGetTime();
};