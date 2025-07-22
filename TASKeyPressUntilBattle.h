#pragma once
#include <vector>
#include "TASKeyPress.h"
#include "Edif/MMFWindowsMasterHeader.hpp"
#include "YuniUtil.h"

class TASKeyPressUntilBattle : public TASKeyPress
{
public:
	TASKeyPressUntilBattle(std::vector<char> keyCodes)
	{
		this->keyCodes = keyCodes;
	}

	bool Tick()
	{
		if (!timerChanged)
			std::cout << "Key Down, waiting for battle.\n";
		timerChanged = true;

		RunHeader* runHeader = GetRunHeader();
		RunObject* battle = YuniUtil::GetFirstRunObjectFromName(_T("battle"));
		if (YuniUtil::GetCounterValue(battle) == 1)
			return true;
		return false;
	}
};