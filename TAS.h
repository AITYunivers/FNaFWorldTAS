#pragma once
#include "MMFGlobals.h"
#include <deque>
#include <vector>
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

	// Deque of keys in a queue
	static std::deque<TASEvent*> Queue;

	static void KeyPress(int timer, std::vector<char> keyCodes);
	static bool IsKeyPressed(char keyCode);
	static void Wait(int frames);
	static void WaitForFrame(int frame);
	static void GotoFrame(int frame);
};