#include "TAS.h"
#include "TASKeyPress.h"
#include "TASClickAt.h"
#include "TASWait.h"
#include "TASWaitForFrame.h"
#include "TASRestartGame.h"
#include "TASIncrementStage.h"

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
	ClickAt(new POINT(700, 400)); // Reset
	Wait(10);
	ClickCharacter(1, 1); // Freddy
	Wait(10);
	ClickCharacter(8, 1); // Mangle
	Wait(10);
	ClickCharacter(6, 1); // Toy Chica
	Wait(10);
	ClickCharacter(2, 1); // Bonnie
	Wait(10);
	ClickCharacter(5, 1); // Toy Bonnie
	Wait(10);
	ClickCharacter(7, 1); // Toy Freddy
	Wait(10);
	ClickCharacter(3, 1); // Chica
	Wait(10);
	ClickCharacter(4, 1); // Foxy
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
	IncrementStage();
	WaitForFrame(5);
	ClickAt(new POINT(750, 50)); // Jump to 1, tiny bit faster than walking directly
	KeyPress(68, { 'S', 'D' });
	ClickAt(new POINT(750, 50)); // Jump to 1
	KeyPress(65, { 'W' });
	KeyPress(21, { 'W', 'D' });
	WaitForFrame(18);
	ClickAt(new POINT(600, 100)); // Play Deedee's Fishing Hole
	WaitForFrame(19);
	KeyPress(1, { 'D' });
	KeyPress(1, { 'S' });
	IncrementStage();
	WaitForFrame(5);
	KeyPress(10, { 'A', 'S' });
	KeyPress(20, { 'A' });
	Wait(30);
	KeyPress(10, { 'A' });
	WaitForFrame(13);
	Wait(1);
	ClickAt(new POINT(200, 100)); // Buy Gnat
	ClickAt(new POINT(400, 100)); // Buy Neon Bee
	ClickAt(new POINT(700, 450)); // Exit Shop
	WaitForFrame(12);
	Wait(20);
	ClickAt(new POINT(100, 100)); // Equip Gnat
	Wait(9);
	ClickAt(new POINT(200, 100)); // Equip Neon Bee
	ClickAt(new POINT(700, 425)); // Exit Bytes Menu
	WaitForFrame(5);
	ClickAt(new POINT(750, 50)); // Jump to 1
	KeyPress(30, { 'A' });
	KeyPress(94, { 'A', 'W' });
	Wait(80);
	ClickAttack(2, 3);
	Wait(1000);
	Wait(197);
	ClickAttack(2, 3);
	Wait(197);
	ClickAttack(2, 3);
	Wait(70);
	ClickAttack(3, 3);
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

void TAS::IncrementStage()
{
	Queue.push_back(new TASIncrementStage());
}

void TAS::ClickCharacter(int x, int y)
{
	TAS::ClickAt(new POINT(63 + (x - 1) * 73, 56 + (y - 1) * 73));
}

void TAS::ClickAttack(int charSlot, int attackSlot)
{
	// Calcs are offset negatively by (10, 43) to account for indexing from 1
	switch (charSlot)
	{
		case 1:
			TAS::ClickAt(new POINT(256 + attackSlot * 10, -5 + attackSlot * 43));
			break;
		case 2:
			TAS::ClickAt(new POINT(414 + attackSlot * 10, 79 + attackSlot * 43));
			break;
		case 3:
			TAS::ClickAt(new POINT(212 + attackSlot * 10, 151 + attackSlot * 43));
			break;
		case 4:
			TAS::ClickAt(new POINT(361 + attackSlot * 10, 235 + attackSlot * 43));
			break;
	}
}