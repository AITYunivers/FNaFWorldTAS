#pragma once
#include "Edif/MMFWindowsMasterHeader.hpp"
#include "MMFGlobals.h"
#include "TAS.h"

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