#pragma once
#include "CRunHook.h"
#include "TAS.h"
#include "CEventProgramHook.h"
#include "YuniUtil.h"
#include "EXP_RANDOMHook.h"
#include "Debug.h"
#include "CImageBankHook.h"

int CRunHook::f_GameLoop()
{
    RunHeader* runHeader = GetRunHeader();

    // Create TAS Thread
    if (!TAS::running)
    {
        std::thread t(TAS::Run);
        t.detach();
    }

    TAS::TickQueue();

    EXP_RANDOMHook::expIndex = 0;
    EXP_RANDOMHook::expEvent = -1;

    return CRUN_f_GameLoop();
}

void CRunHook::calcMouseClientPos()
{
    if (TAS::mousePos != nullptr)
    {
        RunHeader* runHeader = GetRunHeader();
        runHeader->rh2.MouseClient.x = TAS::mousePos->x;
        runHeader->rh2.MouseClient.y = TAS::mousePos->y;
        runHeader->rh2.Mouse.x = runHeader->rh2.MouseClient.x + runHeader->WindowX;
        runHeader->rh2.Mouse.y = runHeader->rh2.MouseClient.y + runHeader->WindowY;
    }
    else
        CRUN_calcMouseClientPos();
}

int CRunHook::prepareFrame()
{
    // Fade Skip
    RunHeader* runHeader = GetRunHeader();
    if (runHeader->Frame->fadeOut != nullptr)
    {
        std::string type((char*)runHeader->Frame->fadeOut, 8);
        if (type == "STDTFADE")
            runHeader->Frame->fadeOut = nullptr;
    }

    // Disable Timer-Based Movements
    runHeader->Frame->hdr.Flags &= ~LTIMEDMVTS;

    return CRUN_prepareFrame();
}

int CRunHook::createFrameObjects(BOOL fade)
{
    int ret = CRUN_createFrameObjects(fade);
    Debug::UpdateObjPointers();
    return ret;
}

void CRunHook::joyTest()
{
    RunHeader* runHeader = GetRunHeader();
    runHeader->TimerDelta = (unsigned int)(1 / 60.0f * 1000);
    runHeader->rh4.mvtTimerCoef = ((double)runHeader->TimerDelta) * ((double)runHeader->Frame->MvtTimerBase) / 1000.0;

    return CRUN_joyTest();
}

int CRunHook::allocRunHeader()
{
    return CRUN_allocRunHeader();
}

int __fastcall CRunHook::loadBanks(unsigned int** tabAdCpt)
{
	printf("CRunHook::loadBanks\n");
	void* GlobalBankLock = GetBankLock();
	CRunApp* GlobalCRunApp = GetCRunApp();

    int bankInfo;
    unsigned int uVar1;
    unsigned short uVar2;
    int bankId;
    unsigned int* puVar3;
    unsigned int storedMem;
    unsigned int* bankUsage;
    unsigned short mem;
    unsigned short* memIndex;

    MMFS2Hook::LockBank(GlobalBankLock, 0xffffffff);
    CImageBankHook::UnloadImages();
    CImageBankHook::UnloadImages2();
    bankId = 0;
    do {
        bankUsage = tabAdCpt[bankId];
        memIndex = GlobalCRunApp->EltDiskToMem[bankId];
        uVar2 = 0;
        if (GlobalCRunApp->nbEltOff[bankId] != 0) {
            do {
                mem = memIndex[uVar2];
                storedMem = (unsigned int)mem;
                if (mem != 0) {
                    if (*bankUsage == 0) {
                        if (((bankId != 2) && (bankId != 3)) ||
                            (bankInfo = MMFS2Hook::IsSndPlaying(GlobalBankLock, storedMem), bankInfo == 0)) {
                            bankInfo = getBankInfo(bankId, storedMem);
                            while (bankInfo != 0) {
                                delBankItem(bankId, storedMem);
                                bankInfo = getBankInfo(bankId, storedMem);
                            }
                            cleanBank(bankId, (unsigned int)uVar2, 0);
                        }
                    }
                    else {
                        bankInfo = getBankInfo(bankId, storedMem);
                        if (bankInfo == 0) {
                            memIndex[uVar2] = 0;
                        }
                        else {
                            uVar1 = getBankInfo(bankId, storedMem);
                            if (*bankUsage < uVar1) {
                                do {
                                    delBankItem(bankId, storedMem);
                                    uVar1 = getBankInfo(bankId, storedMem);
                                } while (*bankUsage < uVar1);
                            }
                            uVar1 = getBankInfo(bankId, storedMem);
                            if (uVar1 < *bankUsage) {
                                do {
                                    switch (bankId) {
                                    case 0:
                                        MMFS2Hook::IncImageCount(GlobalCRunApp->idAppli, storedMem);
                                        break;
                                    case 1:
                                        MMFS2Hook::IncFontCount(GlobalCRunApp->idAppli, storedMem);
                                        break;
                                    case 2:
                                    case 3:
                                        MMFS2Hook::IncSoundCount(GlobalCRunApp->idAppli, storedMem);
                                    }
                                    uVar1 = getBankInfo(bankId, storedMem);
                                } while (uVar1 < *bankUsage);
                            }
                            *bankUsage = (0u - storedMem);
                        }
                    }
                }
                uVar2 = uVar2 + 1;
                bankUsage = bankUsage + 1;
            } while (uVar2 < GlobalCRunApp->nbEltOff[bankId]);
        }
        bankId = bankId + 1;
    } while (bankId < 4);
    bankId = 0;
    do {
        bankUsage = tabAdCpt[bankId];
        uVar2 = 0;
        puVar3 = bankUsage;
        if (GlobalCRunApp->nbEltOff[bankId] != 0) {
            do {
                storedMem = *puVar3;
                if (storedMem != 0) {
                    if ((int)storedMem < 0) {
                        storedMem = (unsigned int)(unsigned short)-(short)storedMem;
                    }
                    else {
                        uVar1 = loadBankItems(bankId, (unsigned int)uVar2);
                        storedMem = uVar1 & 0xffff;
                        if ((short)uVar1 != 0) {
                            *puVar3 = *puVar3 - 1;
                            uVar1 = *puVar3;
                            while (uVar1 != 0) {
                                switch (bankId) {
                                case 0:
                                    MMFS2Hook::IncImageCount(GlobalCRunApp->idAppli, storedMem);
                                    break;
                                case 1:
                                    MMFS2Hook::IncFontCount(GlobalCRunApp->idAppli, storedMem);
                                    break;
                                case 2:
                                case 3:
                                    MMFS2Hook::IncSoundCount(GlobalCRunApp->idAppli, storedMem);
                                }
                                *puVar3 = *puVar3 - 1;
                                uVar1 = *puVar3;
                            }
                        }
                    }
                }
                *(short*)bankUsage = (short)storedMem;
                uVar2 = uVar2 + 1;
                bankUsage = (unsigned int*)((int)bankUsage + 2);
                puVar3 = puVar3 + 1;
            } while (uVar2 < GlobalCRunApp->nbEltOff[bankId]);
        }
        bankId = bankId + 1;
    } while (bankId < 4);
    return MMFS2Hook::UnlockBank(GlobalBankLock, 0xffffffff);
}

void __fastcall CRunHook::objectHide(RunObject* rHo)
{
	CRUN_objectHide(rHo);
}