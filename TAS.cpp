#include "TAS.h"
#include "TASKeyPress.h"
#include "TASClickAt.h"
#include "TASWait.h"
#include "TASWaitForFrame.h"
#include "TASRestartGame.h"

#pragma region Static Variables
bool TAS::running = false;
unsigned int TAS::oldLoopCount = false;
TAS::Stage TAS::stage = TAS::Stage::START;

std::deque<TASEvent*> TAS::Queue;

POINT* TAS::mousePos = nullptr;
#pragma endregion

void TAS::Run()
{
	CRunApp* app = GetCRunApp();
	running = true;
	return;

	WaitForFrame(0);
	KeyPress(1, { VK_RETURN });
	WaitForFrame(2);
	Wait(3);
	ClickAt(new POINT(800, 450)); // Start
	WaitForFrame(3);
	Wait(29);
	ClickAt(new POINT(400, 150)); // Slot 1
	Wait(19);
	ClickAt(new POINT(400, 200)); // New Game
	Wait(19);
	ClickAt(new POINT(400, 200)); // Erase Data
	Wait(19);
	ClickAt(new POINT(400, 200)); // Adventure Mode
	Wait(19);
	ClickAt(new POINT(400, 250)); // Hard Mode
	WaitForFrame(4);
	ClickAt(new POINT(700, 450)); // Done
	WaitForFrame(27);
	Wait(1); // LiveSplit is slow, might start using a websocket later
	RestartGame();
	WaitForFrame(0);
	Wait(1); // Why? Ig RestartGame messes with the RunHeader for a frame
	KeyPress(1, { VK_RETURN });
	WaitForFrame(2);
	Wait(3);
	ClickAt(new POINT(800, 450)); // Start
	WaitForFrame(3);
	Wait(29);
	ClickAt(new POINT(400, 150)); // Slot 1
	Wait(19);
	ClickAt(new POINT(400, 250)); // Continue
	WaitForFrame(4);
	ClickAt(new POINT(700, 450)); // Done
}

#pragma region KeyPress
void TAS::KeyPress(int timer, std::vector<char> keyCodes)
{
	Queue.push_back(new TASKeyPress(timer, keyCodes));
}

bool TAS::IsKeyPressed(char keyCode)
{
	if (Queue.empty())
		return false;

	if (TASKeyPress* keyPress = dynamic_cast<TASKeyPress*>(Queue.front()))
		for (char key : keyPress->keyCodes)
			if (key == keyCode)
				return true;

	return false;
}
#pragma endregion

#pragma region Mouse
void TAS::ClickAt(POINT* mousePos, int mouseBtn)
{
	Queue.push_back(new TASClickAt(mousePos, mouseBtn));
}
#pragma endregion

void TAS::Wait(int frames)
{
	Queue.push_back(new TASWait(frames));
}

void TAS::WaitForFrame(int frame)
{
	Queue.push_back(new TASWaitForFrame(frame));
}

void TAS::RestartGame()
{
	Queue.push_back(new TASRestartGame());
}