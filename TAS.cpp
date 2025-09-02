#include "TAS.h"
#include "TASKeyPress.h"
#include "TASClickAt.h"
#include "TASWait.h"
#include "TASWaitForFrame.h"
#include "TASRestartGame.h"
#include "TASIncrementStage.h"
#include "TASKeyPressUntilFrame.h"
#include <filesystem>

#pragma region Static Variables
bool TAS::running = false;
unsigned int TAS::oldLoopCount = false;
unsigned int TAS::oldFrame = false;
TAS::Stage TAS::stage = TAS::Stage::START;

std::deque<TASEvent*> TAS::Queue;

POINT* TAS::mousePos = nullptr;
#pragma endregion

//#define DEBUGTAS

void TAS::Run()
{
	CRunApp* app = GetCRunApp();
	running = true;
#ifdef DEBUGTAS
	LoadTASSavestate();
	WaitForFrame(2); // title screen
	Wait(3);
	ClickAt(new POINT(800, 450)); // Start
	WaitForFrame(3); // file setup
	Wait(30);
	ClickAt(new POINT(400, 150)); // Slot 1
	Wait(20);
	ClickAt(new POINT(400, 250)); // Continue
	WaitForFrame(4); // character select
	ClickAt(new POINT(700, 450)); // Done
	stage = Stage::SHADOW_FREDDY_UNLOCK;
	goto TAS_JUMP;
#endif
#pragma region Begin Game
	WaitForFrame(0); // Frame 32
	WaitForFrame(2); // title screen
	Wait(3);
	ClickAt(new POINT(800, 450)); // Start
	WaitForFrame(3); // file setup
	Wait(30);
	ClickAt(new POINT(400, 150)); // Slot 1
	Wait(20);
	ClickAt(new POINT(400, 200)); // New Game
	Wait(20);
	ClickAt(new POINT(400, 200)); // Erase Data
	Wait(20);
	ClickAt(new POINT(400, 200)); // Adventure Mode
	Wait(20);
	ClickAt(new POINT(400, 250)); // Hard Mode
	WaitForFrame(4); // character select
	ClickAt(new POINT(700, 450)); // Done
	WaitForFrame(27); // cinematic
	Wait(1); // LiveSplit is slow, might start using a websocket later
	RestartGame();
	WaitForFrame(0); // Frame 32
	Wait(1); // Why? Ig RestartGame messes with the RunHeader for a frame
	KeyPress(1, { VK_RETURN });
	WaitForFrame(2); // title screen
	Wait(3);
	ClickAt(new POINT(800, 450)); // Start
	WaitForFrame(3); // file setup
	Wait(30);
	ClickAt(new POINT(400, 150)); // Slot 1
	Wait(20);
	ClickAt(new POINT(400, 250)); // Continue
	WaitForFrame(4); // character select
	ClickAt(new POINT(700, 450)); // Done
	IncrementStage(); // PEARL_CHEST
#pragma endregion
	WaitForFrame(5); // character select
	KeyPress(10, { 'A' });
	KeyPress(180, { 'A', 'W' });
	KeyPress(300, { 'A' });
	KeyPressUntilFrame(34, { 'A', 'S' }); // halloween land
}

#pragma region KeyPress
void TAS::KeyPress(int timer, std::vector<char> keyCodes)
{
	Queue.push_back(new TASKeyPress(timer, keyCodes));
}

void TAS::KeyPressUntilFrame(int frame, std::vector<char> keyCodes)
{
	Queue.push_back(new TASKeyPressUntilFrame(frame, keyCodes));
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

void TAS::LoadTASSavestate()
{
	static std::string path = "C:\\Users\\Alone\\AppData\\Roaming\\MMFApplications\\fnafw";
	std::filesystem::copy_file((path + "tas").c_str(), (path + "1").c_str(), std::filesystem::copy_options::overwrite_existing);
}

void TAS::SaveTASSavestate()
{
	static std::string path = "C:\\Users\\Alone\\AppData\\Roaming\\MMFApplications\\fnafw";
	std::filesystem::copy_file((path + "tas").c_str(), (path + "1").c_str(), std::filesystem::copy_options::overwrite_existing);
}