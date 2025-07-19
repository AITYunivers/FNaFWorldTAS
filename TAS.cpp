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

#define FROMSTATE

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
	Wait(30);
	ClickAt(new POINT(400, 150)); // Slot 1
	Wait(20);
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
	IncrementStage(); // TWRE_DODGE_TO_AREA_5
	IncrementStage(); // PHANTOM_MANGLE_UNLOCK
	IncrementStage(); // WITHERED_BONNIE_UNLOCK
	IncrementStage(); // TWRE_DODGE_TO_AREA_6
	IncrementStage(); // TWRE_DODGE_TO_GEIST_1
	IncrementStage(); // JACK_O_BONNIE_UNLOCK
	IncrementStage(); // TWRE_DODGE_TO_GEIST_2
	IncrementStage(); // JACK_O_CHICA_UNLOCK
	IncrementStage(); // TWRE_DODGE_TO_GEIST_3
	IncrementStage(); // NIGHTMARE_BB_UNLOCK
	IncrementStage(); // TWRE_DODGE_TO_GEIST_4
	IncrementStage(); // NIGHTMARIONNE_UNLOCK
	IncrementStage(); // TWRE_DODGE_TO_GEIST_5
	IncrementStage(); // COFFEE_UNLOCK
	IncrementStage(); // TWRE_DODGE_TO_GEIST_6
	IncrementStage(); // PURPLE_GUY_UNLOCK
	IncrementStage(); // GOLD_ENDO_GRIND
	IncrementStage(); // PLUSHTRAP_UNLOCK
	IncrementStage(); // ENDOPLUSH_UNLOCK
	IncrementStage(); // SPRINGTRAP_UNLOCK
	IncrementStage(); // RXQ_UNLOCK
	IncrementStage(); // CRYING_CHILD_UNLOCK
	IncrementStage(); // FUNTIME_FOXY_UNLOCK
	IncrementStage(); // NIGHTMARE_FREDBEAR_UNLOCK
	IncrementStage(); // NIGHTMARE_UNLOCK
	IncrementStage(); // FREDBEAR_UNLOCK
	IncrementStage(); // SPRING_BONNIE_UNLOCK
	IncrementStage(); // FOURTH_GLITCH
	IncrementStage(); // AUTO_CHIPPER
	IncrementStage(); // WITHERED_CHICA_UNLOCK
	IncrementStage(); // WITHERED_FREDDY_UNLOCK
	IncrementStage(); // WITHERED_FOXY_UNLOCK
	IncrementStage(); // UNLOCK_AREAS_3_4
	IncrementStage(); // NIGHTMARE_FREDDY_UNLOCK
	IncrementStage(); // NIGHTMARE_BONNIE_UNLOCK
	IncrementStage(); // NIGHTMARE_CHICA_UNLOCK
	IncrementStage(); // NIGHTMARE_FOXY_UNLOCK
	IncrementStage(); // SHADOW_FREDDY_UNLOCK
	IncrementStage(); // MARIONETTE_UNLOCK
	IncrementStage(); // PHANTOM_MARIONETTE_UNLOCK
	IncrementStage(); // GOLDEN_FREDDY_UNLOCK
	IncrementStage(); // PAPERPALS_UNLOCK
	IncrementStage(); // ENDO_01_UNLOCK
	IncrementStage(); // ENDO_02_UNLOCK
	IncrementStage(); // TBD
