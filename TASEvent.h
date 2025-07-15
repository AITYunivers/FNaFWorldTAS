#pragma once

class TASEvent
{
public:
    virtual ~TASEvent() = default;
    virtual bool Tick() { return true; };
};