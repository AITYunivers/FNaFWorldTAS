#pragma once
#include <Windows.h>
#include <detours.h>
#include <string.h>
#include "CRunHook.h"
#include "CEventProgramHook.h"

void __fastcall CEventProgramHook::handle_GlobalEvents(void* param)
{
	//GetRunHeader()->rh2.Mouse = POINT(0, 0);
	CEVENTPROGRAM_handle_GlobalEvents(param);
}