#pragma once
#include "Edif/MMFWindowsMasterHeader.hpp"

extern RunHeader** GlobalRunHeaderPtr;
inline RunHeader* GetRunHeader()
{
    return *GlobalRunHeaderPtr;
}