#pragma once
#include <vector>
#include "TASEvent.h"
#include "CEventProgramHook.h"
#include "Edif/MMFWindowsMasterHeader.hpp"
#include "TAS.h"
#include <iostream>

class TASClickAt : public TASEvent
{
public:
	POINT* mousePos;
	int mouseBtn;

	TASClickAt(POINT* mousePos, int mouseBtn = 0x201) : mousePos(mousePos), mouseBtn(mouseBtn)
	{

	}

	bool Tick()
	{
		std::cout << "Clicked.\n";

		TAS::mousePos = mousePos;
		CEventProgramHook::onMouseButton(mouseBtn);
		TAS::mousePos = nullptr;
		return true;
	}
};