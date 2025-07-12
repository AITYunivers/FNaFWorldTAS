#include "TAS.h"

bool TAS::running = false;
unsigned int TAS::oldLoopCount = false;
unsigned int TAS::moveUp = 0;
unsigned int TAS::moveDown = 0;
unsigned int TAS::moveLeft = 0;
unsigned int TAS::moveRight = 0;
unsigned int TAS::waitTimer = 0;

void TAS::Run()
{
	CRunApp* app = GetCRunApp();
	running = true;

	while (running)
	{
		if (IsBadReadPtr(app, sizeof(CRunApp)) || app->nCurrentFrame != 5)
			continue;

		MoveDownFor(5);
		WaitFor(5);
		MoveDownFor(5);
		MoveRightFor(5);
		WaitFor(5);
		MoveRightFor(5);
		WaitFor(5);
		MoveRightFor(5);
		MoveUpFor(5);
		WaitFor(5);
		MoveUpFor(5);
		WaitFor(5);
		MoveUpFor(5);
		MoveLeftFor(5);
		WaitFor(5);
		MoveLeftFor(5);
		WaitFor(5);
		MoveLeftFor(5);
		MoveDownFor(5);
		WaitFor(5);
	}
}