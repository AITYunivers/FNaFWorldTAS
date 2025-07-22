#pragma once
#include <vector>
#include "TASEvent.h"
#include "MMFGlobals.h"
#include "Edif/MMFWindowsMasterHeader.hpp"
#include <iostream>
#include "YuniUtil.h"

class TASWaitForVictory: public TASEvent
{
public:
	bool timerChanged;

	TASWaitForVictory() : timerChanged(false)
	{

	}

	bool Tick()
	{
		if (!timerChanged)
			std::cout << "Waiting for victory.\n";
		timerChanged = true;

		RunHeader* runHeader = GetRunHeader();
		RunObject* victory = YuniUtil::GetFirstRunObjectFromName(_T("victory"));
		if (victory != nullptr && victory->roc.rcSpeed == 0)
			return true;
		return false;
	}
};