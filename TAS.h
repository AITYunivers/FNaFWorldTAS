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

	static RunObject* foundchip;

#pragma region KeyPress
	// Deque of keys in a queue
	static std::deque<TASEvent*> Queue;

	static void KeyPress(int timer, std::vector<char> keyCodes);
	static void KeyPressUntilFrame(int frame, std::vector<char> keyCodes);
	static void KeyPressUntilBattle(std::vector<char> keyCodes);
	static void KeyPressUntilChip(std::vector<char> keyCodes);
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
		FREDDY_LV_4,
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
		PLUSHTRAP_UNLOCK,
		ENDOPLUSH_UNLOCK,
		SPRINGTRAP_UNLOCK,
		RXQ_UNLOCK,
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
		TROPHY_RUN,
		MAGICAL_PAINBOW
	} stage;

	static inline std::string StageToString(Stage s)
	{
		switch (s)
		{
		case START: return "START";
		case PEARL_CHEST: return "PEARL_CHEST";
		case FREDDY_LV_4: return "FREDDY_LV_4";
		case JJ_UNLOCK: return "JJ_UNLOCK";
		case BB_UNLOCK: return "BB_UNLOCK";
		case PHANTOM_FREDDY_UNLOCK: return "PHANTOM_FREDDY_UNLOCK";
		case PHANTOM_CHICA_UNLOCK: return "PHANTOM_CHICA_UNLOCK";
		case PHANTOM_BB_UNLOCK: return "PHANTOM_BB_UNLOCK";
		case PHANTOM_FOXY_UNLOCK: return "PHANTOM_FOXY_UNLOCK";
		case TWRE_DODGE_TO_AREA_5: return "TWRE_DODGE_TO_AREA_5";
		case PHANTOM_MANGLE_UNLOCK: return "PHANTOM_MANGLE_UNLOCK";
		case WITHERED_BONNIE_UNLOCK: return "WITHERED_BONNIE_UNLOCK";
		case TWRE_DODGE_TO_AREA_6: return "TWRE_DODGE_TO_AREA_6";
		case PLUSHTRAP_UNLOCK: return "PLUSHTRAP_UNLOCK";
		case ENDOPLUSH_UNLOCK: return "ENDOPLUSH_UNLOCK";
		case SPRINGTRAP_UNLOCK: return "SPRINGTRAP_UNLOCK";
		case RXQ_UNLOCK: return "RXQ_UNLOCK";
		case TWRE_DODGE_TO_GEIST_1: return "TWRE_DODGE_TO_GEIST_1";
		case JACK_O_BONNIE_UNLOCK: return "JACK_O_BONNIE_UNLOCK";
		case TWRE_DODGE_TO_GEIST_2: return "TWRE_DODGE_TO_GEIST_2";
		case JACK_O_CHICA_UNLOCK: return "JACK_O_CHICA_UNLOCK";
		case TWRE_DODGE_TO_GEIST_3: return "TWRE_DODGE_TO_GEIST_3";
		case NIGHTMARE_BB_UNLOCK: return "NIGHTMARE_BB_UNLOCK";
		case TWRE_DODGE_TO_GEIST_4: return "TWRE_DODGE_TO_GEIST_4";
		case NIGHTMARIONNE_UNLOCK: return "NIGHTMARIONNE_UNLOCK";
		case TWRE_DODGE_TO_GEIST_5: return "TWRE_DODGE_TO_GEIST_5";
		case COFFEE_UNLOCK: return "COFFEE_UNLOCK";
		case TWRE_DODGE_TO_GEIST_6: return "TWRE_DODGE_TO_GEIST_6";
		case PURPLE_GUY_UNLOCK: return "PURPLE_GUY_UNLOCK";
		case GOLD_ENDO_GRIND: return "GOLD_ENDO_GRIND";
		case CRYING_CHILD_UNLOCK: return "CRYING_CHILD_UNLOCK";
		case FUNTIME_FOXY_UNLOCK: return "FUNTIME_FOXY_UNLOCK";
		case NIGHTMARE_FREDBEAR_UNLOCK: return "NIGHTMARE_FREDBEAR_UNLOCK";
		case NIGHTMARE_UNLOCK: return "NIGHTMARE_UNLOCK";
		case FREDBEAR_UNLOCK: return "FREDBEAR_UNLOCK";
		case SPRING_BONNIE_UNLOCK: return "SPRING_BONNIE_UNLOCK";
		case FOURTH_GLITCH: return "FOURTH_GLITCH";
		case AUTO_CHIPPER: return "AUTO_CHIPPER";
		case WITHERED_CHICA_UNLOCK: return "WITHERED_CHICA_UNLOCK";
		case WITHERED_FREDDY_UNLOCK: return "WITHERED_FREDDY_UNLOCK";
		case WITHERED_FOXY_UNLOCK: return "WITHERED_FOXY_UNLOCK";
		case UNLOCK_AREAS_3_4: return "UNLOCK_AREAS_3_4";
		case NIGHTMARE_FREDDY_UNLOCK: return "NIGHTMARE_FREDDY_UNLOCK";
		case NIGHTMARE_BONNIE_UNLOCK: return "NIGHTMARE_BONNIE_UNLOCK";
		case NIGHTMARE_CHICA_UNLOCK: return "NIGHTMARE_CHICA_UNLOCK";
		case NIGHTMARE_FOXY_UNLOCK: return "NIGHTMARE_FOXY_UNLOCK";
		case SHADOW_FREDDY_UNLOCK: return "SHADOW_FREDDY_UNLOCK";
		case MARIONETTE_UNLOCK: return "MARIONETTE_UNLOCK";
		case PHANTOM_MARIONETTE_UNLOCK: return "PHANTOM_MARIONETTE_UNLOCK";
		case GOLDEN_FREDDY_UNLOCK: return "GOLDEN_FREDDY_UNLOCK";
		case PAPERPALS_UNLOCK: return "PAPERPALS_UNLOCK";
		case ENDO_01_UNLOCK: return "ENDO_01_UNLOCK";
		case ENDO_02_UNLOCK: return "ENDO_02_UNLOCK";
		case TROPHY_RUN: return "TROPHY_RUN";
		case MAGICAL_PAINBOW: return "MAGICAL_PAINBOW";
		}
		return "UNKNOWN_STAGE";
	}

	static void Wait(int frames);
	static void WaitForFrame(int frame);
	static void RestartGame();
	static void IncrementStage();
	static void ClickCharacter(int x, int y);
	static void ClickAttack(int charSlot, int attackSlot);
	static void LoadTASSave();
	static void JumpTo(int area);
	static void WaitForDeedee();
	static void WaitForAttacksReady();
	static void WaitForVictory();
	static void WaitUntilChipsBtn();
	static void WaitForBattleEnd();
	static void WaitForCinematicEnd();
	static void WaitForTokens();
};