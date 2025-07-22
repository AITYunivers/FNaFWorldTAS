#pragma once
#include <vector>
#include "TASEvent.h"
#include "MMFGlobals.h"
#include "Edif/MMFWindowsMasterHeader.hpp"
#include <iostream>
#include "YuniUtil.h"

class TASWaitUntilChipsBtn : public TASEvent
{
public:
	bool timerChanged;

	TASWaitUntilChipsBtn() : timerChanged(false)
	{

	}

	bool Tick()
	{
		if (!timerChanged)
			std::cout << "Waiting for chips button to be clickable.\n";
		timerChanged = true;

		RunHeader* runHeader = GetRunHeader();
		RunObject* battle = YuniUtil::GetFirstRunObjectFromName(_T("battle"));
		RunObject* owl = YuniUtil::GetFirstRunObjectFromName(_T("owl"));
		if (YuniUtil::GetCounterValue(battle) == 0 && YuniUtil::GetAlterableValue(owl, 2) == 0)
			return true;
		return false;
	}
};