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
        virtual char* getMutableBuffer() = 0;
        virtual uint16_t getCapacity() const = 0;

        size_t length() const;
        virtual void setFrom(const char* src) = 0;
        virtual void setLength(size_t value) = 0;
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

        void setFrom(const char* src) override;
        void setLength(size_t value) override;

        const char* getBuffer() const override;
        char* getMutableBuffer() override;

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
char* RegisterString<REGS_SIZE>::getMutableBuffer()
{
    return buffer;
}

template<int REGS_SIZE>
uint16_t RegisterString<REGS_SIZE>::getCapacity() const
{
    return REGS_SIZE;
}

template<int REGS_SIZE>
void RegisterString<REGS_SIZE>::setLength(size_t value) 
{
    auto cap = getCapacity();
    auto len = value > cap ? cap : value;
    buffer[len] = 0;
}

template<int REGS_SIZE>
void RegisterString<REGS_SIZE>::setFrom(const char* src) 
{
    if (src == nullptr) {
        setLength(0);
        return;
    }
    int len = strlen(src);
    auto cap = getCapacity();
    len = len > cap ? cap : len;
    memcpy(buffer, src, len);
    setLength(len);
}

#endif /* REGISTERSTRING_H */
