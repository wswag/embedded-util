#ifndef PULSEGEN_H
#define PULSEGEN_H

#include <stdint.h>

class PulseGen
{
    private:
        uint32_t _lastTime;
        uint32_t _interval;
        bool _autoReset;
        bool _init;
        bool _impulseMode;
        bool _impulseSent;
    public:
        PulseGen(uint32_t interval);
        PulseGen(uint32_t interval, bool autoReset);
        PulseGen(uint32_t interval, bool autoReset, bool impulseMode);
        void setInterval(uint32_t interval);
        uint32_t getInterval();
        void Reset();
        void Set();
        void Set(uint32_t inMillis);
        bool Pulse();
};

#endif