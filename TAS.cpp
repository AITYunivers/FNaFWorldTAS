#include "TAS.h"

bool TAS::running = false;
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

		MoveDownFor(10);
		WaitFor(10);
		MoveRightFor(10);
		WaitFor(10);
		MoveUpFor(10);
		WaitFor(10);
		MoveLeftFor(10);
		WaitFor(10);
	}
}