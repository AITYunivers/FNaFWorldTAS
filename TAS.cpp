#include "TAS.h"
#include "TASKeyPress.h"
#include "TASClickAt.h"
#include "TASWait.h"
#include "TASWaitForFrame.h"
#include "TASRestartGame.h"
#include "TASIncrementStage.h"
#include "TASWaitForDeedee.h"
#include "TASWaitForAttacksReady.h"
#include "TASWaitForVictory.h"
#include "TASWaitUntilChipsBtn.h"
#include "TASWaitForBattleEnd.h"
#include "TASWaitForCinematicEnd.h"
#include "TASWaitForTokens.h"
#include "TASKeyPressUntilFrame.h"
#include "TASKeyPressUntilBattle.h"
#include "TASKeyPressUntilChip.h"
#include <filesystem>

#pragma region Static Variables
bool TAS::running = false;
unsigned int TAS::oldLoopCount = false;
unsigned int TAS::oldFrame = false;
RunObject* TAS::foundchip = NULL;
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
	LoadTASSave();
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
	ClickAt(new POINT(700, 400)); // Reset
	Wait(11);
	ClickCharacter(1, 1); // Freddy
	Wait(11);
	ClickCharacter(8, 1); // Mangle
	Wait(11);
	ClickCharacter(6, 1); // Toy Chica
	Wait(11);
	ClickCharacter(2, 1); // Bonnie
	Wait(11);
	ClickCharacter(5, 1); // Toy Bonnie
	Wait(11);
	ClickCharacter(7, 1); // Toy Freddy
	Wait(11);
	ClickCharacter(3, 1); // Chica
	Wait(11);
	ClickCharacter(4, 1); // Foxy
	Wait(1);
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
#pragma region Pearl 1
	WaitForFrame(5); // overworld
	JumpTo(1); // Tiny bit faster than walking directly
	KeyPress(68, { 'S', 'D' });
	JumpTo(1);
	KeyPress(65, { 'W' });
	KeyPressUntilFrame(18, { 'W', 'D' }); // fishing 1
	ClickAt(new POINT(600, 100)); // Play Deedee's Fishing Hole
	WaitForFrame(19); // fishing 2
	KeyPress(1, { 'D' });
	KeyPress(1, { 'S' });
	WaitForFrame(5); // overworld
#pragma endregion
#pragma region Lolbit - Bees
	KeyPress(10, { 'A', 'S' });
	KeyPress(20, { 'A' });
	Wait(30);
	KeyPressUntilFrame(13, { 'A' }); // shop
	Wait(1);
	ClickAt(new POINT(200, 100)); // Buy Gnat
	Wait(1);
	ClickAt(new POINT(400, 100)); // Buy Neon Bee
	ClickAt(new POINT(700, 450)); // Exit Shop
	WaitForFrame(12); // Bytes
	Wait(20);
	ClickAt(new POINT(100, 100)); // Equip Gnat
	Wait(10);
	ClickAt(new POINT(200, 100)); // Equip Neon Bee
	ClickAt(new POINT(700, 425)); // Exit Bytes Menu
	WaitForFrame(5); // overworld
	IncrementStage(); // FREDDY_LV_4
#pragma endregion
#pragma region Unlock JJ
	JumpTo(1);
	KeyPress(30, { 'A' });
	KeyPressUntilBattle({ 'A', 'W' });
	WaitForAttacksReady();
	ClickAttack(2, 3); // Mangle -> Prize Ball
	WaitForVictory();
	IncrementStage(); // JJ_UNLOCK
	WaitForAttacksReady();
	ClickAttack(2, 3); // Mangle -> Prize Ball
	KeyPress(1, { 'R' });
	WaitForAttacksReady();
	ClickAttack(2, 3); // Mangle -> Prize Ball
	WaitForAttacksReady();
	ClickAttack(3, 3); // Toy Chica -> Waterhose
	WaitUntilChipsBtn();
	ClickAt(new POINT(100, 450)); // Party
	WaitForFrame(4); // character select
	Wait(12);
	ClickCharacter(8, 1); // Mangle
	Wait(11);
	ClickCharacter(2, 2); // JJ
	ClickAt(new POINT(700, 450)); // Done
#pragma endregion
#pragma region Unlock Balloon Boy
	IncrementStage(); // BB_UNLOCK
	WaitForFrame(5); // overworld
	KeyPress(60, { 'A', 'W', 'R' }); // Holding 'R' to initialize the timer for instant running
	KeyPressUntilBattle({ 'A', 'S', 'R' }); // Ditto
	KeyPress(1, { 'R' });
	WaitForAttacksReady();
	ClickAttack(2, 3); // JJ -> Unscrew
	WaitUntilChipsBtn();
	ClickAt(new POINT(200, 450)); // Chips
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
#pragma endregion
#pragma region Unlock Phantom Freddy
	IncrementStage(); // PHANTOM_FREDDY_UNLOCK
	WaitForFrame(5); // overworld
	KeyPress(25, { 'A', 'S', 'R' }); // Holding 'R' to initialize the timer for instant running
	KeyPress(30, { 'S', 'R' });      // Ditto
	KeyPressUntilBattle({ 'A', 'S', 'R' }); // Ditto
	KeyPress(1, { 'R' });
	WaitForAttacksReady();
	ClickAttack(2, 3); // JJ -> Unscrew
	WaitForBattleEnd();
