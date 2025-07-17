#pragma once
#include <d3d9.h>
#include <imgui.h>
#include "YuniUtil.h"

class Debug
{
public:
	// Statics
	static RunObject *charge1,
					 *charge2,
					 *charge3,
					 *charge4,
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
			}

			if (runHeader->App->nCurrentFrame == 5)
			{
				ImGui::SeparatorText("Counter Values");
				{
					ImGui::Text(("charge 1: " + std::to_string(YuniUtil::GetCounterValue(charge1))).c_str());
					ImGui::Text(("charge 2: " + std::to_string(YuniUtil::GetCounterValue(charge2))).c_str());
					ImGui::Text(("charge 3: " + std::to_string(YuniUtil::GetCounterValue(charge3))).c_str());
					ImGui::Text(("charge 4: " + std::to_string(YuniUtil::GetCounterValue(charge4))).c_str());
					
					ImGui::Text(("Character 2 AltVal E: " + std::to_string(YuniUtil::GetAlterableValue(character2, 4))).c_str());
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
			charge1 = YuniUtil::GetFirstRunObjectFromName(_T("charge 1"));
			charge2 = YuniUtil::GetFirstRunObjectFromName(_T("charge 2"));
			charge3 = YuniUtil::GetFirstRunObjectFromName(_T("charge 3"));
			charge4 = YuniUtil::GetFirstRunObjectFromName(_T("charge 4"));
			character2 = YuniUtil::GetFirstRunObjectFromName(_T("character 2"));
		}
		else
			charge1 = charge2 = charge3 = charge4 = character2 = nullptr;
	}
};