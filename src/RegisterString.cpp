#include "RegisterString.h"

size_t RegisterStringInterface::length() const
{
    return strlen(getBuffer());
}

