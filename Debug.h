#pragma once
#include <d3d9.h>
#include <imgui.h>
#include "YuniUtil.h"
#include "TASWait.h"
#include "TASWaitForFrame.h"
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
#include "TASKeyPress.h"
#include "TASClickAt.h"

class Debug
{
public:
	// Statics
	static RunObject *battle,
					 *water,
					 *enemyMaxLife,
					 *shop3;
	static std::vector<RunObject*> charges;

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
					else if (TASWaitForDeedee* waitDeedeeEvt = dynamic_cast<TASWaitForDeedee*>(event))
						ImGui::Text("Waiting for Deedee");
					else if (TASWaitForAttacksReady* waitAttacksEvt = dynamic_cast<TASWaitForAttacksReady*>(event))
						ImGui::Text("Waiting for attacks to be ready");
					else if (TASWaitUntilChipsBtn* waitChipsBtnEvt = dynamic_cast<TASWaitUntilChipsBtn*>(event))
						ImGui::Text("Waiting for chips button to be clickable");
					else if (TASWaitForVictory* waitVictoryEvt = dynamic_cast<TASWaitForVictory*>(event))
						ImGui::Text("Waiting for victory");
					else if (TASWaitForBattleEnd* waitBattleEndEvt = dynamic_cast<TASWaitForBattleEnd*>(event))
						ImGui::Text("Waiting for the battle to end");
					else if (TASWaitForCinematicEnd* waitCineEvt = dynamic_cast<TASWaitForCinematicEnd*>(event))
						ImGui::Text("Waiting for cinematic to end");
					else if (TASWaitForTokens* waitTokensEvt = dynamic_cast<TASWaitForTokens*>(event))
						ImGui::Text("Waiting for tokens");
					else if (TASKeyPressUntilFrame* keyPressFrameEvt = dynamic_cast<TASKeyPressUntilFrame*>(event))
						ImGui::Text(("Pressing " + std::to_string(keyPressFrameEvt->keyCodes.size()) + " key(s) until frame " + std::to_string(keyPressFrameEvt->frame)).c_str());
					else if (TASKeyPressUntilBattle* keyPressBattleEvt = dynamic_cast<TASKeyPressUntilBattle*>(event))
						ImGui::Text(("Pressing " + std::to_string(keyPressBattleEvt->keyCodes.size()) + " key(s) until battle").c_str());
					else if (TASKeyPressUntilChip* keyPressChipEvt = dynamic_cast<TASKeyPressUntilChip*>(event))
						ImGui::Text(("Pressing " + std::to_string(keyPressBattleEvt->keyCodes.size()) + " key(s) until chip").c_str());
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
					bool deedee = YuniUtil::GetAlterableValue(shop3, 4) != 1;
					ImGui::Text(("Deedee Ready: " + std::string(deedee ? "True" : "False")).c_str());

					if (inBattle)
					{
						std::vector<RunObject*> targets = YuniUtil::GetRunObjectsFromName(_T("target"));

						if (!targets.empty() || !charges.empty())
							ImGui::SeparatorText("Battle");
						
						if (!targets.empty())
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

						if (!charges.empty())
						{
							std::string chargeStr = "Charges: (";
							for (int i = 0; i < charges.size(); i++)
							{
								if (i > 0)
									chargeStr += ", ";
								chargeStr += std::to_string(YuniUtil::GetCounterValue(charges[i]));
							}
							chargeStr += ")";
							ImGui::Text(chargeStr.c_str());
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
			shop3 = YuniUtil::GetFirstRunObjectFromName(_T("shop 3"));
			charges.push_back(YuniUtil::GetFirstRunObjectFromName(_T("charge 1")));
			charges.push_back(YuniUtil::GetFirstRunObjectFromName(_T("charge 2")));
			charges.push_back(YuniUtil::GetFirstRunObjectFromName(_T("charge 3")));
			charges.push_back(YuniUtil::GetFirstRunObjectFromName(_T("charge 4")));
			charges.push_back(YuniUtil::GetFirstRunObjectFromName(_T("charge 5")));
			charges.push_back(YuniUtil::GetFirstRunObjectFromName(_T("charge 6")));
			charges.push_back(YuniUtil::GetFirstRunObjectFromName(_T("charge 7")));
			charges.push_back(YuniUtil::GetFirstRunObjectFromName(_T("charge 8")));
		}
		else
		{
			battle = water = enemyMaxLife = shop3 = nullptr;
			charges.clear();
		}
	}
};