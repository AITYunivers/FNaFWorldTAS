#pragma once
#include <vector>
#include "TASEvent.h"
#include "MMFGlobals.h"
#include "Edif/MMFWindowsMasterHeader.hpp"
#include <iostream>
#include "YuniUtil.h"

class TASWaitForTokens : public TASEvent
{
public:
	bool timerChanged;

	TASWaitForTokens() : timerChanged(false)
	{

	}

	bool Tick()
	{
		if (!timerChanged)
			std::cout << "Waiting for tokens.\n";
		timerChanged = true;

		RunHeader* runHeader = GetRunHeader();
		RunObject* tokens = YuniUtil::GetFirstRunObjectFromName(_T("tokens"));
		if (tokens != nullptr && YuniUtil::GetCounterValue(tokens) == 0)
			return true;
		return false;
	}
};