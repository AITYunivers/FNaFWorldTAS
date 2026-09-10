#pragma once
#include <vector>
#include "TASEvent.h"
#include "MMFGlobals.h"
#include "Edif/MMFWindowsMasterHeader.hpp"
#include <iostream>

class TASGotoFrame : public TASEvent
{
public:
	int frame;
	bool timerChanged;
	bool doReturn;

	TASGotoFrame(int frame) : frame(frame), timerChanged(false), doReturn(false)
	{

	}

	bool Tick()
	{
		if (doReturn)
			return true;

		if (!timerChanged)
			std::cout << "Jumping to frame " << std::to_string(frame) << ".\n";

		RunHeader* runHeader = GetRunHeader();
		if (!IsBadReadPtr(runHeader, sizeof(RunHeader)) && !IsBadReadPtr(runHeader->App, sizeof(CRunApp)))
		{
			if (!timerChanged)
			{
				int16_t level = static_cast<int16_t>(frame);
				runHeader->Quit = LOOPEXIT_GOTOLEVEL;
				runHeader->QuitParam = level;
			}
			doReturn = runHeader->App->nCurrentFrame == frame;
		}

		timerChanged = true;
		return false;
	}
};