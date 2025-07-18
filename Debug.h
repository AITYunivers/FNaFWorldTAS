#pragma once
#include <d3d9.h>
#include <imgui.h>
#include "YuniUtil.h"
#include "TASWait.h"
#include "TASWaitForFrame.h"
#include "TASKeyPress.h"
#include "TASClickAt.h"

class Debug
{
public:
	// Statics
	static RunObject *battle,
					 *water,
					 *enemyMaxLife,
					 *character2;

	// Functions
	static void Render()
	{
        RunHeader* runHeader = GetRunHeader();

		if (runHeader == nullptr || runHeader->App == nullptr || runHeader->Frame == nullptr)
			return;

		int total = 0;
		for (int n = 0; n < MAX_FRAMERATE; n++)
			total += runHeader->rh4.FrameRateArray[n];

		ImGui::SetNextWindowSize(ImVec2(400, 300));
        if (ImGui::Begin("FNAFWTAS Debug"))
        {
			ImGui::SeparatorText("General");
			{
				ImGui::Text(("FPS: " + std::to_string((1000 * MAX_FRAMERATE) / total)).c_str());
				ImGui::Text(("Timer: " + std::to_string(runHeader->LoopCount)).c_str());
			}

			if (!TAS::Queue.empty())
			{
				ImGui::SeparatorText("TAS");
				{
					TASEvent* event = TAS::Queue.front();
					ImGui::Text(("Stage: " + std::to_string(TAS::stage)).c_str());
					if (TASWait* waitEvt = dynamic_cast<TASWait*>(event))
						ImGui::Text(("Waiting for " + std::to_string(waitEvt->timer)).c_str());
					else if (TASWaitForFrame* waitFrameEvt = dynamic_cast<TASWaitForFrame*>(event))
						ImGui::Text(("Waiting for Frame " + std::to_string(waitFrameEvt->frame)).c_str());
					else if (TASKeyPress* keyPressEvt = dynamic_cast<TASKeyPress*>(event))
						ImGui::Text(("Pressing " + std::to_string(keyPressEvt->keyCodes.size()) + " key(s) for " + std::to_string(keyPressEvt->timer)).c_str());
					else if (TASClickAt* clickEvt = dynamic_cast<TASClickAt*>(event))
						ImGui::Text(("Clicking at (" + std::to_string(clickEvt->mousePos->x) + ", " + std::to_string(clickEvt->mousePos->y) + ")").c_str());
				}
			}

			if (runHeader->App->nCurrentFrame == 5)
			{
				ImGui::SeparatorText("Overworld");
				{
					bool inBattle = YuniUtil::GetCounterValue(battle) == 1;
					ImGui::Text(("In Battle: " + std::string(inBattle ? "True" : "False")).c_str());
					ImGui::Text(("Next Encounter ID: " + std::to_string(YuniUtil::GetAlterableValue(character2, 4))).c_str());

					if (inBattle)
					{
						std::vector<RunObject*> targets = YuniUtil::GetRunObjectsFromName(_T("target"));
						if (!targets.empty())
						{
							ImGui::SeparatorText("Battle");
							{
								std::string targetStr = "Targets Health: (";
								int health = YuniUtil::GetCounterValue(enemyMaxLife);
								for (int i = 0; i < targets.size(); i++)
								{
									if (i > 0)
										targetStr += ", ";
									targetStr += std::to_string(health + YuniUtil::GetAlterableValue(targets[i], 11));
								}
								targetStr += ")";
								ImGui::Text(targetStr.c_str());
							}
						}
					}
				}
			}
        }
        ImGui::End();
	}

	static void UpdateObjPointers()
	{
		RunHeader* runHeader = GetRunHeader();
		if (runHeader->App->nCurrentFrame == 5)
		{
			battle = YuniUtil::GetFirstRunObjectFromName(_T("battle"));
			water = YuniUtil::GetFirstRunObjectFromName(_T("water"));
			enemyMaxLife = YuniUtil::GetFirstRunObjectFromName(_T("enemy max life"));
			character2 = YuniUtil::GetFirstRunObjectFromName(_T("character 2"));
		}
		else
			battle = water = enemyMaxLife = character2 = nullptr;
	}
};