#pragma once
#include <vector>
#include "TASEvent.h"
#include <iostream>

class TASWait : public TASEvent
{
public:
	int timer;
	bool timerChanged;

	TASWait(int timer) : timer(timer), timerChanged(false)
	{

	}

	bool Tick()
	{
		if (!timerChanged)
			std::cout << "Waiting.\n";
		timerChanged = true;

		timer--;
		return timer <= 0;
	}
};