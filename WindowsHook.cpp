#pragma once
#include "WindowsHook.h"

DWORD(__stdcall* WNDS_timeGetTime)() = nullptr;
unsigned int WindowsHook::oldLoopCount = 0;
int WindowsHook::totalLoops = 0;
bool WindowsHook::calledFromAlloc = false;

DWORD __stdcall WindowsHook::timeGetTime()
{
	//if (calledFromAlloc)
	//{
	//	calledFromAlloc = false;
	//	printf(("Setting RNG to " + std::to_string(totalLoops) + "\n").c_str());
	//	return totalLoops;
	//}
	return WNDS_timeGetTime();
}