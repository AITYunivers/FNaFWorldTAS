#pragma once
#include <vector>
#include "TASEvent.h"
#include "MMFGlobals.h"
#include "Edif/MMFWindowsMasterHeader.hpp"
#include <iostream>
#include "YuniUtil.h"

class TASWaitForBattleEnd : public TASEvent
{
public:
	bool timerChanged;

	TASWaitForBattleEnd() : timerChanged(false)
	{

	}

	bool Tick()
	{
		if (!timerChanged)
			std::cout << "Waiting for battle end.\n";
		timerChanged = true;

		RunHeader* runHeader = GetRunHeader();
		RunObject* battle = YuniUtil::GetFirstRunObjectFromName(_T("battle"));
		if (YuniUtil::GetCounterValue(battle) == 0)
			return true;
		return false;
	}
};