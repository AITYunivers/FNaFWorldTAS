#pragma once
#include <Psapi.h>
#include <iostream>
#include <cstdio>
#include <cstdint>
#include "HookHelper.h"
#include "MMFGlobals.h"

CREATE_FUNC(CEVENTPROGRAM_handle_GlobalEvents, 0x58b00, void, void* param);
CREATE_FUNC(CEVENTPROGRAM_compute_TimerEvents, 0x58e10, void);
CREATE_FUNC(CEVENTPROGRAM_evt_AddCurrentObject, 0x59f40, void, void* param);
CREATE_FUNC(CEVENTPROGRAM_evt_AddCurrentQualifier, 0x59ec0, void, unsigned int param);

class CEventProgramHook
{
public:
	// Hooks
	static void __fastcall handle_GlobalEvents(void* param);
	static void __fastcall compute_TimerEvents();

	// Callbacks
	static void evt_AddCurrentObject(void* param)
	{
		CEVENTPROGRAM_evt_AddCurrentObject(param);
	};

	static void evt_AddCurrentQualifier(unsigned int param)
	{
		CEVENTPROGRAM_evt_AddCurrentQualifier(param);
	};
};