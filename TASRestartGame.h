#pragma once
#include "TASEvent.h"
#include "Edif/MMFWindowsMasterHeader.hpp"
#include "TAS.h"
#include <iostream>

class TASRestartGame: public TASEvent
{
public:
	TASRestartGame()
	{

	}

	bool Tick()
	{
		std::cout << "Restarted game.\n";

		GetRunHeader()->Quit = LOOPEXIT_NEWGAME;
		return true;
	}
};