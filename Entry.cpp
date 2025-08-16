// dllmain.cpp : Defines the entry point for the DLL application.
#include "MMFGlobals.h"
#include "HookHelper.h"
#include "CRunHook.h"
#include "CRunAppHook.h"
#include "CEventProgramHook.h"
#include "CImageBankHook.h"
#include "EXP_RANDOMHook.h"
#include "CND_KEYDEPRESSEDHook.h"
#include "CND_KBPRESSKEYHook.h"
#include "CND_EXTCHOOSEHook.h"
#include "CNDL_MCLICKHook.h"
#include "CNDL_MCLICKONOBJECTHook.h"
#include "CND_TIMERSUPHook.h"
#include "TAS.h"
#include "timeapi.h"

std::vector<std::tuple<PVOID*, PVOID>> hooks;

BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD   ul_reason_for_call,
                      LPVOID  lpReserved)
{
    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
        {
            //AllocConsole();
            //FILE* dummy;
            //freopen_s(&dummy, "CONOUT$", "w", stdout); // Redirects std::cout
            //freopen_s(&dummy, "CONOUT$", "w", stderr); // Redirects std::cerr
            //freopen_s(&dummy, "CONIN$", "r", stdin);   // Redirects std::cin

            // Register globals here
            {
                GlobalRunHeaderPtr = reinterpret_cast<RunHeader**>(GET_ADDRESS(0xAC9B4));
                GlobalCRunAppPtr = reinterpret_cast<CRunApp**>(GET_ADDRESS(0xAC9AC));
                GlobalBankLockPtr = reinterpret_cast<void**>(GET_ADDRESS(0xAC97C));
            }

            // Register hooks here
            {
                // Expressions
                registerHook(&(PVOID&)EXP_RANDOM_evaluate, &EXP_RANDOMHook::evaluate);

                // Conditions
                registerHook(&(PVOID&)CND_KEYDEPRESSED_evaluate, &CND_KEYDEPRESSEDHook::evaluate);
                registerHook(&(PVOID&)CND_KBPRESSKEY_evaluate, &CND_KBPRESSKEYHook::evaluate);
                registerHook(&(PVOID&)CND_EXTCHOOSE_evaluate, &CND_EXTCHOOSEHook::evaluate);
                registerHook(&(PVOID&)CND_TIMERSUP_evaluate, &CND_TIMERSUPHook::evaluate);

                // Immediate Conditions
                registerHook(&(PVOID&)CNDL_MCLICK_evaluate, &CNDL_MCLICKHook::evaluate);
                registerHook(&(PVOID&)CNDL_MCLICKONOBJECT_evaluate, &CNDL_MCLICKONOBJECTHook::evaluate);

                // Event Program
                registerHook(&(PVOID&)CEVENTPROGRAM_handle_GlobalEvents, &CEventProgramHook::handle_GlobalEvents);
            
                // CRun
                registerHook(&(PVOID&)CRUN_f_GameLoop, &CRunHook::f_GameLoop);
                registerHook(&(PVOID&)CRUN_calcMouseClientPos, &CRunHook::calcMouseClientPos);
                registerHook(&(PVOID&)CRUN_prepareFrame, &CRunHook::prepareFrame);
                registerHook(&(PVOID&)CRUN_createFrameObjects, &CRunHook::createFrameObjects);
                registerHook(&(PVOID&)CRUN_joyTest, &CRunHook::joyTest);
                registerHook(&(PVOID&)CRUN_allocRunHeader, &CRunHook::allocRunHeader);
                //registerHook(&(PVOID&)CRUN_loadBanks, &CRunHook::loadBanks);
                registerHook(&(PVOID&)CRUN_objectHide, &CRunHook::objectHide);

                // CRunApp
                registerHook(&(PVOID&)CRUNAPP_playApplication, &CRunAppHook::playApplication);
            }
            break;
        }
    }

    return TRUE;
}

// MMFGlobals.h
RunHeader** GlobalRunHeaderPtr = nullptr;
RunHeader* GetRunHeader();
CRunApp** GlobalCRunAppPtr = nullptr;
CRunApp* GetCRunApp();
void** GlobalBankLockPtr = nullptr;
void* GetBankLock();