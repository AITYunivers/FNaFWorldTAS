#pragma once
#include <WinUser.h>
#include "Edif/MMFWindowsMasterHeader.hpp"
#include "MMFGlobals.h"
#include "TAS.h"
#include "CEventProgramHook.h"
#include "MMFS2Hook.h"

namespace YuniUtil
{
	static bool IsKeyDown(char keyChar)
	{
		RunHeader* runHeader = GetRunHeader();
		HWND pHVar6 = GetActiveWindow();
		if (pHVar6 == runHeader->HTopLevelWnd ||
			pHVar6 == runHeader->HEditWin ||
			pHVar6 == runHeader->HMainWin)
		{
			if (TAS::IsKeyPressed(keyChar))
				return true;

			SHORT keyState = GetKeyState(keyChar);
			return keyState < 0;
		}
		return false;
	}

	static int GetEventIndex()
	{
		RunHeader* runHeader = GetRunHeader();
		int eventCount = 1;
		int pointer = (int)&runHeader->Frame->eventPrograms->evgSize;
		int end = (int)&runHeader->EventGroup->evgSize;
		while (pointer != end)
		{
			pointer -= ((eventGroup*)pointer)->evgSize;
			eventCount++;
		}
		return eventCount;
	}

	static void AdvanceExpToken()
	{
		RunHeader* runHeader = GetRunHeader();
		expression* expToken = runHeader->rh4.ExpToken;
		(runHeader->rh4).ExpToken = (expression*)(&expToken->u + expToken->size + -6);
	}

	static void SetReturnInt(int value)
	{
		RunHeader* runHeader = GetRunHeader();
		CValueMultiPlat* result = (CValueMultiPlat*)runHeader->rh4.Results[runHeader->rh4.PosPile];
		result->m_type = 0;
		result->m_long = value;
	}

	static uintptr_t GetParam(event2* ace, int index)
	{
		uintptr_t ptr = (uintptr_t)ace + sizeof(event2);
		for (int i = 0; i < index; i++)
		{
			short size = *(short*)ptr;
			ptr += size;
		}
		return ptr + 4;
	}

	static EventParam* GetEventParam(event2* ace, int index)
	{
		EventParam* ptr = (EventParam*)((uintptr_t)ace + sizeof(event2));
		for (int i = 0; i < index; i++)
			ptr += ptr->size;
		return ptr;
	}

	static event2* GetACE(eventGroup* evg, int index)
	{
		if (index >= (size_t)(evg->evgNCond + evg->evgNAct))
			return nullptr;

		uintptr_t ptr = (uintptr_t)evg + sizeof(eventGroup);
		for (int i = 0; i < index; i++)
		{
			short size = *(short*)ptr;
			ptr += size;
		}
		return (event2*)(ptr + 2);
	}

	static ObjInfo* GetOIFromName(std::tstring name)
	{
		CRunApp* app = GetCRunApp();
		for (int i = 0; i < app->oiMaxIndex; i++)
		{
			ObjInfo* oi = (ObjInfo*)app->ois[i];
			if (name.compare(oi->oiName) == 0)
				return oi;
		}
		return nullptr;
	}

	static RunObject* GetFirstRunObject(ObjInfo* oi)
	{
		RunHeader* runHeader = GetRunHeader();
		for (int i = 0; i < runHeader->NObjects; i++)
		{
			objectsList list = runHeader->ObjectList[i];
			RunObject* runObj = list.oblOffset;
			if (runObj != nullptr && runObj->rHo.Oi == oi->oiHdr.Handle)
				return runObj;
		}
		return nullptr;
	}

	static RunObject* GetFirstRunObjectFromName(std::tstring name)
	{
		ObjInfo* oi = GetOIFromName(name);
		if (oi != nullptr)
			return GetFirstRunObject(oi);
		return nullptr;
	}

	static std::vector<RunObject*> GetRunObjects(ObjInfo* oi)
	{
		std::vector<RunObject*> runObjs;
		RunHeader* runHeader = GetRunHeader();
		for (int i = 0; i < runHeader->NObjects; i++)
		{
			objectsList list = runHeader->ObjectList[i];
			RunObject* runObj = list.oblOffset;
			if (runObj != nullptr && runObj->rHo.Oi == oi->oiHdr.Handle)
				runObjs.push_back(runObj);
		}
		return runObjs;
	}

	static std::vector<RunObject*> GetRunObjectsFromName(std::tstring name)
	{
		ObjInfo* oi = GetOIFromName(name);
		if (oi != nullptr)
			return GetRunObjects(oi);
		return std::vector<RunObject*>();
	}

	static int GetCounterValue(RunObject* ro)
	{
		rs* systemObj = (rs*)ro;
		return systemObj->Value.m_long * -1 - 1;
	}

	static int GetAlterableValue(RunObject* ro, int index)
	{
		if (ro->rov.rvValueCount < index)
			return 0;
		return ro->rov.rvValues[index].m_long;
	}
}