#pragma endregion
#pragma region Cinematic - 1st Clock
	IncrementStage(); // PHANTOM_CHICA_UNLOCK
	KeyPressUntilFrame(27, { 'A', 'S' }); // cinematic
	KeyPress(1500, { VK_RETURN });
	WaitForCinematicEnd();
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
#pragma endregion
#pragma region Unlock Warp 2
	WaitForFrame(5); // overworld
	KeyPressUntilFrame(8, { 'A', 'S' }); // underground 1
	KeyPress(363, { 'D', 'S' });
	KeyPress(51, { 'D' });
	KeyPress(149, { 'D', 'S' });
	KeyPress(40, { 'S' });
	KeyPressUntilFrame(5, { 'D', 'S' }); // overworld
#pragma endregion
#pragma region Unlock Phantom Chica
	KeyPress(35, { 'A', 'R' });
	JumpTo(1);
	KeyPress(45, { 'D', 'S', 'R' });
	KeyPressUntilBattle({ 'D', 'R' });
	KeyPress(1, { 'R' });
	WaitForAttacksReady();
	ClickAttack(2, 3); // JJ -> Unscrew
	WaitUntilChipsBtn();
	ClickAt(new POINT(200, 450)); // Chips
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
#pragma endregion
#pragma region Unlock Phantom Balloon Boy
	IncrementStage(); // PHANTOM_BB_UNLOCK
	WaitForFrame(5); // overworld
	KeyPress(39, { 'D', 'R' });
	KeyPress(45, { 'D', 'W', 'R' });
	KeyPressUntilBattle({ 'D', 'S', 'R' });
	KeyPress(1, { 'R' });
	WaitForAttacksReady();
	ClickAttack(2, 3); // JJ -> Unscrew
	WaitUntilChipsBtn();
	ClickAt(new POINT(200, 450)); // Chips
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
#pragma endregion
#pragma region Unlock Phantom Foxy
	IncrementStage(); // PHANTOM_FOXY_UNLOCK
	WaitForFrame(5); // overworld
	KeyPress(114, { 'D', 'S', 'R' });
	KeyPressUntilBattle({ 'A', 'S', 'R' });
	KeyPress(1, { 'R' });
	WaitForAttacksReady();
	ClickAttack(2, 3); // JJ -> Unscrew
	WaitForBattleEnd();
#pragma endregion
#pragma region 1st Clock
	KeyPress(16, { 'A', 'S' });
	KeyPressUntilFrame(28, { 'A', 'W' }); // clock
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
	Wait(30);
	ClickAt(new POINT(400, 150)); // Slot 1
	Wait(20);
	ClickAt(new POINT(400, 250)); // Continue
	WaitForFrame(4); // character select
	ClickAt(new POINT(700, 450)); // Done
	IncrementStage(); // TWRE_DODGE_TO_AREA_5
#pragma endregion
#pragma region Cinematic - Clock 2
	WaitForFrame(5); // overworld
	JumpTo(2);
	KeyPressUntilFrame(27, { 'S' }); // cinematic
	KeyPress(1900, { VK_RETURN });
	WaitForCinematicEnd();
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
#pragma endregion
#pragma region TWRE Dodge toward Area 5
	WaitForFrame(5); // overworld
	KeyPress(10, { 'D', 'S', 'R' });
	KeyPress(81, { 'D', 'R' });
	KeyPress(76, { 'D', 'W', 'R' });
	JumpTo(1);
#pragma endregion
#pragma region Unlock Phantom Mangle
	IncrementStage(); // PHANTOM_MANGLE_UNLOCK
	KeyPressUntilBattle({ 'D', 'R' });
	KeyPress(1, { 'R' });
	WaitForAttacksReady();
	ClickAttack(2, 3); // JJ -> Unscrew
	WaitForBattleEnd();
#pragma endregion
#pragma region Unlock Withered Bonnie
	IncrementStage(); // WITHERED_BONNIE_UNLOCK
	KeyPress(350, { 'D', 'R' });
	KeyPressUntilBattle({ 'D', 'W', 'R' });
	KeyPress(70, { 'R' });
	WaitForAttacksReady();
	ClickAttack(2, 3); // JJ -> Unscrew
	WaitForBattleEnd();
#pragma endregion
#pragma region Chip - Auto: Shield
	IncrementStage(); // TWRE_DODGE_TO_AREA_6
	KeyPressUntilChip({ 'D', 'W' });
	KeyPress(240, { 'W', 'A' });
	KeyPress(90, { 'A' });
	WaitForDeedee();
	ClickAt(new POINT(200, 450)); // Chips
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
#pragma endregion
#pragma region Pearl 2
	WaitForFrame(5); // overworld
	KeyPressUntilFrame(8, { 'A', 'S' }); // underground 1
	KeyPress(230, { 'D', 'S' });
	KeyPress(100, { 'S' });
	KeyPress(540, { 'D', 'S' });
	KeyPress(150, { 'D', 'W' });
	KeyPress(32, { 'D' });
	KeyPress(90, { 'A', 'W' });
	KeyPressUntilFrame(10, { 'A' }); // underground 2
	KeyPressUntilFrame(8, { 'A', 'S' }); // underground 1
	KeyPress(200, { 'A', 'S' });
	KeyPress(100, { 'A', 'W' });
	KeyPressUntilFrame(5, { 'A' }); // overworld
	KeyPress(60, { 'A' });
	JumpTo(1);
	KeyPress(65, { 'W' });
	KeyPressUntilFrame(18, { 'W', 'D' }); // fishing 1
	ClickAt(new POINT(600, 100)); // Play Deedee's Fishing Hole
	WaitForFrame(19); // fishing 2
	KeyPress(1, { 'D' });
	KeyPress(1, { 'S' });
	WaitForFrame(5); // overworld
