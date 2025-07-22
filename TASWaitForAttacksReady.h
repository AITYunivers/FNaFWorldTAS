#pragma once
#include <vector>
#include "TASEvent.h"
#include "MMFGlobals.h"
#include "Edif/MMFWindowsMasterHeader.hpp"
#include <iostream>
#include "YuniUtil.h"

class TASWaitForAttacksReady : public TASEvent
{
public:
	bool timerChanged;

	TASWaitForAttacksReady() : timerChanged(false)
	{

	}

	bool Tick()
	{
		if (!timerChanged)
		{
			std::cout << "Waiting for attacks to be ready.\n";
			timerChanged = true;
			return false; // Wait 1 frame before checking anything
		}

		RunHeader* runHeader = GetRunHeader();
		RunObject* button = YuniUtil::GetFirstRunObjectFromName(_T("button"));
		if (button != nullptr && button->roc.rcSpeed == 0)
			return true;
		return false;
	}
};