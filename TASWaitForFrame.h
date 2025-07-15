#pragma once
#include <vector>
#include "TASEvent.h"
#include "MMFGlobals.h"
#include "Edif/MMFWindowsMasterHeader.hpp"
#include <iostream>

class TASWaitForFrame : public TASEvent
{
public:
	int frame;
	bool timerChanged;

	TASWaitForFrame(int frame) : frame(frame), timerChanged(false)
	{

	}

	bool Tick()
	{
		if (!timerChanged)
			std::cout << "Waiting for frame.\n";
		timerChanged = true;

		RunHeader* runHeader = GetRunHeader();
		if (IsBadReadPtr(runHeader, sizeof(RunHeader)) || IsBadReadPtr(runHeader->App, sizeof(CRunApp)))
			return false;
		return runHeader->App->nCurrentFrame == frame;
	}
};