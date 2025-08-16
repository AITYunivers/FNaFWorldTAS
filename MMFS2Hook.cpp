#pragma once
#include "MMFS2Hook.h"

int(__stdcall* MMFS2_LockBank)(void*, int) = nullptr;
int(__stdcall* MMFS2_UnlockBank)(void*, int) = nullptr;
unsigned int(__stdcall* MMFS2_IncFontCount)(void*, unsigned int) = nullptr;
unsigned int(__stdcall* MMFS2_IncImageCount)(void*, unsigned int) = nullptr;
int(__stdcall* MMFS2_IsSndPlaying)(void*, unsigned int) = nullptr;
unsigned int(__stdcall* MMFS2_IncSoundCount)(void*, unsigned int) = nullptr;

void MMFS2Hook::LoadHooks()
{
	MMFS2_LockBank = reinterpret_cast<int(__stdcall*)(void*, int)>(GET_DLL_ADDRESS(L"mmfs2.dll", 0x08440));
	MMFS2_UnlockBank = reinterpret_cast<int(__stdcall*)(void*, int)>(GET_DLL_ADDRESS(L"mmfs2.dll", 0x08480));
	MMFS2_IncFontCount = reinterpret_cast<unsigned int(__stdcall*)(void*, unsigned int)>(GET_DLL_ADDRESS(L"mmfs2.dll", 0x08700));
	MMFS2_IncImageCount = reinterpret_cast<unsigned int(__stdcall*)(void*, unsigned int)>(GET_DLL_ADDRESS(L"mmfs2.dll", 0x09970));
	MMFS2_IsSndPlaying = reinterpret_cast<int(__stdcall*)(void*, unsigned int)>(GET_DLL_ADDRESS(L"mmfs2.dll", 0x10e90));
	MMFS2_IncSoundCount = reinterpret_cast<unsigned int(__stdcall*)(void*, unsigned int)>(GET_DLL_ADDRESS(L"mmfs2.dll", 0x10cc0));
}