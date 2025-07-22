#pragma once
#include <vector>
#include "TASEvent.h"
#include "MMFGlobals.h"
#include "Edif/MMFWindowsMasterHeader.hpp"
#include <iostream>
#include "YuniUtil.h"

class TASWaitForDeedee : public TASEvent
{
public:
	bool timerChanged;

	TASWaitForDeedee() : timerChanged(false)
	{

	}

	bool Tick()
	{
		if (!timerChanged)
			std::cout << "Waiting for Deedee.\n";
		timerChanged = true;

		RunHeader* runHeader = GetRunHeader();
		RunObject* runObject = YuniUtil::GetFirstRunObjectFromName(_T("shop 3"));
		if (YuniUtil::GetAlterableValue(runObject, 4) != 1)
			return true;
		return false;
	}
};