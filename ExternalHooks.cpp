#pragma once
#include "ExternalHooks.h"

BOOL __stdcall ExternalHooks::GetCursorPosHook(LPPOINT lpPoint)
{
	return GetCursorPos(lpPoint);
}