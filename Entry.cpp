// dllmain.cpp : Defines the entry point for the DLL application.
#include "MMFGlobals.h"
#include "HookHelper.h"
#include "CRunHook.h"
#include "CEventProgramHook.h"
#include "EXP_RANDOMHook.h"
#include "CND_KEYDEPRESSEDHook.h"
#include "CNDL_MCLICKHook.h"
#include "CNDL_MCLICKONOBJECTHook.h"

std::vector<std::tuple<PVOID*, PVOID>> hooks;

BOOL APIENTRY DllMain(HMODULE hModule,
                      DWORD   ul_reason_for_call,
                      LPVOID  lpReserved)
{
    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
        {
            // Register globals here
            GlobalRunHeaderPtr = reinterpret_cast<RunHeader**>(GET_ADDRESS(0xAC9B4));

            // Register hooks here
            {
                // Expressions
                registerHook(&(PVOID&)EXP_RANDOM_evaluate, &EXP_RANDOMHook::evaluate);

                // Conditions
                registerHook(&(PVOID&)CND_KEYDEPRESSED_evaluate, &CND_KEYDEPRESSEDHook::evaluate);

                // Immediate Conditions
                registerHook(&(PVOID&)CNDL_MCLICK_evaluate, &CNDL_MCLICKHook::evaluate);
                registerHook(&(PVOID&)CNDL_MCLICKONOBJECT_evaluate, &CNDL_MCLICKONOBJECTHook::evaluate);

                // Event Program
                registerHook(&(PVOID&)CEVENTPROGRAM_handle_GlobalEvents, &CEventProgramHook::handle_GlobalEvents);
            }
            break;
        }
    }

    return TRUE;
}

// MMFGlobals.h
RunHeader** GlobalRunHeaderPtr = nullptr;
RunHeader* GetRunHeader();