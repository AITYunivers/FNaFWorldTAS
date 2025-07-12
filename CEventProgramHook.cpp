#pragma once
#include "CEventProgramHook.h"

void __fastcall CEventProgramHook::handle_GlobalEvents(void* param)
{
	//GetRunHeader()->rh2.Mouse = POINT(0, 0);
	CEVENTPROGRAM_handle_GlobalEvents(param);
}

void __fastcall CEventProgramHook::compute_TimerEvents()
{
	RunHeader* runHeader = GetRunHeader();
	runHeader->TimerDelta = (unsigned int)(1 / 60.0f * 1000);

	CEVENTPROGRAM_compute_TimerEvents();
}