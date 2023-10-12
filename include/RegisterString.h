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
        virtual const char* getBuffer() const = 0;
        virtual uint16_t getCapacity() const = 0;

        void setFrom(const char* src);
        size_t length() const;
        void setLength(size_t value);
};

template<int REGS_SIZE>
class RegisterString : public RegisterStringInterface {
    private:
        char buffer[REGS_SIZE+1]; // preserve a trailing zero
    public:
        RegisterString<REGS_SIZE>& operator=(const char* rvalue);
        bool operator==(const char* rvalue) const;
        bool operator<(const char* rvalue) const;
        bool operator>(const char* rvalue) const;
        bool operator!=(const char* rvalue) const;
        bool operator>=(const char* rvalue) const;
        bool operator<=(const char* rvalue) const;

        const char* getBuffer() const override;

        virtual uint16_t getCapacity() const override;

};

template<int REGS_SIZE>
RegisterString<REGS_SIZE>& RegisterString<REGS_SIZE>::operator=(const char* rvalue) 
{
    setFrom(rvalue);
    return *this;
}

template<int REGS_SIZE>
bool RegisterString<REGS_SIZE>::operator==(const char* rvalue) const
{
    return strcmp(buffer, rvalue) == 0;
}

template<int REGS_SIZE>
bool RegisterString<REGS_SIZE>::operator<(const char* rvalue) const
{
    return strcmp(buffer, rvalue) == -1;
}

template<int REGS_SIZE>
bool RegisterString<REGS_SIZE>::operator>(const char* rvalue) const
{
    return strcmp(buffer, rvalue) == 1;
}

template<int REGS_SIZE>
bool RegisterString<REGS_SIZE>::operator!=(const char* rvalue) const
{
    return strcmp(buffer, rvalue) != 0;
}

template<int REGS_SIZE>
bool RegisterString<REGS_SIZE>::operator>=(const char* rvalue) const
{
    int result = strcmp(buffer, rvalue);
    return result == 0 || result == 1;
}

template<int REGS_SIZE>
bool RegisterString<REGS_SIZE>::operator<=(const char* rvalue) const
{
    int result = strcmp(buffer, rvalue);
    return result == 0 || result == -1;
}

template<int REGS_SIZE>
const char* RegisterString<REGS_SIZE>::getBuffer() const
{
    return buffer;
}

template<int REGS_SIZE>
uint16_t RegisterString<REGS_SIZE>::getCapacity() const
{
    return REGS_SIZE;
}

#endif /* REGISTERSTRING_H */
