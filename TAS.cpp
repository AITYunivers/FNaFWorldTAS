#include "TAS.h"
#include "TASKeyPress.h"
#include "TASWait.h"
#include "TASWaitForFrame.h"
#include "TASGotoFrame.h"
#include <filesystem>

#pragma region Static Variables
bool TAS::running = false;
unsigned int TAS::oldLoopCount = false;
unsigned int TAS::oldFrame = false;

std::deque<TASEvent*> TAS::Queue;
#pragma endregion

void TAS::Run()
{
	CRunApp* app = GetCRunApp();
	running = true;
	WaitForFrame(0); // Wait for Frame 32 to load
	GotoFrame(44); // Go To Rainbow Adventure

	KeyPress(240, { VK_RIGHT });		// Begin walk from start
	KeyPress(30, { VK_RIGHT, 'Z' });	// Jump through first 2 flowers

	KeyPress(50, { VK_RIGHT });			// Walk to next 2 flower shooters
	KeyPress(30, { VK_RIGHT, 'Z' });	// Jump through 2 flower shooters

	KeyPress(69, { VK_RIGHT });			// Walk to next trigger
	KeyPress(8, { VK_RIGHT, 'Z' });		// Jump into little pocket on first trigger
	KeyPress(4, { 'Z' });				// Stop moving to avoid death, but keep jumping to gain height
	Wait(1);							// Wait a total of 6 frames before continuing right

	KeyPress(91, { VK_RIGHT });			// Walk toward second trigger
	KeyPress(11, { VK_RIGHT, 'Z' });	// Jump towards platform
	KeyPress(12, { VK_RIGHT });			// Stop jump for edge-clip
	KeyPress(2, { VK_LEFT });
	KeyPress(2, { VK_RIGHT });		// Start moving right while doing a max jump

	KeyPress(70, { VK_RIGHT });			// Fall and walk to next trigger
	KeyPress(1, { VK_RIGHT, 'Z' });		// Jump for 6 frames, go to right for 1 frame
	KeyPress(1, { VK_LEFT, 'Z' });		// Go to left for 1 frame immediately after going right
	KeyPress(2, { 'Z' });				// Let go of left and right for 2 frames
	KeyPress(2, { VK_RIGHT, 'Z' });		// Resume holding right, let go of jump in 2 frames

	KeyPress(60, { VK_RIGHT });			// Walk into rainbow trigger and past it
	KeyPress(20, { VK_RIGHT, 'Z' });	// Jump onto the platform
	KeyPress(83, { VK_RIGHT });			// Fall off of the platform

	// Follow Rainbow
	Wait(7);
	KeyPress(1, { VK_RIGHT });
	Wait(2);
	KeyPress(46, { VK_RIGHT });
	Wait(1);
	KeyPress(2, { VK_RIGHT });
	Wait(1);
	KeyPress(5, { VK_RIGHT });
	Wait(1);
	KeyPress(2, { VK_RIGHT });
	Wait(1);
	KeyPress(2, { VK_RIGHT });
	Wait(1);
	KeyPress(3, { VK_RIGHT });
	Wait(1);
	KeyPress(5, { VK_RIGHT });
	Wait(1);
	KeyPress(2, { VK_RIGHT });
	Wait(1);
	KeyPress(5, { VK_RIGHT });			// Avoid flower shooter
	Wait(1);
	KeyPress(13, { VK_RIGHT });
	Wait(9);
	KeyPress(49, { VK_RIGHT });
	Wait(1);
	KeyPress(2, { VK_RIGHT });
	Wait(1);
	KeyPress(2, { VK_RIGHT });
	Wait(1);
	KeyPress(5, { VK_RIGHT });

	Wait(27);							// Wait for rainbow to disolve
	KeyPress(80, { VK_RIGHT, 'Z' });	// Jump over the remaining rainbow and the first 2 butterflys
	KeyPress(23, { VK_RIGHT });			// Continue walking right
	Wait(6);
	KeyPress(2, { VK_RIGHT });
	Wait(15);
	KeyPress(5, { VK_RIGHT });
	Wait(15);
	KeyPress(6, { VK_RIGHT, 'Z' });
	KeyPress(36, { VK_RIGHT });


	Wait(14);							// Wait for the fourth butterfly's to stop shooting
	KeyPress(6, { VK_RIGHT, 'Z' });		// Jump over the last bit of the butterfly's laser, precise..?

	KeyPress(78, { VK_RIGHT });			// Walk toward the first spike trigger
	KeyPress(50, { VK_RIGHT, 'Z' });	// Jump over spikes
	KeyPress(40, { VK_RIGHT });			// Walk toward next triggers
	KeyPress(52, { VK_RIGHT, 'Z' });	// Jump over spike
	Wait(9);							// Stop for 9 frames before hitting the pedal

	KeyPress(25, { VK_RIGHT });			// Walk toward the next spike trigger
	KeyPress(35, { VK_RIGHT, 'Z' });	// Jump over spikes

	KeyPress(112, { VK_RIGHT });		// Walk to edge of rainbow trigger
	Wait(148);							// Wait for the rainbow to catch up
	KeyPress(1, { VK_RIGHT });			// Activate the trigger
	KeyPress(21, { VK_LEFT });			// Go left under the rainbow, to the right of it's middle laser

	// Follow laser at the back
	for (int i = 0; i < 15; i++)
	{
		Wait(6);
		KeyPress(2, { VK_RIGHT });
	}

	KeyPress(4, { VK_RIGHT });			// Align yourself to the furthest left you can be
	Wait(4);							// Wait for the lasers to almost end
	KeyPress(18, { 'Z' });				// Start a max jump
	KeyPress(29, { VK_RIGHT, 'Z' });	// 18 frames into the jump, begin going right
	KeyPress(25, { VK_RIGHT });			// Survive the first spike and end jump out of the second spike
	Wait(9);							// Align yourself between two spikes and wait for 9 frames
	KeyPress(30, { VK_RIGHT, 'Z' });	// Continue right, touch down, and immediately jump
	KeyPress(77, { VK_RIGHT });			// Survive the third spike and continue right
	KeyPress(30, { VK_RIGHT, 'Z' });	// Jump over the fourth spikes

	KeyPress(96, { VK_RIGHT });			// Walk toward the log trigger and activate it
	KeyPress(32, { VK_LEFT, 'Z' });		// Jump left
	KeyPress(6, { VK_LEFT });			// Land on the platform as soon as possible
	KeyPress(40, { VK_RIGHT, 'Z' });	// Immediately (optionally max) jump to the right
	KeyPress(85, { VK_RIGHT });			// Walk to before the next trigger
	KeyPress(60, { VK_RIGHT, 'Z' });	// Jump through the next trigger, dodging the 2 obstacles
	Wait(25);							// Wait until you touch down
	KeyPress(8, { 'Z' });	// Immediately jump to the right
	KeyPress(20, { VK_RIGHT, 'Z' });	// Max jump to the right
	KeyPress(1, { VK_RIGHT });
	KeyPress(50, { VK_RIGHT, 'Z' });

	KeyPress(338, { VK_RIGHT });		// Run right, avoiding the eyeballs, toward the next trigger
	KeyPress(30, { VK_RIGHT, 'Z' });	// Jump over the first spikes
	KeyPress(57, { VK_RIGHT });			// Continue running toward the next trigger
	KeyPress(30, { VK_RIGHT, 'Z' });	// Jump over the second spikes
	KeyPress(183, { VK_RIGHT });		// Continue running toward the next trigger
	KeyPress(30, { VK_RIGHT, 'Z' });	// Jump over the third spikes
	KeyPress(62, { VK_RIGHT });			// Walk toward the flower shooter's trigger
	KeyPress(15, { VK_RIGHT, 'Z' });	// Jump between the flower shooter's pedals
	KeyPress(70, { VK_RIGHT, 'Z' });	// Continue to the finish, avoiding the remaining eyeballs
	KeyPress(400, { VK_RIGHT });
}

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

void TAS::Wait(int frames)
{
	Queue.push_back(new TASWait(frames));
}

void TAS::WaitForFrame(int frame)
{
	Queue.push_back(new TASWaitForFrame(frame));
}

void TAS::GotoFrame(int frame)
{
	Queue.push_back(new TASGotoFrame(frame));
}
