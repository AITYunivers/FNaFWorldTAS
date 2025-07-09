#include <Windows.h>
#include <detours.h>
#include <string.h>
#include "CRunApp.h"

#include <thread>
#include <chrono>

int CRunApp::loopFrame()
{
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    return CRUNAPP_loopFrame();
}