#include "PulseGen.h"
#include <Arduino.h>

PulseGen::PulseGen(uint32_t interval)
{
    setInterval(interval);
    _autoReset = true;
    _init = false;
}

PulseGen::PulseGen(uint32_t interval, bool autoReset)
{
    setInterval(interval);
    _autoReset = autoReset;
    _init = false;
}

void PulseGen::setInterval(uint32_t interval)
{
    _interval = interval;
}

uint32_t PulseGen::getInterval() 
{
    return _interval;
}

void PulseGen::Reset()
{
    _init = true;
    _lastTime = millis();
}

void PulseGen::Set()
{
    Set(0);
}

void PulseGen::Set(uint32_t inMillis)
{
    _init = true;
    _lastTime = millis() - _interval + inMillis;
}

bool PulseGen::Pulse()
{
    // first reset
    if (!_init) Reset();

    uint32_t currentTime = millis();
    // also works for roll over 0
    if (currentTime - _lastTime >= _interval)
    {
        if (_autoReset)
            _lastTime = currentTime;
        return true;
    }
    else
        return false;
}