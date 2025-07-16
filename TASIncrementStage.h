#pragma once
#include "TASEvent.h"
#include "Edif/MMFWindowsMasterHeader.hpp"
#include "TAS.h"
#include <iostream>

class TASIncrementStage : public TASEvent
{
public:
	TASIncrementStage()
	{

	}

	bool Tick()
	{
		TAS::stage = (TAS::Stage)((int)TAS::stage + 1);
		std::cout << "Incremented stage to " << std::to_string((int)TAS::stage) << ".\n";
		return true;
	}
};