#pragma endregion
#pragma region TWRE Dodge to Area 6
	JumpTo(2);
	KeyPress(58, { 'S' });
	KeyPress(15, { 'D', 'S' });
	KeyPress(75, { 'D' });
	KeyPress(77, { 'D', 'W' });
	JumpTo(5);
	KeyPress(10, { 'A' });
	KeyPress(339, { 'A', 'S' });
	ClickAt(new POINT(200, 450)); // Chips
	KeyPress(1, { 'A', 'S' });
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
#pragma endregion
#pragma region Unlock Plushtrap
	IncrementStage(); // PLUSHTRAP_UNLOCK
	WaitForFrame(5); // overworld
	KeyPressUntilBattle({ 'D', 'S', 'R' });
	KeyPress(1, { 'R' });
	WaitForAttacksReady();
	ClickAttack(2, 3); // JJ -> Unscrew
	WaitUntilChipsBtn();
	ClickAt(new POINT(200, 450)); // Chips
	KeyPress(1, { 'S' });
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
#pragma endregion
#pragma region Unlock Endoplush
	IncrementStage(); // ENDOPLUSH_UNLOCK
	WaitForFrame(5); // overworld
	KeyPressUntilBattle({ 'A', 'S', 'R' });
	KeyPress(1, { 'R' });
	WaitForAttacksReady();
	ClickAttack(2, 3); // JJ -> Unscrew
	WaitUntilChipsBtn();
	ClickAt(new POINT(200, 450)); // Chips
	KeyPress(1, { 'S' });
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
#pragma endregion
#pragma region Unlock Springtrap
	IncrementStage(); // SPRINGTRAP_UNLOCK
	WaitForFrame(5); // overworld
	KeyPress(30, { 'A', 'S', 'R' });
	KeyPressUntilBattle({ 'D', 'S', 'R' });
	KeyPress(1, { 'R' });
	WaitForAttacksReady();
	ClickAttack(2, 3); // JJ -> Unscrew
	WaitUntilChipsBtn();
	ClickAt(new POINT(200, 450)); // Chips
	KeyPress(1, { 'S' });
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
#pragma endregion
#pragma region Unlock RXQ
	IncrementStage(); // RXQ_UNLOCK
	WaitForFrame(5); // overworld
	KeyPressUntilBattle({ 'D', 'S', 'R' });
	KeyPress(1, { 'R' });
	WaitForAttacksReady();
	ClickAttack(2, 3); // JJ -> Unscrew
	WaitUntilChipsBtn();
	ClickAt(new POINT(200, 450)); // Chips
	KeyPress(1, { 'S' });
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
#pragma endregion
#pragma region Unlock Halloween Characters
	IncrementStage(); // TWRE_DODGE_TO_GEIST_1
	WaitForFrame(5); // overworld
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
		if (i > 0 && i < 4)
		{
			WaitForDeedee();
			ClickAt(new POINT(200, 450)); // Chips
		}
		else
		{
			ClickAt(new POINT(200, 450)); // Chips
			KeyPress(1, { 'D' });
		}
		WaitForFrame(7); // chips
		ClickAt(new POINT(700, 425)); // Done
		IncrementStage(); // CHARACTER_UNLOCK
		WaitForFrame(5); // overworld
		KeyPressUntilBattle({ 'D', 'R' });
		KeyPress(1, { 'R' });
		JumpTo(2);
		WaitForAttacksReady();
		ClickAttack(2, 3); // JJ -> Unscrew
		WaitForBattleEnd();
		IncrementStage(); // TWRE_DODGE_TO_GEIST
		if (i > 0 && i < 4)
		{
			JumpTo(1);
			KeyPress(65, { 'W' });
			KeyPressUntilFrame(18, { 'W', 'D' }); // fishing 1
			ClickAt(new POINT(600, 100)); // Play Deedee's Fishing Hole
			WaitForFrame(19); // fishing 2
			KeyPress(i == 3 ? 2 : 1, { 'D' });
			KeyPress(1, { 'S' });
			WaitForFrame(5); // overworld
			JumpTo(2);
		}
	}
