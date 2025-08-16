#pragma once
#include <vector>
#include "TASKeyPress.h"
#include "Edif/MMFWindowsMasterHeader.hpp"

class TASKeyPressUntilFrame : public TASKeyPress
{
public:
	int frame;
	bool doReturn;

	TASKeyPressUntilFrame(int frame, std::vector<char> keyCodes) : frame(frame), doReturn(false)
	{
		this->keyCodes = keyCodes;
	}

	bool Tick()
	{
		if (doReturn)
			return true;

		if (!timerChanged)
			std::cout << "Key Down, waiting for frame " << std::to_string(frame) << ".\n";
		timerChanged = true;

		CRunApp* app = GetCRunApp();
		if (!IsBadReadPtr(app, sizeof(CRunApp)))
			doReturn = app->nCurrentFrame == frame;
		return false;
	}
};