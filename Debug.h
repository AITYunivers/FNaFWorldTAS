#pragma once
#include <d3d9.h>
#include <imgui.h>
#include "YuniUtil.h"
#include "TASWait.h"
#include "TASWaitForFrame.h"
#include "TASGotoFrame.h"
#include "TASKeyPress.h"

class Debug
{
public:
	// Functions
	static void Render()
	{
        RunHeader* runHeader = GetRunHeader();

		if (runHeader == nullptr || runHeader->App == nullptr || runHeader->Frame == nullptr)
			return;

		int total = 0;
		for (int n = 0; n < MAX_FRAMERATE; n++)
			total += runHeader->rh4.FrameRateArray[n];

		ImGui::SetNextWindowSize(ImVec2(300, 300));
        if (ImGui::Begin("FNAFWTAS Debug"))
        {
			ImGui::SeparatorText("General");
			{
				ImGui::Text(("FPS: " + std::to_string((1000 * MAX_FRAMERATE) / total)).c_str());
				ImGui::Text(("Frame Timer: " + std::to_string(runHeader->LoopCount)).c_str());
				ImGui::Text(("Stable Timer: " + std::to_string((unsigned int)((1.0 / 60.0) / 0.001 * runHeader->LoopCount))).c_str());
				ImGui::Text(("Current Frame: " + std::to_string(runHeader->App->nCurrentFrame)).c_str());
				ImGui::Text(("Next Frame: " + std::to_string(runHeader->App->nextFrame)).c_str());
				ImGui::Text(("rhQuit: " + std::to_string(runHeader->Quit)).c_str());
			}

			if (!TAS::Queue.empty())
			{
				ImGui::SeparatorText("TAS");
				{
					TASEvent* event = TAS::Queue.front();
					if (TASWait* waitEvt = dynamic_cast<TASWait*>(event))
						ImGui::Text(("Waiting for " + std::to_string(waitEvt->timer)).c_str());
					else if (TASWaitForFrame* waitFrameEvt = dynamic_cast<TASWaitForFrame*>(event))
						ImGui::Text(("Waiting for Frame " + std::to_string(waitFrameEvt->frame)).c_str());
					else if (TASGotoFrame* gotoFrameEvt = dynamic_cast<TASGotoFrame*>(event))
						ImGui::Text(("Going to Frame " + std::to_string(gotoFrameEvt->frame)).c_str());
					else if (TASKeyPress* keyPressEvt = dynamic_cast<TASKeyPress*>(event))
						ImGui::Text(("Pressing " + std::to_string(keyPressEvt->keyCodes.size()) + " key(s) for " + std::to_string(keyPressEvt->timer)).c_str());
				}
			}
        }
        ImGui::End();
	}
};