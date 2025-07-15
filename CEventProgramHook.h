#pragma once
#include "HookHelper.h"
#include "MMFGlobals.h"

CREATE_FUNC(CEVENTPROGRAM_handle_GlobalEvents, 0x58b00, void, int code);
CREATE_FUNC(CEVENTPROGRAM_compute_TimerEvents, 0x58e10, void);
CREATE_FUNC(CEVENTPROGRAM_evt_AddCurrentObject, 0x59f40, void, void* param);
CREATE_FUNC(CEVENTPROGRAM_evt_AddCurrentQualifier, 0x59ec0, void, unsigned int param);
CREATE_FUNC(CEVENTPROGRAM_onMouseButton, 0x57a80, void, int mouseBtn);
CREATE_FUNC(CEVENTPROGRAM_computeEventList, 0x58f80, void, int num, RunObject* rHo);
CREATE_FUNC(CEVENTPROGRAM_handle_Event, 0x58b40, void, RunObject* rHo, int code);

class CEventProgramHook
{
public:
	// Hooks
	static void __fastcall handle_GlobalEvents(int code);
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

	static void onMouseButton(int mouseBtn)
	{
		CEVENTPROGRAM_onMouseButton(mouseBtn);
	};

	static void computeEventList(int num, RunObject* rHo)
	{
		CEVENTPROGRAM_computeEventList(num, rHo);
	};

	static void handle_Event(RunObject* rHo, int code)
	{
		CEVENTPROGRAM_handle_Event(rHo, code);
	};
};