#ifndef REGISTERSTRING_H
#define REGISTERSTRING_H

#include <stddef.h>
#include <stdint.h>
#include <string.h>

class RegisterStringInterface {
    private:
        size_t _len;
    public:
        virtual ~RegisterStringInterface() {}
        virtual char* getBuffer() = 0;
        virtual uint16_t getCapacity() = 0;

        void setFrom(const char* src);
        size_t length();
        void setLength(size_t value);
};

template<int REGS_SIZE>
class RegisterString : public RegisterStringInterface {
    private:
        char buffer[REGS_SIZE+1]; // preserve a trailing zero
    public:
        RegisterString<REGS_SIZE>& operator=(const char* rvalue);
        bool operator==(const char* rvalue);
        bool operator<(const char* rvalue);
        bool operator>(const char* rvalue);
        bool operator!=(const char* rvalue);
        bool operator>=(const char* rvalue);
        bool operator<=(const char* rvalue);

        char* getBuffer() override;

        virtual uint16_t getCapacity() override;

};

template<int REGS_SIZE>
RegisterString<REGS_SIZE>& RegisterString<REGS_SIZE>::operator=(const char* rvalue) 
{
    setFrom(rvalue);
    return *this;
}

template<int REGS_SIZE>
bool RegisterString<REGS_SIZE>::operator==(const char* rvalue) 
{
    return strcmp(buffer, rvalue) == 0;
}

template<int REGS_SIZE>
bool RegisterString<REGS_SIZE>::operator<(const char* rvalue) 
{
    return strcmp(buffer, rvalue) == -1;
}

template<int REGS_SIZE>
bool RegisterString<REGS_SIZE>::operator>(const char* rvalue) 
{
    return strcmp(buffer, rvalue) == 1;
}

template<int REGS_SIZE>
bool RegisterString<REGS_SIZE>::operator!=(const char* rvalue) 
{
    return strcmp(buffer, rvalue) != 0;
}

template<int REGS_SIZE>
bool RegisterString<REGS_SIZE>::operator>=(const char* rvalue) 
{
    int result = strcmp(buffer, rvalue);
    return result == 0 || result == 1;
}

template<int REGS_SIZE>
bool RegisterString<REGS_SIZE>::operator<=(const char* rvalue) 
{
    int result = strcmp(buffer, rvalue);
    return result == 0 || result == -1;
}

template<int REGS_SIZE>
char* RegisterString<REGS_SIZE>::getBuffer() 
{
    return buffer;
}

template<int REGS_SIZE>
uint16_t RegisterString<REGS_SIZE>::getCapacity() 
{
    return REGS_SIZE;
}

#endif /* REGISTERSTRING_H */
