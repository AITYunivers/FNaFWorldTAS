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
	bool doReturn;

	TASWaitForFrame(int frame) : frame(frame), timerChanged(false), doReturn(false)
	{

	}

	bool Tick()
	{
		if (doReturn)
			return true;

		if (!timerChanged)
			std::cout << "Waiting for frame.\n";
		timerChanged = true;

		RunHeader* runHeader = GetRunHeader();
		if (!IsBadReadPtr(runHeader, sizeof(RunHeader)) && !IsBadReadPtr(runHeader->App, sizeof(CRunApp)))
			doReturn = runHeader->App->nCurrentFrame == frame;
		return false;
	}
};