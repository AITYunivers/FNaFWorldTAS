#pragma once
#include <Psapi.h>
#include <iostream>
#include <cstdio>
#include <cstdint>
#include "HookHelper.h"

class CRunApp {
public:
	static int loopFrame();
};

CREATE_FUNC(CRUNAPP_loopFrame, 0x45430, int);