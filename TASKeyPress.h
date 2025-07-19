#pragma once
#include <vector>
#include "TASEvent.h"
#include <iostream>

class TASKeyPress : public TASEvent
{
public:
	std::vector<char> keyCodes;
	int timer;
	bool timerChanged;

	TASKeyPress(int timer, std::vector<char> keyCodes) : timer(timer), keyCodes(keyCodes), timerChanged(false)
	{

	}

	bool Tick()
	{
		if (timer <= 0)
			return true;

		if (!timerChanged)
			std::cout << "Key Down.\n";
		timerChanged = true;

		timer--;

		if (timer <= 0)
			std::cout << "Key Up.\n";
		return false;
	}
};