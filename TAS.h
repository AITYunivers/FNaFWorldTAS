#pragma once
#include "MMFGlobals.h"
#include <deque>
#include "CEventProgramHook.h"
#include "TASEvent.h"

class TAS
{
public:
	static bool running;
	static unsigned int oldLoopCount;
	static unsigned int oldFrame;
	static void Run();

	static void TickQueue()
	{
		RunHeader* runHeader = GetRunHeader();
		if (TAS::oldLoopCount == runHeader->LoopCount && TAS::oldFrame == runHeader->App->nCurrentFrame)
			return;
		TAS::oldLoopCount = runHeader->LoopCount;
		TAS::oldFrame = runHeader->App->nCurrentFrame;

		while (!Queue.empty() && Queue.front()->Tick())
			Queue.pop_front();
	}

#pragma region KeyPress
	// Deque of keys in a queue
	static std::deque<TASEvent*> Queue;

	static void KeyPress(int timer, std::vector<char> keyCodes);
	static bool IsKeyPressed(char keyCode);
#pragma endregion

#pragma region Mouse
	static POINT* mousePos;

	/// <summary>
	/// Clicks at a set position
	/// </summary>
	/// <param name="mousePos">The mouse position in terms of the client (0,0 -> 800,480)</param>
	/// <param name="mouseBtn">0x201 (LMB) by default, the btnCode is defined in CEventProgram::onMouseButton</param>
	static void ClickAt(POINT* mousePos, int mouseBtn = 0x201);
#pragma endregion

	static enum Stage
	{
		START,
		PEARL_CHEST,
		JJ_UNLOCK,
		BB_UNLOCK,
		PHANTOM_FREDDY_UNLOCK,
		PHANTOM_CHICA_UNLOCK,
		PHANTOM_BB_UNLOCK,
		PHANTOM_FOXY_UNLOCK,
		TWRE_DODGE_TO_AREA_5,
		PHANTOM_MANGLE_UNLOCK,
		WITHERED_BONNIE_UNLOCK,
		TWRE_DODGE_TO_AREA_6,
		TWRE_DODGE_TO_GEIST_1,
		JACK_O_BONNIE_UNLOCK,
		TWRE_DODGE_TO_GEIST_2,
		JACK_O_CHICA_UNLOCK,
		TWRE_DODGE_TO_GEIST_3,
		NIGHTMARE_BB_UNLOCK,
		TWRE_DODGE_TO_GEIST_4,
		NIGHTMARIONNE_UNLOCK,
		TWRE_DODGE_TO_GEIST_5,
		COFFEE_UNLOCK,
		TWRE_DODGE_TO_GEIST_6,
		PURPLE_GUY_UNLOCK,
		GOLD_ENDO_GRIND,
		PLUSHTRAP_UNLOCK,
		ENDOPLUSH_UNLOCK,
		SPRINGTRAP_UNLOCK,
		RXQ_UNLOCK,
		CRYING_CHILD_UNLOCK,
		FUNTIME_FOXY_UNLOCK,
		NIGHTMARE_FREDBEAR_UNLOCK,
		NIGHTMARE_UNLOCK,
		FREDBEAR_UNLOCK,
		SPRING_BONNIE_UNLOCK,
		FOURTH_GLITCH,
		AUTO_CHIPPER,
		WITHERED_CHICA_UNLOCK,
		WITHERED_FREDDY_UNLOCK,
		WITHERED_FOXY_UNLOCK,
		UNLOCK_AREAS_3_4,
		NIGHTMARE_FREDDY_UNLOCK,
		NIGHTMARE_BONNIE_UNLOCK,
		NIGHTMARE_CHICA_UNLOCK,
		NIGHTMARE_FOXY_UNLOCK,
		SHADOW_FREDDY_UNLOCK,
		MARIONETTE_UNLOCK,
		PHANTOM_MARIONETTE_UNLOCK,
		GOLDEN_FREDDY_UNLOCK,
		PAPERPALS_UNLOCK,
		ENDO_01_UNLOCK,
		ENDO_02_UNLOCK,
	} stage;

	static void Wait(int frames);
	static void WaitForFrame(int frame);
	static void RestartGame();
	static void IncrementStage();
	static void ClickCharacter(int x, int y);
	static void ClickAttack(int charSlot, int attackSlot);
	static void LoadTASSave();
	static void JumpTo(int area);
};