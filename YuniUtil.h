#pragma once
#include <WinUser.h>
#include "Edif/MMFWindowsMasterHeader.hpp"
#include "MMFGlobals.h"
#include "TAS.h"
#include "CEventProgramHook.h"
#include "MMFS2Hook.h"

namespace YuniUtil
{
	static bool IsKeyDown(char keyChar)
	{
		RunHeader* runHeader = GetRunHeader();
		HWND pHVar6 = GetActiveWindow();
		if (pHVar6 == runHeader->HTopLevelWnd ||
			pHVar6 == runHeader->HEditWin ||
			pHVar6 == runHeader->HMainWin)
		{
			if (TAS::IsKeyPressed(keyChar))
				return true;

			SHORT keyState = GetKeyState(keyChar);
			return keyState < 0;
		}
		return false;
	}

	static int GetEventIndex()
	{
		RunHeader* runHeader = GetRunHeader();
		int eventCount = 1;
		int pointer = (int)&runHeader->Frame->eventPrograms->evgSize;
		int end = (int)&runHeader->EventGroup->evgSize;
		while (pointer != end)
		{
			pointer -= ((eventGroup*)pointer)->evgSize;
			eventCount++;
		}
		return eventCount;
	}

	static void AdvanceExpToken()
	{
		RunHeader* runHeader = GetRunHeader();
		expression* expToken = runHeader->rh4.ExpToken;
		(runHeader->rh4).ExpToken = (expression*)(&expToken->u + expToken->size + -6);
	}

	static void SetReturnInt(int value)
	{
		RunHeader* runHeader = GetRunHeader();
		CValueMultiPlat* result = (CValueMultiPlat*)runHeader->rh4.Results[runHeader->rh4.PosPile];
		result->m_type = 0;
		result->m_long = value;
	}

	static uintptr_t GetParam(event2* ace, int index)
	{
		uintptr_t ptr = (uintptr_t)ace + sizeof(event2);
		for (int i = 0; i < index; i++)
		{
			short size = *(short*)ptr;
			ptr += size;
		}
		return ptr + 4;
	}
}