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
CREATE_FUNC(CEVENTPROGRAM_get_CurrentObject, 0x5a4c0, RunObject*, short oiList, BOOL* repeat);
CREATE_FUNC(CEVENTPROGRAM_count_ObjectsFromOiList, 0x5aeb0, RunObject*, unsigned int oil, int stop, int* count);
CREATE_FUNC(CEVENTPROGRAM_evt_ForceOneObject, 0x59fd0, void, unsigned int oil, RunObject* rHo);
CREATE_FUNC(CEVENTPROGRAM_evt_FirstObject, 0x59940, RunObject*, unsigned int oiHandle, int* selectedNum);

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

	static RunObject* get_CurrentObject(short oiList, BOOL* repeat)
	{
		return CEVENTPROGRAM_get_CurrentObject(oiList, repeat);
	};

	static RunObject* count_ObjectsFromOiList(unsigned int oil, int stop, int* count)
	{
		RunObject* result;
		__asm
		{
			push esp
			mov ecx, oil
			mov edx, stop
			push count
			call CEVENTPROGRAM_count_ObjectsFromOiList
			add esp, 4
			mov result, eax
			pop esp
		}
		return result;
	};

	static void evt_ForceOneObject(unsigned int oil, RunObject* rHo)
	{
		CEVENTPROGRAM_evt_ForceOneObject(oil, rHo);
	};

	static RunObject* evt_FirstObject(unsigned int oiHandle, int* selectedNum)
	{
		return CEVENTPROGRAM_evt_FirstObject(oiHandle, selectedNum);
	};
};