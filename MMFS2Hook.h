#pragma once
#include "HookHelper.h"
#include "MMFGlobals.h"

CREATE_FUNC(MMFS2_ORDINAL47, 0xab630, void, void* param1, RECT* param2);
CREATE_FUNC(MMFS2_ORDINAL70, 0xab60c, Spr*, void* param1, Spr* param2, int param3, int param4, int param5, DWORD param6);
CREATE_FUNC(MMFS2_ORDINAL77, 0xab610, LPARAM, void* param1, Spr* param2);

class MMFS2Hook
{
public:
	// Callbacks
	static void WinGetLogRect(void* param1, RECT* param2)
	{
		MMFS2_ORDINAL47(param1, param2);
	};

	static Spr* SpriteCol_TestPoint(void* param1, Spr* param2, int param3, int param4, int param5, DWORD param6)
	{
		return MMFS2_ORDINAL70(param1, param2, param3, param4, param5, param6);
	};

	static LPARAM GetSpriteExtra(void* param1, Spr* param2)
	{
		return MMFS2_ORDINAL77(param1, param2);
	};
};