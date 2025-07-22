#pragma once
#include <vector>
#include "TASKeyPress.h"
#include "Edif/MMFWindowsMasterHeader.hpp"
#include "YuniUtil.h"

class TASKeyPressUntilChip : public TASKeyPress
{
public:
	TASKeyPressUntilChip(std::vector<char> keyCodes)
	{
		this->keyCodes = keyCodes;
	}

	bool Tick()
	{
		if (!timerChanged)
			std::cout << "Key Down, waiting for chip.\n";
		timerChanged = true;

		RunHeader* runHeader = GetRunHeader();
		RunObject* foundChip = YuniUtil::GetFirstRunObjectFromName(_T("foundchip"));
		if (YuniUtil::GetAlterableValue(foundChip, 0) > 0)
			return true;
		return false;
	}
};