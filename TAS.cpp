#include "TAS.h"
#include "TASKeyPress.h"
#include "TASClickAt.h"
#include "TASWait.h"
#include "TASWaitForFrame.h"
#include "TASRestartGame.h"
#include "TASIncrementStage.h"
#include <filesystem>

#pragma region Static Variables
bool TAS::running = false;
unsigned int TAS::oldLoopCount = false;
unsigned int TAS::oldFrame = false;
TAS::Stage TAS::stage = TAS::Stage::START;

std::deque<TASEvent*> TAS::Queue;

POINT* TAS::mousePos = nullptr;
#pragma endregion

//#define FROMSTATE

void TAS::Run()
{
	CRunApp* app = GetCRunApp();
	running = true;
#ifdef FROMSTATE
	LoadTASSave();
	WaitForFrame(0); // Frame 32
#else
	WaitForFrame(0); // Frame 32
	KeyPress(1, { VK_RETURN });
	WaitForFrame(2); // title screen
	Wait(3);
	ClickAt(new POINT(800, 450)); // Start
	WaitForFrame(3); // file setup
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
	WaitForFrame(4); // character select
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
	WaitForFrame(27); // cinematic
	Wait(1); // LiveSplit is slow, might start using a websocket later
	RestartGame();
	WaitForFrame(0); // Frame 32
	Wait(1); // Why? Ig RestartGame messes with the RunHeader for a frame
#endif
	KeyPress(1, { VK_RETURN });
	WaitForFrame(2); // title screen
	Wait(3);
	ClickAt(new POINT(800, 450)); // Start
	WaitForFrame(3); // file setup
	Wait(29);
	ClickAt(new POINT(400, 150)); // Slot 1
	Wait(19);
	ClickAt(new POINT(400, 250)); // Continue
	WaitForFrame(4); // character select
	ClickAt(new POINT(700, 450)); // Done
	IncrementStage(); // PEARL_CHEST 
#ifdef FROMSTATE
	IncrementStage(); // JJ_UNLOCK
	IncrementStage(); // BB_UNLOCK
	IncrementStage(); // PHANTOM_FREDDY_UNLOCK
	IncrementStage(); // PHANTOM_CHICA_UNLOCK
	IncrementStage(); // PHANTOM_BB_UNLOCK
	IncrementStage(); // PHANTOM_FOXY_UNLOCK
	IncrementStage(); // PHANTOM_MANGLE_UNLOCK
#else
	WaitForFrame(5); // overworld
	ClickAt(new POINT(750, 50)); // Jump to 1, tiny bit faster than walking directly
	KeyPress(68, { 'S', 'D' });
	ClickAt(new POINT(750, 50)); // Jump to 1
	KeyPress(65, { 'W' });
	KeyPress(21, { 'W', 'D' });
	WaitForFrame(18); // fishing 1
	ClickAt(new POINT(600, 100)); // Play Deedee's Fishing Hole
	WaitForFrame(19); // fishing 2
	KeyPress(1, { 'D' });
	KeyPress(1, { 'S' });
	IncrementStage(); // JJ_UNLOCK
	WaitForFrame(5); // overworld
	KeyPress(10, { 'A', 'S' });
	KeyPress(20, { 'A' });
	Wait(30);
	KeyPress(10, { 'A' });
	WaitForFrame(13); // shop
	Wait(1);
	ClickAt(new POINT(200, 100)); // Buy Gnat
	ClickAt(new POINT(400, 100)); // Buy Neon Bee
	ClickAt(new POINT(700, 450)); // Exit Shop
	WaitForFrame(12); // Bytes
	Wait(20);
	ClickAt(new POINT(100, 100)); // Equip Gnat
	Wait(9);
	ClickAt(new POINT(200, 100)); // Equip Neon Bee
	ClickAt(new POINT(700, 425)); // Exit Bytes Menu
	WaitForFrame(5); // overworld
	ClickAt(new POINT(750, 50)); // Jump to 1
	KeyPress(30, { 'A' });
	KeyPress(94, { 'A', 'W' });
	Wait(73);
	ClickAttack(2, 3); // Mangle -> Prize Ball
	Wait(686);
	ClickAttack(2, 3); // Mangle -> Prize Ball
	KeyPress(1, { 'R' });
	Wait(186);
	ClickAttack(2, 3); // Mangle -> Prize Ball
	Wait(61);
	ClickAttack(3, 3); // Toy Chica -> Waterhose
	Wait(413 + 18); // Annoying inconsistent, fix later
	ClickAt(new POINT(100, 450)); // Party
	WaitForFrame(4); // character select
	Wait(11);
	ClickCharacter(8, 1); // Mangle
	Wait(10);
	ClickCharacter(2, 2); // JJ
	ClickAt(new POINT(700, 450)); // Done
	IncrementStage(); // BB_UNLOCK
	WaitForFrame(5); // overworld
	KeyPress(60, { 'A', 'W', 'R' }); // Holding 'R' to initialize the timer for instant running
	KeyPress(65, { 'A', 'S', 'R' }); // Ditto
	Wait(1); // Can't get an encounter if we run on the first frame
	KeyPress(1, { 'R' });
	Wait(161 + 2); // Annoying inconsistent, fix later
	ClickAttack(2, 3); // JJ -> Unscrew
	Wait(466 + 2); // Annoying inconsistent, fix later
	ClickAt(new POINT(200, 450)); // Chips
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
	IncrementStage(); // PHANTOM_FREDDY_UNLOCK
	WaitForFrame(5); // overworld
	KeyPress(25, { 'A', 'S', 'R' }); // Holding 'R' to initialize the timer for instant running
	KeyPress(30, { 'S', 'R' });      // Ditto
	KeyPress(70, { 'A', 'S', 'R' }); // Ditto
	Wait(1); // Can't get an encounter if we run on the first frame
	KeyPress(1, { 'R' });
	Wait(161 + 2); // Annoying inconsistent, fix later
	ClickAttack(2, 3); // JJ -> Unscrew
	Wait(466 + 2); // Annoying inconsistent, fix later
	ClickAt(new POINT(200, 450)); // Chips
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
	IncrementStage(); // PHANTOM_CHICA_UNLOCK
	WaitForFrame(5); // overworld
	KeyPress(58, { 'A', 'S' });
	WaitForFrame(27); // cinematic
	KeyPress(1926, { VK_RETURN });
	RestartGame();
	WaitForFrame(0); // Frame 32
	Wait(1); // Why? Ig RestartGame messes with the RunHeader for a frame
	KeyPress(1, { VK_RETURN });
	WaitForFrame(2); // title screen
	Wait(3);
	ClickAt(new POINT(800, 450)); // Start
	WaitForFrame(3); // file setup
	Wait(29);
	ClickAt(new POINT(400, 150)); // Slot 1
	Wait(19);
	ClickAt(new POINT(400, 250)); // Continue
	WaitForFrame(4); // character select
	ClickAt(new POINT(700, 450)); // Done
	WaitForFrame(5); // overworld
	KeyPress(55, { 'A', 'S' });
	WaitForFrame(8); // underground 1
	KeyPress(363, { 'D', 'S' });
	KeyPress(80, { 'D' });
	KeyPress(120, { 'D', 'S' });
	KeyPress(100, { 'S' });
	KeyPress(80, { 'D', 'S' });
	WaitForFrame(5); // overworld
	KeyPress(35, { 'A', 'R' });
	ClickAt(new POINT(750, 50)); // Jump to 1
	KeyPress(45, { 'D', 'S', 'R' });
	KeyPress(46, { 'D', 'R' });
	Wait(1); // Can't get an encounter if we run on the first frame
	KeyPress(1, { 'R' });
	Wait(161 + 2); // Annoying inconsistent, fix later
	ClickAttack(2, 3); // JJ -> Unscrew
	Wait(466 + 2); // Annoying inconsistent, fix later
	ClickAt(new POINT(200, 450)); // Chips
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
	IncrementStage(); // PHANTOM_BB_UNLOCK
	WaitForFrame(5); // overworld
	KeyPress(39, { 'D', 'R' });
	KeyPress(45, { 'D', 'W', 'R' });
	KeyPress(41, { 'D', 'S', 'R' });
	Wait(1); // Can't get an encounter if we run on the first frame
	KeyPress(1, { 'R' });
	Wait(161 + 2); // Annoying inconsistent, fix later
	ClickAttack(2, 3); // JJ -> Unscrew
	Wait(466 + 2); // Annoying inconsistent, fix later
	ClickAt(new POINT(200, 450)); // Chips
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
	IncrementStage(); // PHANTOM_FOXY_UNLOCK
	WaitForFrame(5); // overworld
	KeyPress(114, { 'D', 'S', 'R' });
	KeyPress(11, { 'A', 'S', 'R' });
	Wait(1); // Can't get an encounter if we run on the first frame
	KeyPress(1, { 'R' });
	Wait(161 + 2); // Annoying inconsistent, fix later
	ClickAttack(2, 3); // JJ -> Unscrew
	Wait(466 + 2); // Annoying inconsistent, fix later
	KeyPress(16, { 'A', 'S' });
	KeyPress(42, { 'A', 'W' });
	WaitForFrame(28); // clock
	KeyPress(75, { 'A', 'W' });
	KeyPress(50, { 'A' });
	KeyPress(13, { 'A', 'W'});
	RestartGame();
	WaitForFrame(0); // Frame 32
	Wait(1); // Why? Ig RestartGame messes with the RunHeader for a frame
	KeyPress(1, { VK_RETURN });
	WaitForFrame(2); // title screen
	Wait(3);
	ClickAt(new POINT(800, 450)); // Start
	WaitForFrame(3); // file setup
	Wait(29);
	ClickAt(new POINT(400, 150)); // Slot 1
	Wait(19);
	ClickAt(new POINT(400, 250)); // Continue
	WaitForFrame(4); // character select
	ClickAt(new POINT(700, 450)); // Done
	IncrementStage(); // PHANTOM_MANGLE_UNLOCK
#endif
	WaitForFrame(5); // overworld
	ClickAt(new POINT(750, 100)); // Jump to 2
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

void TAS::LoadTASSave()
{
	static std::string path = "C:\\Users\\Alone\\AppData\\Roaming\\MMFApplications\\fnafw";
	std::filesystem::copy_file((path + "tas").c_str(), (path + "1").c_str(), std::filesystem::copy_options::overwrite_existing);
}