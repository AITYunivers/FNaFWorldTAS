#pragma once
#include "Edif/MMFWindowsMasterHeader.hpp"

extern RunHeader** GlobalRunHeaderPtr;
inline RunHeader* GetRunHeader()
{
    return *GlobalRunHeaderPtr;
}

extern CRunApp** GlobalCRunAppPtr;
inline CRunApp* GetCRunApp()
{
    return *GlobalCRunAppPtr;
}