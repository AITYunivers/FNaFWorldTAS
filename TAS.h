#pragma once
#include "MMFGlobals.h"

class TAS
{
public:
	static bool running;
	static void Run();

	static unsigned int moveLeft;
	static void MoveLeftFor(unsigned int frames)
	{
		moveLeft = frames;
	}

	static unsigned int moveRight;
	static void MoveRightFor(unsigned int frames)
	{
		moveRight = frames;
	}

	static unsigned int moveUp;
	static void MoveUpFor(unsigned int frames)
	{
		moveUp = frames;
	}

	static unsigned int moveDown;
	static void MoveDownFor(unsigned int frames)
	{
		moveDown = frames;
	}

	static unsigned int waitTimer;
	static void WaitFor(unsigned int frames)
	{
		waitTimer = frames;
		while (waitTimer > 0) {}
	}
};