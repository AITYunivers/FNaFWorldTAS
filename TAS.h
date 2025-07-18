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

		if (!Queue.empty() && Queue.front()->Tick())
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
	} stage;

	static void Wait(int frames);
	static void WaitForFrame(int frame);
	static void RestartGame();
	static void IncrementStage();
	static void ClickCharacter(int x, int y);
	static void ClickAttack(int charSlot, int attackSlot);
	static void LoadTASSave();
};