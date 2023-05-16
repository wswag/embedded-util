#include "RegisterString.h"

size_t RegisterStringInterface::length() 
{
    return strlen(getBuffer());
}

void RegisterStringInterface::setLength(size_t value) 
{
    auto cap = getCapacity();
    auto len = value > cap ? cap : value;
    getBuffer()[len] = 0;
}
void RegisterStringInterface::setFrom(const char* src) 
{
    int len = strlen(src);
    auto cap = getCapacity();
    len = len > cap ? cap : len;
    auto buffer = getBuffer();
    memcpy(buffer, src, len);
    setLength(len);
}