#pragma endregion
#pragma region Gold Endo Grind
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
	for (int i = 0; i < 28; i++)
	{
		WaitForAttacksReady();
		ClickAttack(2, 3); // JJ -> Unscrew
		WaitForVictory();
		WaitForTokens();
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
	WaitForAttacksReady();
	ClickAttack(2, 3); // JJ -> Unscrew
	WaitUntilChipsBtn();
	ClickAt(new POINT(200, 450)); // Chips
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
#pragma endregion
#pragma region Unlock Crying Child -> Springbonnie
	IncrementStage(); // CRYING_CHILD_UNLOCK
	for (int i = 0; i < 6; i++)
	{
		WaitForFrame(5); // overworld
		KeyPress(63, { 'A', 'R' });
		KeyPressUntilBattle({ 'D', 'R' });
		KeyPress(1, { 'R' });
		WaitForAttacksReady();
		ClickAttack(2, 3); // JJ -> Unscrew
		WaitUntilChipsBtn();
		if (i == 5)
			break;
		ClickAt(new POINT(200, 450)); // Chips
		WaitForFrame(7); // chips
		ClickAt(new POINT(700, 425)); // Done
		IncrementStage(); // CHARACTER_UNLOCK
	}
#pragma endregion
#pragma region Fourth Glitch Ending
	IncrementStage(); // FOURTH_GLITCH
	KeyPressUntilFrame(8, { 'D', 'S' }); // underground 1
	KeyPress(165, { 'D', 'S' });
	KeyPress(121, { 'D' });
	KeyPress(175, { 'D', 'W' });
	KeyPressUntilFrame(10, { 'A', 'W' }); // underground 2
	KeyPress(19, { 'W' });
	KeyPressUntilFrame(11, { 'D', 'W' }); // underground 3
	KeyPress(730, { 'D', 'W' });
	KeyPress(125, { 'D', 'S' });
	KeyPressUntilFrame(15, { 'A', 'S' }); // lost world
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
#pragma endregion
#pragma region Buy Armor and Neon Wasp
	WaitForFrame(5); // overworld
	JumpTo(1);
	KeyPressUntilFrame(14, { 'D' }); // armor shop
	ClickAt(new POINT(600, 100)); // Buy Titanium
	ClickAt(new POINT(700, 450)); // Exit Shop
	WaitForFrame(5); // overworld
	JumpTo(1);
	KeyPressUntilFrame(13, { 'A', 'W' }); // shop
	ClickAt(new POINT(600, 100)); // Buy Neon Wasp
	ClickAt(new POINT(700, 450)); // Exit Shop
#pragma endregion
#pragma region Fight Area 1 Auto Chipper
	IncrementStage(); // AUTO_CHIPPER
	WaitForFrame(5); // overworld
	JumpTo(1);
	KeyPress(30, { 'A' });
	KeyPress(140, { 'A', 'W' });
	KeyPressUntilBattle({ 'D', 'W' });
	WaitForAttacksReady();
	ClickAttack(2, 3); // JJ -> Unscrew
	WaitForBattleEnd();
#pragma endregion
#pragma region Chip - Headstart: Strength
	KeyPressUntilChip({ 'A', 'W' });
	ClickAt(new POINT(200, 450)); // Chips
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
	WaitForFrame(5); // overworld
#pragma endregion
#pragma region Chip - Headstart: Defense
	KeyPressUntilChip({ 'D', 'S' });
	ClickAt(new POINT(200, 450)); // Chips
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
	WaitForFrame(5); // overworld
#pragma endregion
#pragma region Fight Area 2 Auto Chipper
	JumpTo(2);
	KeyPress(135, { 'A', 'S' });
	KeyPress(50, { 'A', 'W' });
	KeyPress(50, { 'W' });
	KeyPressUntilBattle({ 'A', 'W' });
	WaitForAttacksReady();
	ClickAttack(2, 3); // JJ -> Unscrew
	WaitForBattleEnd();
#pragma endregion
#pragma region Chip - Evercomet: Weak
	KeyPressUntilChip({ 'W' });
	ClickAt(new POINT(200, 450)); // Chips
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
#pragma endregion
#pragma region Unlock Area 3
	WaitForFrame(5); // overworld
	KeyPress(105, { 'D', 'S', 'R' });
	KeyPress(80, { 'A', 'S', 'R' });
	KeyPress(197, { 'A', 'R' });
#pragma endregion
#pragma region Unlock Withered Chica
	IncrementStage(); // WITHERED_CHICA_UNLOCK
	JumpTo(3);
	KeyPress(55, { 'A', 'W', 'R' });
	KeyPress(33, { 'A', 'R' });
	KeyPressUntilBattle({ 'A', 'W', 'R' });
	KeyPress(1, { 'R' });
	WaitForAttacksReady();
	ClickAttack(2, 3); // JJ -> Unscrew
	WaitUntilChipsBtn();
	ClickAt(new POINT(200, 450)); // Chips
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
#pragma endregion
#pragma region Unlock Withered Freddy
	IncrementStage(); // WITHERED_FREDDY_UNLOCK
	WaitForFrame(5); // overworld
	KeyPress(20, { 'A', 'W', 'R' });
	KeyPress(50, { 'W', 'R' });
	KeyPressUntilBattle({ 'D', 'W', 'R' });
	KeyPress(1, { 'R' });
	WaitForAttacksReady();
	ClickAttack(2, 3); // JJ -> Unscrew
	WaitForBattleEnd();
#pragma endregion
#pragma region Chip - Block: Jumpscare
	KeyPressUntilChip({ 'D', 'W', 'R' });
	ClickAt(new POINT(200, 450)); // Chips
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
#pragma endregion
#pragma region Unlock Withered Foxy
	IncrementStage(); // WITHERED_FOXY_UNLOCK
	WaitForFrame(5); // overworld
	JumpTo(3);
	KeyPress(112, { 'A', 'S', 'R' });
	KeyPressUntilBattle({ 'A', 'R' });
	KeyPress(1, { 'R' });
	WaitForAttacksReady();
	ClickAttack(2, 3); // JJ -> Unscrew
	WaitForBattleEnd();
#pragma endregion
#pragma region Buy Reapers
	IncrementStage(); // UNLOCK_AREAS_3_4
	KeyPress(165, { 'A', 'W' });
	KeyPress(20, { 'A' });
	KeyPress(50, { 'A', 'W' });
	KeyPressUntilFrame(13, { 'W' }); // shop
	ClickAt(new POINT(600, 100)); // Buy X-Reaper
	Wait(1);
	ClickAt(new POINT(400, 100)); // Buy Reaper
	Wait(1);
	ClickAt(new POINT(200, 100)); // Buy Mini-Reaper
	ClickAt(new POINT(700, 450)); // Exit Shop
	WaitForFrame(12); // Bytes
	Wait(20);
	ClickAt(new POINT(200, 200)); // Equip X-Reaper
	ClickAt(new POINT(700, 425)); // Exit Bytes Menu
#pragma endregion
#pragma region Clock 2
	WaitForFrame(5); // overworld
	KeyPress(10, { 'D', 'S' });
	KeyPress(20, { 'D' });
	KeyPress(45, { 'D', 'S' });
	KeyPressUntilFrame(28, { 'A', 'S' }); // clock
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
#pragma endregion
#pragma region Cinematic - Clock 3
	WaitForFrame(5); // overworld
	KeyPress(113, { 'D', 'W' });
	KeyPressUntilFrame(27, { 'W' }); // cinematic
	KeyPress(1500, { VK_RETURN });
	WaitForCinematicEnd();
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
#pragma endregion
#pragma region Unlock Area 4
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
#pragma endregion
#pragma region Chip - Run: Luck
	KeyPressUntilChip({ 'A', 'S' });
	ClickAt(new POINT(200, 450)); // Chips
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
#pragma endregion
#pragma region Chip - Headstart: Speed
	WaitForFrame(5); // overworld
	JumpTo(4);
	KeyPress(20, { 'A' });
	KeyPress(40, { 'A', 'S' });
	KeyPress(60, { 'S' });
	KeyPress(52, { 'A', 'S' });
	KeyPress(40, { 'A' });
	KeyPressUntilChip({ 'A', 'S' });
	ClickAt(new POINT(200, 450)); // Chips
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
	WaitForFrame(5); // overworld
#pragma endregion
#pragma region Buy Medpods
	KeyPress(10, { 'D', 'W' });
	KeyPressUntilFrame(13, { 'D', 'S' });
	WaitForFrame(13); // shop
	ClickAt(new POINT(600, 100)); // Buy Mega-Med
	Wait(1);
	ClickAt(new POINT(400, 100)); // Buy Medpod 2
	Wait(1);
	ClickAt(new POINT(200, 100)); // Buy Medpod 1
	ClickAt(new POINT(700, 450)); // Exit Shop
	WaitForFrame(12); // Bytes
	ClickAt(new POINT(700, 425)); // Exit Bytes Menu
#pragma endregion
#pragma region Chip - Block: Unscrew
	WaitForFrame(5); // overworld
	JumpTo(2);
	KeyPress(58, { 'S' });
	KeyPress(15, { 'D', 'S' });
	KeyPress(75, { 'D' });
	KeyPress(77, { 'D', 'W' });
	JumpTo(3);
	KeyPressUntilChip({ 'D', 'W' });
#pragma endregion
#pragma region Key
	JumpTo(4);
	Wait(150);
	KeyPress(135, { 'D', 'S' });
	KeyPress(74, { 'S' });
	ClickAt(new POINT(200, 450)); // Chips
	KeyPress(1, { 'S' });
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
#pragma endregion
#pragma region Chip - Find: Characters
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
	KeyPressUntilBattle({ 'A', 'W' });
	WaitForBattleEnd();
	KeyPressUntilChip({ 'W' });
	ClickAt(new POINT(200, 450)); // Chips
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
#pragma endregion
#pragma region Buy UFOs
	WaitForFrame(5); // overworld
	JumpTo(6);
	KeyPressUntilFrame(13, { 'A', 'W' }); // shop
	ClickAt(new POINT(600, 100)); // Buy X-FO
	Wait(1);
	ClickAt(new POINT(400, 100)); // Buy UFO
	Wait(1);
	ClickAt(new POINT(200, 100)); // Buy Mini-FO
	ClickAt(new POINT(700, 450)); // Exit Shop
	WaitForFrame(12); // Bytes
	ClickAt(new POINT(700, 425)); // Exit Bytes Menu
#pragma endregion
#pragma region Chip - Freddle: Fury
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
	KeyPressUntilBattle({ 'A', 'W' });
	WaitForBattleEnd();
	KeyPressUntilChip({ 'W' });
	ClickAt(new POINT(200, 450)); // Chips
	KeyPress(1, { 'W' });
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
#pragma endregion
#pragma region Unlock Nightmare Freddy
	IncrementStage(); // NIGHTMARE_FREDDY_UNLOCK
	WaitForFrame(5); // overworld
	JumpTo(5);
	KeyPress(20, { 'S', 'R' });
	KeyPressUntilBattle({ 'D', 'S', 'R' });
	KeyPress(1, { 'R' });
	WaitForVictory();
	WaitUntilChipsBtn();
	ClickAt(new POINT(200, 450)); // Chips
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
#pragma endregion
#pragma region Unlock Nightmare Bonnie
	IncrementStage(); // NIGHTMARE_BONNIE_UNLOCK
	WaitForFrame(5); // overworld
	KeyPress(50, { 'S', 'R' });
	KeyPressUntilBattle({ 'A', 'S', 'R' });
	KeyPress(1, { 'R' });
	WaitForVictory();
	WaitUntilChipsBtn();
	ClickAt(new POINT(200, 450)); // Chips
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
#pragma endregion
#pragma region Chip - Block: Jumpscare
	IncrementStage(); // NIGHTMARE_CHICA_UNLOCK
	WaitForFrame(5); // overworld
	KeyPressUntilChip({ 'A', 'S' });
	ClickAt(new POINT(200, 450)); // Chips
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
#pragma endregion
#pragma region Unlock Nightmare Chica
	WaitForFrame(5); // overworld
	KeyPressUntilBattle({ 'D', 'W', 'R' });
	KeyPress(1, { 'R' });
	WaitForVictory();
	WaitUntilChipsBtn();
	ClickAt(new POINT(200, 450)); // Chips
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
#pragma endregion
#pragma region Unlock Nightmare Foxy
	IncrementStage(); // NIGHTMARE_FOXY_UNLOCK
	WaitForFrame(5); // overworld
	KeyPressUntilBattle({ 'D', 'R' });
	KeyPress(1, { 'R' });
	WaitForVictory();
	WaitUntilChipsBtn();
	ClickAt(new POINT(200, 450)); // Chips
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
#pragma endregion
#pragma region Buy Bomb Bytes
	IncrementStage(); // SHADOW_FREDDY_UNLOCK
	WaitForFrame(5); // overworld
	KeyPressUntilFrame(13, { 'D', 'W' }); // shop
	ClickAt(new POINT(600, 100)); // Buy KABOOM
	Wait(1);
	ClickAt(new POINT(400, 100)); // Buy BOOM
	Wait(1);
	ClickAt(new POINT(200, 100)); // Buy Pop-Pop
	ClickAt(new POINT(700, 450)); // Exit Shop
	WaitForFrame(12); // Bytes
	//Wait(20);
	//ClickAt(new POINT(400, 300)); // Equip KABOOM
	ClickAt(new POINT(700, 425)); // Exit Bytes Menu
#pragma endregion
	TAS_JUMP:
#pragma region Unlock Shadow Freddy
	WaitForFrame(5); // overworld
	KeyPress(60, { 'S', 'R' });
	KeyPressUntilBattle({ 'A', 'S', 'R' });
	KeyPress(1, { 'R' });
	WaitForVictory();
	WaitUntilChipsBtn();
	ClickAt(new POINT(200, 450)); // Chips
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
#pragma endregion
#pragma region Unlock Marionette
	IncrementStage(); // MARIONETTE_UNLOCK
	WaitForFrame(5); // overworld
	KeyPress(14, { 'A', 'S', 'R' });
	KeyPress(55, { 'A', 'W', 'R' });
	KeyPressUntilBattle({ 'A', 'S', 'R' });
	KeyPress(1, { 'R' });
	WaitForVictory();
	WaitUntilChipsBtn();
	ClickAt(new POINT(200, 450)); // Chips
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
#pragma endregion
#pragma region Unlock Phantom Marionette
	IncrementStage(); // PHANTOM_MARIONETTE_UNLOCK
	WaitForFrame(5); // overworld
	KeyPress(50, { 'D', 'S', 'R' });
	KeyPressUntilBattle({ 'D', 'W', 'R' });
	KeyPress(1, { 'R' });
	WaitForVictory();
	WaitUntilChipsBtn();
	ClickAt(new POINT(200, 450)); // Chips
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
#pragma endregion
#pragma region Unlock Golden Freddy
	IncrementStage(); // GOLDEN_FREDDY_UNLOCK
	WaitForFrame(5); // overworld
	KeyPress(60, { 'D', 'S', 'R' });
	KeyPressUntilBattle({ 'A', 'S', 'R' });
	KeyPress(1, { 'R' });
	WaitForVictory();
	WaitUntilChipsBtn();
	ClickAt(new POINT(200, 450)); // Chips
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
#pragma endregion
#pragma region Unlock Paperpals
	IncrementStage(); // PAPERPALS_UNLOCK
	WaitForFrame(5); // overworld
	KeyPressUntilBattle({ 'A', 'W', 'R' });
	KeyPress(1, { 'R' });
	WaitForVictory();
	WaitUntilChipsBtn();
	ClickAt(new POINT(200, 450)); // Chips
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
#pragma endregion
#pragma region Unlock Endo 01
	IncrementStage(); // ENDO_01_UNLOCK
	WaitForFrame(5); // overworld
	KeyPressUntilBattle({ 'A', 'W', 'R' });
	KeyPress(1, { 'R' });
	WaitForVictory();
	WaitUntilChipsBtn();
	ClickAt(new POINT(200, 450)); // Chips
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
#pragma endregion
#pragma region Unlock Endo 02
	IncrementStage(); // ENDO_02_UNLOCK
	WaitForFrame(5); // overworld
	KeyPressUntilBattle({ 'A', 'W', 'R' });
	KeyPress(1, { 'R' });
	WaitForVictory();
	WaitUntilChipsBtn();
	ClickAt(new POINT(200, 450)); // Chips
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
#pragma endregion
#pragma region Buy Boss Drains
	IncrementStage(); // TROPHY_RUN
	WaitForFrame(5); // overworld
	KeyPressUntilFrame(13, { 'D', 'W' }); // shop
	ClickAt(new POINT(600, 100)); // Buy BossDrain-X
	Wait(1);
	ClickAt(new POINT(400, 100)); // Buy BossDrain02
	Wait(1);
	ClickAt(new POINT(200, 100)); // Buy BossDrain01
	ClickAt(new POINT(700, 450)); // Exit Shop
	WaitForFrame(12); // Bytes
	ClickAt(new POINT(700, 425)); // Exit Bytes Menu
#pragma endregion
#pragma region Chip - Pizza: Fury
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
#pragma endregion
#pragma region Chip - Counter: Bite
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
#pragma endregion
#pragma region Chip - Auto: Regen
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
	WaitForFrame(5); // overworld
#pragma endregion
#pragma region Chip - Endless: Speed
	JumpTo(2);
	KeyPress(58, { 'S' });
	KeyPress(15, { 'D', 'S' });
	KeyPress(75, { 'D' });
	KeyPress(77, { 'D', 'W' });
	JumpTo(6);
	KeyPress(50, { 'A', 'S' });
	KeyPress(853, { 'A' });
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
#pragma endregion
#pragma region Chip - Auto: Mimic
	JumpTo(2);
	KeyPress(58, { 'S' });
	KeyPress(15, { 'D', 'S' });
	KeyPress(75, { 'D' });
	KeyPress(77, { 'D', 'W' });
	JumpTo(5);
	KeyPress(10, { 'A' });
	KeyPress(280, { 'A', 'S' });
	KeyPressUntilChip({ 'A' });
	ClickAt(new POINT(200, 450)); // Chips
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
	WaitForFrame(5); // overworld
#pragma endregion
#pragma region Chip - Auto: Giftboxes
	KeyPress(68, { 'A', 'W' });
	KeyPressUntilBattle({ 'A', 'S' });
	WaitForBattleEnd();
	KeyPressUntilChip({ 'A', 'S' });
	ClickAt(new POINT(200, 450)); // Chips
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
	WaitForFrame(5); // overworld
#pragma endregion
#pragma region Clock 3
	KeyPress(48, { 'D', 'W' });
	KeyPress(100, { 'D', 'S' });
	KeyPress(150, { 'A', 'S' });
	KeyPress(110, { 'D', 'S' });
	KeyPressUntilFrame(28, { 'A', 'S' }); // clock
	KeyPress(75, { 'A', 'W' });
	KeyPress(188, { 'A' });
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
#pragma endregion
#pragma region Chip - Endless: Defense
	JumpTo(2);
	KeyPress(58, { 'S' });
	KeyPress(15, { 'D', 'S' });
	KeyPress(75, { 'D' });
	KeyPress(77, { 'D', 'W' });
	JumpTo(5);
	KeyPress(10, { 'A' });
	KeyPress(230, { 'A', 'S' });
	KeyPress(880, { 'A' });
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
#pragma endregion
#pragma region Chip - Endless: Strength
	KeyPressUntilBattle({ 'A', 'S' });
	WaitForBattleEnd();
	KeyPress(258, { 'A', 'S' });
	KeyPress(210, { 'A', 'W' });
	KeyPressUntilChip({ 'A', 'S' });
	ClickAt(new POINT(200, 450)); // Chips
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
	WaitForFrame(5); // overworld
#pragma endregion
#pragma region Fight/Unlock Chipper
	KeyPress(60, { 'D', 'W' });
	KeyPress(40, { 'D', 'S' });
	KeyPressUntilBattle({ 'A', 'S' });
	WaitForVictory();
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
#pragma endregion
#pragma region Cinematic - Clock 4
	Wait(1);
	JumpTo(4);
	KeyPress(15, { 'D' });
	WaitForFrame(27); // cinematic
	KeyPress(2000, { VK_RETURN });
	WaitForCinematicEnd();
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
	Wait(27);
	ClickCharacter(1, 1); // Freddy
	Wait(11);
	ClickCharacter(7, 5); // Fredbear
	ClickAt(new POINT(700, 450)); // Done
	WaitForFrame(5); // overworld
#pragma endregion
#pragma region Universe Ending
	JumpTo(5);
	KeyPress(20, { 'S' });
	KeyPressUntilFrame(30, { 'D', 'S' }); // Frame 31
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
#pragma endregion
#pragma region Chip - Evercomet: Strong
	JumpTo(2);
	KeyPress(58, { 'S' });
	KeyPress(15, { 'D', 'S' });
	KeyPress(75, { 'D' });
	KeyPress(77, { 'D', 'W' });
	JumpTo(5);
	KeyPress(10, { 'A' });
	KeyPress(430, { 'A', 'S' });
	KeyPress(444, { 'A' });
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
#pragma endregion
#pragma region Chip - Curse: Status
	JumpTo(2);
	KeyPress(58, { 'S' });
	KeyPress(15, { 'D', 'S' });
	KeyPress(75, { 'D' });
	KeyPress(77, { 'D', 'W' });
	JumpTo(5);
	KeyPress(10, { 'A' });
	KeyPress(180, { 'A', 'S' });
	KeyPress(819, { 'A' });
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
#pragma endregion
#pragma region Fight Security Owl
	JumpTo(2);
	KeyPress(58, { 'S' });
	KeyPress(15, { 'D', 'S' });
	KeyPress(75, { 'D' });
	KeyPress(77, { 'D', 'W' });
	JumpTo(5);
	KeyPress(10, { 'A' });
	KeyPress(440, { 'A', 'S' });
	KeyPress(220, { 'S' });
	ClickAt(new POINT(200, 450)); // Chips
	KeyPress(1, { 'S' });
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
	WaitForFrame(5); // overworld
	WaitForBattleEnd();
#pragma endregion
#pragma region Fight/Unlock Animdude
	KeyPressUntilFrame(26, { 'W' }); // boss cutscene
	WaitForFrame(5); // overworld
	WaitForVictory();
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
	Wait(38);
	ClickCharacter(7, 5); // Fredbear
	Wait(11);
	ClickCharacter(1, 1); // Freddy
	ClickAt(new POINT(700, 450)); // Done
	WaitForFrame(5); // overworld
#pragma endregion
#pragma region Clock 4
	Wait(1);
	JumpTo(2);
	KeyPress(58, { 'S' });
	KeyPress(15, { 'D', 'S' });
	KeyPress(75, { 'D' });
	KeyPress(77, { 'D', 'W' });
	JumpTo(6);
	KeyPress(250, { 'A', 'W' });
	KeyPress(300, { 'A' });
	KeyPress(5, { 'A', 'W' });
	KeyPress(191, { 'A' });
	ClickAt(new POINT(200, 450)); // Chips
	KeyPress(1, { 'A' });
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
	WaitForFrame(28); // clock
	KeyPress(189, { 'A' });
	WaitForFrame(5); // overworld
#pragma endregion
#pragma region Buy Blocks
	KeyPress(100, { 'A', 'W' });
	KeyPress(80, { 'A', 'S' });
	KeyPress(80, { 'A', 'W' });
	KeyPress(200, { 'D', 'W' });
	KeyPress(80, { 'W' });
	KeyPress(220, { 'A', 'W' });
	KeyPress(70, { 'A', 'S' });
	KeyPressUntilFrame(13, { 'A', 'W' }); // shop
	ClickAt(new POINT(600, 100)); // Buy Block50
	Wait(1);
	ClickAt(new POINT(400, 100)); // Buy Block20
	Wait(1);
	ClickAt(new POINT(200, 100)); // Buy Block5
	ClickAt(new POINT(700, 450)); // Exit Shop
	WaitForFrame(12); // Bytes
	ClickAt(new POINT(700, 425)); // Exit Bytes Menu
#pragma endregion
#pragma region Cinematic - Clock 5
	WaitForFrame(5); // overworld
	JumpTo(2);
	KeyPress(58, { 'S' });
	KeyPress(15, { 'D', 'S' });
	KeyPress(75, { 'D' });
	KeyPress(77, { 'D', 'W' });
	JumpTo(6);
	KeyPress(100, { 'A', 'S' });
	ClickAt(new POINT(200, 450)); // Chips
	KeyPress(1, { 'S' });
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
	WaitForFrame(5); // overworld
	KeyPressUntilFrame(27, { 'S' });
	KeyPress(1000, { VK_RETURN });
	WaitForCinematicEnd();
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
#pragma endregion
#pragma region Clock 5
	JumpTo(2);
	KeyPress(58, { 'S' });
	KeyPress(15, { 'D', 'S' });
	KeyPress(75, { 'D' });
	KeyPress(77, { 'D', 'W' });
	JumpTo(2);
	KeyPress(50, { 'D', 'S' });
	KeyPress(9, { 'S' });
	KeyPress(270, { 'D', 'S' });
	KeyPress(80, { 'D', 'W' });
	KeyPress(35, { 'D' });
	ClickAt(new POINT(200, 450)); // Chips
	KeyPress(1, { 'D' });
	WaitForFrame(7); // chips
	ClickAt(new POINT(700, 425)); // Done
	WaitForFrame(28); // clock
	KeyPress(75, { 'A', 'W' });
	KeyPress(100, { 'A' });
	KeyPress(1, { 'A', 'W' });
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
#pragma endregion
#pragma region Clock Ending
	JumpTo(4);
	KeyPress(250, { 'D', 'W' });
	KeyPress(150, { 'A', 'W' });
	KeyPress(100, { 'A' });
	KeyPress(80, { 'A', 'S' });
	KeyPress(50, { 'A' });
	KeyPressUntilFrame(29, { 'A', 'S' }); // ending 4
	RestartGame();
#pragma endregion
#pragma region Fight Chicas Magical Rainbow
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
	Wait(11);
	ClickCharacter(1, 1); // Freddy (From)
	Wait(12);
	ClickCharacter(8, 3); // Paperpals (To)
	Wait(11);
	ClickCharacter(2, 2); // JJ (From)
	Wait(11);
	ClickCharacter(1, 6); // Jack-O-Bonnie (To)
	Wait(11);
	ClickCharacter(6, 1); // Toy Chica (From)
	Wait(11);
	ClickCharacter(7, 5); // Fredbear (To)
	Wait(11);
	ClickCharacter(2, 1); // Bonnie (From)
	Wait(11);
	ClickCharacter(8, 6); // Purple Guy (To)
	ClickAt(new POINT(700, 450)); // Done
	IncrementStage(); // MAGICAL_PAINBOW
	WaitForFrame(5); // overworld
	Wait(1);
	JumpTo(2);
	KeyPress(58, { 'S' });
	KeyPress(15, { 'D', 'S' });
	KeyPress(75, { 'D' });
	KeyPress(77, { 'D', 'W' });
	JumpTo(6);
	KeyPress(1340, { 'D', 'W' });
	KeyPress(506, { 'W' });
	ClickAt(new POINT(200, 450)); // Chips
	KeyPress(1, { 'W' });
	WaitForFrame(7); // chips
	Wait(20);
	ClickAt(new POINT(300, 200)); // Equip Endless: Speed
	Wait(10);
	ClickAt(new POINT(500, 200)); // Equip Auto: Giftboxes
	ClickAt(new POINT(700, 425)); // Done
	WaitForFrame(5); // overworld
	WaitForAttacksReady();
	ClickAttack(1, 3); // Mimic Ball
	WaitForAttacksReady();
	ClickAttack(2, 3); // Slasher
	WaitForAttacksReady();
	ClickAttack(3, 3); // Mimic Ball
	WaitForAttacksReady();
	ClickAttack(4, 2); // Slasher
	WaitForAttacksReady();
	ClickAttack(1, 3); // Mimic Ball
	WaitForAttacksReady();
	ClickAttack(2, 3); // Slasher
#pragma endregion
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

void TAS::KeyPressUntilBattle(std::vector<char> keyCodes)
{
	Queue.push_back(new TASKeyPressUntilBattle(keyCodes));
}

void TAS::KeyPressUntilChip(std::vector<char> keyCodes)
{
	Queue.push_back(new TASKeyPressUntilChip(keyCodes));
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

void TAS::WaitForDeedee()
{
	Queue.push_back(new TASWaitForDeedee());
}

void TAS::WaitForAttacksReady()
{
	Queue.push_back(new TASWaitForAttacksReady());
}

void TAS::WaitForVictory()
{
	Queue.push_back(new TASWaitForVictory());
}

void TAS::WaitUntilChipsBtn()
{
	Queue.push_back(new TASWaitUntilChipsBtn());
}

void TAS::WaitForBattleEnd()
{
	Queue.push_back(new TASWaitForBattleEnd());
}

void TAS::WaitForCinematicEnd()
{
	Queue.push_back(new TASWaitForCinematicEnd());
}

void TAS::WaitForTokens()
{
	Queue.push_back(new TASWaitForTokens());
}