#else
	WaitForFrame(5); // overworld
	JumpTo(1); // Tiny bit faster than walking directly
	KeyPress(68, { 'S', 'D' });
	JumpTo(1);
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
	JumpTo(1);
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
	JumpTo(1);
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
	IncrementStage(); // TWRE_DODGE_TO_AREA_5
	WaitForFrame(5); // overworld
	JumpTo(2);
	KeyPress(58, { 'S' });
	WaitForFrame(27); // cinematic
	KeyPress(2026, { VK_RETURN });
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
	KeyPress(15, { 'D', 'S', 'R' });
	KeyPress(75, { 'D', 'R' });
	KeyPress(79, { 'D', 'W', 'R' });
	JumpTo(1);
	IncrementStage(); // PHANTOM_MANGLE_UNLOCK
	KeyPress(82, { 'D', 'R' });
	Wait(161 + 2); // Annoying inconsistent, fix later
	ClickAttack(2, 3); // JJ -> Unscrew
	Wait(480 + 2); // Annoying inconsistent, fix later
	IncrementStage(); // WITHERED_BONNIE_UNLOCK
	KeyPress(350, { 'D', 'R' });
	KeyPress(119, { 'D', 'W', 'R' });
	KeyPress(194, { 'W', 'R' });
	Wait(161 + 2); // Annoying inconsistent, fix later
	ClickAttack(2, 3); // JJ -> Unscrew
	Wait(478 + 2); // Annoying inconsistent, fix later
	KeyPress(130, { 'W' });
	ClickAt(new POINT(200, 450)); // Chips
	KeyPress(1, { 'W' });
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
	IncrementStage(); // TWRE_DODGE_TO_AREA_6
	WaitForFrame(5); // overworld
	KeyPress(200, { 'A', 'S' });
	WaitForFrame(8); // underground 1
	KeyPress(230, { 'D', 'S' });
	KeyPress(100, { 'S' });
	KeyPress(540, { 'D', 'S' });
	KeyPress(150, { 'D', 'W' });
	KeyPress(32, { 'D' });
	KeyPress(90, { 'A', 'W' });
	KeyPress(35, { 'A' });
	WaitForFrame(10); // underground 2
	KeyPress(545, { 'A', 'S' });
	WaitForFrame(8); // underground 1
	KeyPress(200, { 'A', 'S' });
	KeyPress(100, { 'A', 'W' });
	KeyPress(14, { 'A' });
	WaitForFrame(5); // overworld
	KeyPress(60, { 'A' });
	JumpTo(2);
	KeyPress(58, { 'S' });
	KeyPress(15, { 'D', 'S' });
	KeyPress(75, { 'D' });
	KeyPress(77, { 'D', 'W' });
	JumpTo(5);
	KeyPress(10, { 'A' });
	KeyPress(340, { 'A', 'S' });
	KeyPress(360, { 'S' });
	ClickAt(new POINT(200, 450)); // Chips
	KeyPress(1, { 'S' });
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
	IncrementStage(); // TWRE_DODGE_TO_GEIST_1
	WaitForFrame(5); // overworld
	KeyPress(36, { 'S' });
	JumpTo(2);
	for (int i = 0; i < 6; i++)
	{
		KeyPress(58, { 'S' });
		KeyPress(15, { 'D', 'S' });
		KeyPress(75, { 'D' });
		KeyPress(77, { 'D', 'W' });
		JumpTo(6);
		KeyPress(70, { 'D', 'S' });
		KeyPress(1204, { 'D' });
		ClickAt(new POINT(200, 450)); // Chips
		KeyPress(1, { 'D' });
		WaitForFrame(7); // chips
		ClickAt(new POINT(700, 425)); // Done
		IncrementStage(); // CHARACTER_UNLOCK
		WaitForFrame(5); // overworld
		KeyPress(126, { 'D', 'R' });
		Wait(1); // Can't get an encounter if we run on the first frame
		KeyPress(1, { 'R' });
		JumpTo(2);
		Wait(165 + 2); // Annoying inconsistent, fix later
		ClickAttack(2, 3); // JJ -> Unscrew
		Wait(480 + 2); // Annoying inconsistent, fix later
		IncrementStage(); // TWRE_DODGE_TO_GEIST
	}
	KeyPress(58, { 'S' });
	KeyPress(15, { 'D', 'S' });
	KeyPress(75, { 'D' });
	KeyPress(77, { 'D', 'W' });
	JumpTo(5);
	KeyPress(10, { 'A' });
	KeyPress(105, { 'A', 'S' });
	KeyPress(200, { 'A' });
	KeyPress(30, { 'A', 'W' });
	KeyPress(320, { 'A' });
	ClickAt(new POINT(200, 450)); // Chips
	KeyPress(1, { 'A' });
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
	WaitForFrame(5); // overworld
	for (int i = 0; i < 31; i++)
	{
		Wait(72 + 2); // Annoying inconsistent, fix later
		ClickAttack(2, 3); // JJ -> Unscrew
		Wait(1103);
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
		WaitForFrame(5); // overworld
		Wait(62);
		ClickAt(new POINT(200, 450)); // Chips
		WaitForFrame(7); // chips
		ClickAt(new POINT(700, 425)); // Done
		WaitForFrame(5); // overworld
	}
	Wait(72 + 2); // Annoying inconsistent, fix later
	ClickAttack(2, 3); // JJ -> Unscrew
	Wait(1204);
	ClickAt(new POINT(200, 450)); // Chips
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
	IncrementStage(); // ENDO_01_UNLOCK
	for (int i = 0; i < 10; i++)
	{
		WaitForFrame(5); // overworld
		KeyPress(63, { 'A', 'R' });
		KeyPress(63, { 'D', 'R' });
		Wait(1); // Can't get an encounter if we run on the first frame
		KeyPress(1, { 'R' });
		Wait(165 + 2); // Annoying inconsistent, fix later
		ClickAttack(2, 3); // JJ -> Unscrew
		Wait(578 + 2); // Annoying inconsistent, fix later
		if (i == 9)
			break;
		ClickAt(new POINT(200, 450)); // Chips
		WaitForFrame(7); // chips
		ClickAt(new POINT(700, 425)); // Done
		IncrementStage(); // CHARACTER_UNLOCK
	}
	IncrementStage(); // FOURTH_GLITCH
	KeyPress(242, { 'D', 'S' });
	WaitForFrame(8); // underground 1
	KeyPress(165, { 'D', 'S' });
	KeyPress(130, { 'D' });
	KeyPress(175, { 'D', 'W' });
	KeyPress(68, { 'A', 'W' });
	WaitForFrame(10); // underground 2
	KeyPress(100, { 'W' });
	KeyPress(109, { 'D', 'W' });
	WaitForFrame(11); // underground 3
	KeyPress(730, { 'D', 'W' });
	KeyPress(125, { 'D', 'S' });
	KeyPress(597, { 'A', 'S' });
	WaitForFrame(15); // underground 3
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
	WaitForFrame(5); // overworld
	JumpTo(1);
	KeyPress(71, { 'D' });
	WaitForFrame(14); // armor shop
	ClickAt(new POINT(600, 100)); // Buy Titanium
	ClickAt(new POINT(700, 450)); // Exit Shop
	WaitForFrame(5); // overworld
	JumpTo(1);
	KeyPress(59, { 'A', 'W' });
	WaitForFrame(13); // shop
	ClickAt(new POINT(600, 100)); // Buy Neon Wasp
	ClickAt(new POINT(700, 450)); // Exit Shop
	IncrementStage(); // AUTO_CHIPPER
	WaitForFrame(5); // overworld
	JumpTo(1);
	KeyPress(30, { 'A' });
	KeyPress(140, { 'A', 'W' });
	KeyPress(269, { 'D', 'W' });
	Wait(69 + 2); // Annoying inconsistent, fix later
	ClickAttack(2, 3); // JJ -> Unscrew
	Wait(543 + 2); // Annoying inconsistent, fix later
	KeyPress(60, { 'A', 'W' });
	ClickAt(new POINT(200, 450)); // Chips
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
	WaitForFrame(5); // overworld
	KeyPress(225, { 'D', 'S' });
	ClickAt(new POINT(200, 450)); // Chips
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
	WaitForFrame(5); // overworld
	JumpTo(2);
	KeyPress(135, { 'A', 'S' });
	KeyPress(50, { 'A', 'W' });
	KeyPress(50, { 'W' });
	KeyPress(108, { 'A', 'W' });
	Wait(69 + 2); // Annoying inconsistent, fix later
	ClickAttack(2, 3); // JJ -> Unscrew
	Wait(568 + 2); // Annoying inconsistent, fix later
	KeyPress(27, { 'W' });
	ClickAt(new POINT(200, 450)); // Chips
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
	WaitForFrame(5); // overworld
	KeyPress(105, { 'D', 'S', 'R' });
	KeyPress(80, { 'A', 'S', 'R' });
	KeyPress(197, { 'A', 'R' });
	IncrementStage(); // WITHERED_CHICA_UNLOCK
	JumpTo(3);
	KeyPress(55, { 'A', 'W', 'R' });
	KeyPress(33, { 'A', 'R' });
	KeyPress(31, { 'A', 'W', 'R' });
	Wait(1); // Can't get an encounter if we run on the first frame
	KeyPress(1, { 'R' });
	Wait(165 + 2); // Annoying inconsistent, fix later
	ClickAttack(2, 3); // JJ -> Unscrew
	Wait(471 + 2); // Annoying inconsistent, fix later
	ClickAt(new POINT(200, 450)); // Chips
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
	IncrementStage(); // WITHERED_FREDDY_UNLOCK
	WaitForFrame(5); // overworld
	KeyPress(20, { 'A', 'W', 'R' });
	KeyPress(50, { 'W', 'R' });
	KeyPress(55, { 'D', 'W', 'R' });
	Wait(1); // Can't get an encounter if we run on the first frame
	KeyPress(1, { 'R' });
	Wait(165 + 2); // Annoying inconsistent, fix later
	ClickAttack(2, 3); // JJ -> Unscrew
	Wait(471 + 2); // Annoying inconsistent, fix later
	KeyPress(12, { 'D', 'W', 'R' });
	ClickAt(new POINT(200, 450)); // Chips
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
	IncrementStage(); // WITHERED_FOXY_UNLOCK
	WaitForFrame(5); // overworld
	JumpTo(3);
	KeyPress(112, { 'A', 'S', 'R' });
	KeyPress(14, { 'A', 'R' });
	Wait(1); // Can't get an encounter if we run on the first frame
	KeyPress(1, { 'R' });
	Wait(165 + 2); // Annoying inconsistent, fix later
	ClickAttack(2, 3); // JJ -> Unscrew
	Wait(471 + 2); // Annoying inconsistent, fix later
	IncrementStage(); // UNLOCK_AREAS_3_4
	KeyPress(165, { 'A', 'W' });
	KeyPress(20, { 'A' });
	KeyPress(50, { 'A', 'W' });
	KeyPress(129, { 'W' });
	WaitForFrame(13); // shop
	ClickAt(new POINT(200, 100)); // Buy Mini-Reaper
	Wait(1);
	ClickAt(new POINT(400, 100)); // Buy Reaper
	Wait(1);
	ClickAt(new POINT(600, 100)); // Buy X-Reaper
	ClickAt(new POINT(700, 450)); // Exit Shop
	WaitForFrame(12); // Bytes
	Wait(20);
	ClickAt(new POINT(200, 200)); // Equip X-Reaper
	ClickAt(new POINT(700, 425)); // Exit Bytes Menu
	WaitForFrame(5); // overworld
	KeyPress(10, { 'D', 'S' });
	KeyPress(20, { 'D' });
	KeyPress(45, { 'D', 'S' });
	KeyPress(41, { 'A', 'S' });
	WaitForFrame(28); // clock
	KeyPress(20, { 'D', 'S' });
	KeyPress(149, { 'D' });
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
	WaitForFrame(5); // overworld
	KeyPress(113, { 'D', 'W' });
	KeyPress(63, { 'W' });
	WaitForFrame(27); // cinematic
	KeyPress(1627, { VK_RETURN });
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
	WaitForFrame(5); // overworld
	JumpTo(2);
	KeyPress(58, { 'S' });
	KeyPress(15, { 'D', 'S' });
	KeyPress(75, { 'D' });
	KeyPress(77, { 'D', 'W' });
	JumpTo(1);
	KeyPress(300, { 'D' });
	KeyPress(70, { 'D', 'W' });
	ClickAt(new POINT(200, 450)); // Chips
	KeyPress(1, { 'D' });
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
	WaitForFrame(5); // overworld
	KeyPress(14, { 'D' });
	KeyPress(87, { 'A', 'S' });
	ClickAt(new POINT(200, 450)); // Chips
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
	WaitForFrame(5); // overworld
	JumpTo(4);
	KeyPress(20, { 'A' });
	KeyPress(40, { 'A', 'S' });
	KeyPress(60, { 'S' });
	KeyPress(52, { 'A', 'S' });
	KeyPress(40, { 'A' });
	KeyPress(31, { 'A', 'S' });
	ClickAt(new POINT(200, 450)); // Chips
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
	WaitForFrame(5); // overworld
	KeyPress(10, { 'D', 'W' });
	KeyPress(118, { 'D', 'S' });
	WaitForFrame(13); // shop
	ClickAt(new POINT(200, 100)); // Buy Medpod 1
	Wait(1);
	ClickAt(new POINT(400, 100)); // Buy Medpod 2
	Wait(1);
	ClickAt(new POINT(600, 100)); // Buy Mega-Med
	ClickAt(new POINT(700, 450)); // Exit Shop
	WaitForFrame(12); // Bytes
	ClickAt(new POINT(700, 425)); // Exit Bytes Menu
	WaitForFrame(5); // overworld
	JumpTo(2);
	KeyPress(58, { 'S' });
	KeyPress(15, { 'D', 'S' });
	KeyPress(75, { 'D' });
	KeyPress(77, { 'D', 'W' });
	JumpTo(3);
	KeyPress(188, { 'D', 'W' });
	JumpTo(4);
	Wait(150);
	KeyPress(18, { 'D', 'S' });
	KeyPress(235, { 'D', 'W' });
	KeyPress(15, { 'D' });
	JumpTo(4);
	Wait(150);
	KeyPress(135, { 'D', 'S' });
	KeyPress(74, { 'S' });
	ClickAt(new POINT(200, 450)); // Chips
	KeyPress(1, { 'S' });
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
	WaitForFrame(5); // overworld
	JumpTo(2);
	KeyPress(58, { 'S' });
	KeyPress(15, { 'D', 'S' });
	KeyPress(75, { 'D' });
	KeyPress(77, { 'D', 'W' });
	JumpTo(6);
	KeyPress(234, { 'D', 'W' });
	ClickAt(new POINT(200, 450)); // Chips
	KeyPress(1, { 'D', 'W' });
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
	WaitForFrame(5); // overworld
	KeyPress(840, { 'A', 'W' });
	ClickAt(new POINT(200, 450)); // Chips
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
	WaitForFrame(5); // overworld
	JumpTo(6);
	KeyPress(65, { 'A', 'W' });
	WaitForFrame(13); // shop
	ClickAt(new POINT(200, 100)); // Buy Mini-FO
	Wait(1);
	ClickAt(new POINT(400, 100)); // Buy UFO
	Wait(1);
	ClickAt(new POINT(600, 100)); // Buy X-FO
	ClickAt(new POINT(700, 450)); // Exit Shop
	WaitForFrame(12); // Bytes
	ClickAt(new POINT(700, 425)); // Exit Bytes Menu
	WaitForFrame(5); // overworld
	JumpTo(2);
	KeyPress(58, { 'S' });
	KeyPress(15, { 'D', 'S' });
	KeyPress(75, { 'D' });
	KeyPress(77, { 'D', 'W' });
	JumpTo(6);
	KeyPress(277, { 'A', 'W' });
	ClickAt(new POINT(200, 450)); // Chips
	KeyPress(1, { 'A', 'W' });
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
	WaitForFrame(5); // overworld
	KeyPress(712, { 'A', 'W' });
	ClickAt(new POINT(200, 450)); // Chips
	KeyPress(1, { 'W' });
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
	IncrementStage(); // NIGHTMARE_FREDDY_UNLOCK
	WaitForFrame(5); // overworld
	JumpTo(5);
	KeyPress(20, { 'S', 'R' });
	KeyPress(106, { 'D', 'S', 'R' });
	Wait(1); // Can't get an encounter if we run on the first frame
	KeyPress(1, { 'R' });
	Wait(644);
	ClickAt(new POINT(200, 450)); // Chips
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
	IncrementStage(); // NIGHTMARE_BONNIE_UNLOCK
	WaitForFrame(5); // overworld
	KeyPress(50, { 'S', 'R' });
	KeyPress(76, { 'A', 'S', 'R' });
	Wait(1); // Can't get an encounter if we run on the first frame
	KeyPress(1, { 'R' });
	Wait(651);
	ClickAt(new POINT(200, 450)); // Chips
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
	IncrementStage(); // NIGHTMARE_CHICA_UNLOCK
	WaitForFrame(5); // overworld
	KeyPress(104, { 'A', 'S', 'R' });
	ClickAt(new POINT(200, 450)); // Chips
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
	WaitForFrame(5); // overworld
	KeyPress(125, { 'D', 'W', 'R' });
	Wait(1); // Can't get an encounter if we run on the first frame
	KeyPress(1, { 'R' });
	Wait(651);
	ClickAt(new POINT(200, 450)); // Chips
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
	IncrementStage(); // NIGHTMARE_FOXY_UNLOCK
	WaitForFrame(5); // overworld
	KeyPress(126, { 'D', 'R' });
	Wait(1); // Can't get an encounter if we run on the first frame
	KeyPress(1, { 'R' });
	Wait(640);
	ClickAt(new POINT(200, 450)); // Chips
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
	IncrementStage(); // SHADOW_FREDDY_UNLOCK
	WaitForFrame(5); // overworld
	KeyPress(86, { 'D', 'W' });
	WaitForFrame(13); // shop
	ClickAt(new POINT(200, 100)); // Buy Pop-Pop
	Wait(1);
	ClickAt(new POINT(400, 100)); // Buy BOOM
	Wait(1);
	ClickAt(new POINT(600, 100)); // Buy KABOOM
	ClickAt(new POINT(700, 450)); // Exit Shop
	WaitForFrame(12); // Bytes
	ClickAt(new POINT(700, 425)); // Exit Bytes Menu
	WaitForFrame(5); // overworld
	KeyPress(60, { 'S', 'R' });
	KeyPress(66, { 'A', 'S', 'R' });
	Wait(1); // Can't get an encounter if we run on the first frame
	KeyPress(1, { 'R' });
	Wait(648);
	ClickAt(new POINT(200, 450)); // Chips
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
	IncrementStage(); // MARIONETTE_UNLOCK
	WaitForFrame(5); // overworld
	KeyPress(14, { 'A', 'S', 'R' });
	KeyPress(55, { 'A', 'W', 'R' });
	KeyPress(57, { 'A', 'S', 'R' });
	Wait(1); // Can't get an encounter if we run on the first frame
	KeyPress(1, { 'R' });
	Wait(648);
	ClickAt(new POINT(200, 450)); // Chips
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
	IncrementStage(); // PHANTOM_MARIONETTE_UNLOCK
	WaitForFrame(5); // overworld
	KeyPress(50, { 'D', 'S', 'R' });
	KeyPress(76, { 'D', 'W', 'R' });
	Wait(1); // Can't get an encounter if we run on the first frame
	KeyPress(1, { 'R' });
	Wait(662);
	ClickAt(new POINT(200, 450)); // Chips
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
	IncrementStage(); // GOLDEN_FREDDY_UNLOCK
	WaitForFrame(5); // overworld
	KeyPress(60, { 'D', 'S', 'R' });
	KeyPress(66, { 'A', 'S', 'R' });
	Wait(1); // Can't get an encounter if we run on the first frame
	KeyPress(1, { 'R' });
	Wait(662);
	ClickAt(new POINT(200, 450)); // Chips
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
	IncrementStage(); // PAPERPALS_UNLOCK
	WaitForFrame(5); // overworld
	KeyPress(126, { 'A', 'W', 'R' });
	Wait(1); // Can't get an encounter if we run on the first frame
	KeyPress(1, { 'R' });
	Wait(662);
	ClickAt(new POINT(200, 450)); // Chips
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
	IncrementStage(); // ENDO_01_UNLOCK
	WaitForFrame(5); // overworld
	KeyPress(126, { 'A', 'W', 'R' });
	Wait(1); // Can't get an encounter if we run on the first frame
	KeyPress(1, { 'R' });
	Wait(662);
	ClickAt(new POINT(200, 450)); // Chips
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
	IncrementStage(); // ENDO_02_UNLOCK
	WaitForFrame(5); // overworld
	KeyPress(126, { 'A', 'W', 'R' });
	Wait(1); // Can't get an encounter if we run on the first frame
	KeyPress(1, { 'R' });
	Wait(662);
	ClickAt(new POINT(200, 450)); // Chips
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
	IncrementStage(); // TBD
	WaitForFrame(5); // overworld
	KeyPress(73, { 'D', 'W' });
	WaitForFrame(13); // shop
	ClickAt(new POINT(200, 100)); // Buy BossDrain01
	Wait(1);
	ClickAt(new POINT(400, 100)); // Buy BossDrain02
	Wait(1);
	ClickAt(new POINT(600, 100)); // Buy BossDrain-X
	ClickAt(new POINT(700, 450)); // Exit Shop
	WaitForFrame(12); // Bytes
	ClickAt(new POINT(700, 425)); // Exit Bytes Menu
	WaitForFrame(5); // overworld
	JumpTo(2);
	KeyPress(58, { 'S' });
	KeyPress(15, { 'D', 'S' });
	KeyPress(75, { 'D' });
	KeyPress(77, { 'D', 'W' });
	JumpTo(5);
	KeyPress(10, { 'A' });
	KeyPress(238, { 'A', 'S' });
	ClickAt(new POINT(200, 450)); // Chips
	KeyPress(1, { 'S' });
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
	WaitForFrame(5); // overworld
	Wait(1);
	ClickAt(new POINT(200, 450)); // Chips
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
	WaitForFrame(5); // overworld
	JumpTo(2);
	KeyPress(58, { 'S' });
	KeyPress(15, { 'D', 'S' });
	KeyPress(75, { 'D' });
	KeyPress(77, { 'D', 'W' });
	JumpTo(5);
	KeyPress(10, { 'A' });
	KeyPress(230, { 'A', 'S' });
	KeyPress(44, { 'A' });
	ClickAt(new POINT(200, 450)); // Chips
	KeyPress(1, { 'A' });
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
	WaitForFrame(5); // overworld
	Wait(1);
	ClickAt(new POINT(200, 450)); // Chips
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
	WaitForFrame(5); // overworld
	JumpTo(2);
	KeyPress(58, { 'S' });
	KeyPress(15, { 'D', 'S' });
	KeyPress(75, { 'D' });
	KeyPress(77, { 'D', 'W' });
	JumpTo(5);
	KeyPress(10, { 'A' });
	KeyPress(120, { 'A', 'S' });
	KeyPress(108, { 'A', 'W' });
	KeyPress(121, { 'A' });
	ClickAt(new POINT(200, 450)); // Chips
	KeyPress(1, { 'A' });
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
	WaitForFrame(5); // overworld
	Wait(1);
	ClickAt(new POINT(200, 450)); // Chips
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
#endif
	WaitForFrame(5); // overworld
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

void TAS::JumpTo(int area)
{
	ClickAt(new POINT(750, 50 * area));
}