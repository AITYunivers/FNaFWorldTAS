#pragma once
#include <vector>
#include "TASEvent.h"
#include "MMFGlobals.h"
#include "Edif/MMFWindowsMasterHeader.hpp"
#include <iostream>
#include "YuniUtil.h"

class TASWaitForCinematicEnd : public TASEvent
{
public:
	bool timerChanged;

	TASWaitForCinematicEnd() : timerChanged(false)
	{

	}

	bool Tick()
	{
		if (!timerChanged)
			std::cout << "Waiting for cinematic to end.\n";
		timerChanged = true;

		RunHeader* runHeader = GetRunHeader();
		int cinematic = YuniUtil::GetCounterValue(YuniUtil::GetFirstRunObjectFromName(_T("cinematic")));
		int textStage = YuniUtil::GetCounterValue(YuniUtil::GetFirstRunObjectFromName(_T("text stage")));
		if (cinematic == 2 && textStage == 7)
			return true;
		else if (cinematic == 3 && textStage == 8)
			return true;
		else if (cinematic == 4 && textStage == 7)
			return true;
		else if (cinematic == 5 && textStage == 7)
			return true;
		else if (cinematic == 7 && textStage == 5)
			return true;
		return false;
	}
};