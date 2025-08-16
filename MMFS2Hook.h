#pragma once
#include "HookHelper.h"
#include "MMFGlobals.h"

CREATE_FUNC(MMFS2_WinGetLogRect, 0xab630, void, void* param1, RECT* param2);
CREATE_FUNC(MMFS2_SpriteCol_TestPoint, 0xab60c, Spr*, void* param1, Spr* param2, int param3, int param4, int param5, DWORD param6);
CREATE_FUNC(MMFS2_GetSpriteExtra, 0xab610, LPARAM, void* param1, Spr* param2);

extern int(__stdcall* MMFS2_LockBank)(void*, int);
extern int(__stdcall* MMFS2_UnlockBank)(void*, int);
extern unsigned int(__stdcall* MMFS2_IncFontCount)(void*, unsigned int);
extern unsigned int(__stdcall* MMFS2_IncImageCount)(void*, unsigned int);
extern int(__stdcall* MMFS2_IsSndPlaying)(void*, unsigned int);
extern unsigned int(__stdcall* MMFS2_IncSoundCount)(void*, unsigned int);

class MMFS2Hook
{
public:
	// Functions
	static void LoadHooks();

	// Callbacks
	static void WinGetLogRect(void* param1, RECT* param2)
	{
		MMFS2_WinGetLogRect(param1, param2);
	};

	static Spr* SpriteCol_TestPoint(void* param1, Spr* param2, int param3, int param4, int param5, DWORD param6)
	{
		return MMFS2_SpriteCol_TestPoint(param1, param2, param3, param4, param5, param6);
	};

	static LPARAM GetSpriteExtra(void* param1, Spr* param2)
	{
		return MMFS2_GetSpriteExtra(param1, param2);
	};

	static int LockBank(void* param1, int param2)
	{
		return MMFS2_LockBank(param1, param2);
	};

	static int UnlockBank(void* param1, int param2)
	{
		return MMFS2_UnlockBank(param1, param2);
	};

	static unsigned int IncFontCount(void* param1, unsigned int param2)
	{
		return MMFS2_IncFontCount(param1, param2);
	};

	static unsigned int IncImageCount(void* param1, unsigned int param2)
	{
		return MMFS2_IncImageCount(param1, param2);
	};

	static int IsSndPlaying(void* param1, unsigned int param2)
	{
		return MMFS2_IsSndPlaying(param1, param2);
	};

	static unsigned int IncSoundCount(void* param1, unsigned int param2)
	{
		return MMFS2_IncSoundCount(param1, param2);
	};
};