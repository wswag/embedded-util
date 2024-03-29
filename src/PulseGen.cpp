#include "PulseGen.h"
#include <Arduino.h>

PulseGen::PulseGen(uint32_t interval)
{
    setInterval(interval);
    _autoReset = true;
    _init = false;
    _impulseMode = false;
    _impulseSent = false;
}

PulseGen::PulseGen(uint32_t interval, bool autoReset)
{
    setInterval(interval);
    _autoReset = autoReset;
    _init = false;
    _impulseMode = false;
    _impulseSent = false;
}

PulseGen::PulseGen(uint32_t interval, bool autoReset, bool impulseMode)
{
    setInterval(interval);
    _autoReset = autoReset;
    _init = false;
    _impulseMode = impulseMode;
    _impulseSent = false;
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
    _impulseSent = false;
}

void PulseGen::Set()
{
    Set(0);
}

void PulseGen::Set(uint32_t inMillis)
{
    _init = true;
    _lastTime = millis() - _interval + inMillis;
    _impulseSent = false;
}

bool PulseGen::Pulse()
{
    // first reset
    if (!_init) Reset();

    uint32_t currentTime = millis();
    // also works for roll over 0
    if (currentTime - _lastTime >= _interval)
    {
        bool result = !_impulseSent || !_impulseMode;
        _impulseSent = true;
        if (_autoReset) {
            _lastTime = currentTime;
            _impulseSent = false;
        }
        return result;
    }
    else
        return false;
}