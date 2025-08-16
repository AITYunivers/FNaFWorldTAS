#pragma once
#include "HookHelper.h"
#include "MMFGlobals.h"

CREATE_FUNC(CRUN_f_GameLoop, 0x29f40, int);
CREATE_FUNC(CRUN_calcMouseClientPos, 0x2a610, void);
CREATE_FUNC(CRUN_getExpression, 0x1f6f0, CValueMultiPlat*);
CREATE_FUNC(CRUN_prepareFrame, 0x459b0, int);
CREATE_FUNC(CRUN_createFrameObjects, 0x45d90, int, BOOL);
CREATE_FUNC(CRUN_joyTest, 0x2c850, void);
CREATE_FUNC(CRUN_allocRunHeader, 0x449e0, int);
CREATE_FUNC(CRUN_loadBanks, 0x333e0, int, unsigned int**);
CREATE_FUNC(CRUN_getBankInfo, 0x33060, unsigned int, int, unsigned int);
CREATE_FUNC(CRUN_delBankItem, 0x32f60, void, int, unsigned int);
CREATE_FUNC(CRUN_cleanBank, 0x32e30, void, int, unsigned int, unsigned int);
CREATE_FUNC(CRUN_loadBankItems, 0x33140, unsigned int, int, unsigned int);
CREATE_FUNC(CRUN_objectHide, 0x022f0, void, RunObject*);

class CRunHook
{
public:
	// Hooks
	static int __fastcall f_GameLoop();
	static void __fastcall calcMouseClientPos();
	static int __fastcall prepareFrame();
	static int __fastcall createFrameObjects(BOOL fade);
	static void __fastcall joyTest();
	static int __fastcall allocRunHeader();
	static int __fastcall loadBanks(unsigned int** tabAdCpt);
	static void __fastcall objectHide(RunObject* rHo);

	// Callbacks
	static CValueMultiPlat* getExpression()
	{
		return CRUN_getExpression();
	};

	static unsigned int getBankInfo(int bankId, unsigned int param)
	{
		return CRUN_getBankInfo(bankId, param);
	};

	static void delBankItem(int bankId, unsigned int param)
	{
		CRUN_delBankItem(bankId, param);
	};

	static void cleanBank(int bankId, unsigned int param1, unsigned int param2)
	{
		CRUN_cleanBank(bankId, param1, param2);
	};

	static unsigned int loadBankItems(int bankId, unsigned int param)
	{
		return CRUN_loadBankItems(bankId, param);
	};
};