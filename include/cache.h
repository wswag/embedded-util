#ifndef CACHE_H
#define CACHE_H

#include <stdint.h>
#include <string.h>

template<uint32_t CAPACITY, typename TChunkLength>
class Cache {
    private:
        uint8_t _buffer[CAPACITY];
        uint32_t _readcursor = 0;
        uint32_t _writecursor = 0;
        uint32_t _chunksCount = 0;
        uint32_t _occupiedBytes = 0;

        void writeRing(const uint8_t* data, uint32_t dataLen);
        void readRing(uint8_t* dst, uint32_t dataLen, bool peek);

    public:
        Cache();

        bool enqueue(const uint8_t* data, TChunkLength dataLen);
        TChunkLength dequeue(void* dst);
        TChunkLength peekNextLen();
};

template<uint32_t CAPACITY, typename TChunkLength>
void Cache<CAPACITY, TChunkLength>::writeRing(const uint8_t* data, uint32_t dataLen) 
{
    if (dataLen < CAPACITY) {
        uint32_t nextCursorPos = (_writecursor + dataLen) % CAPACITY;
        // swap ring buffer
        if (nextCursorPos < _writecursor) {
            int part1 = CAPACITY - _writecursor;
            memcpy(&_buffer[_writecursor], data, part1);
            memcpy(_buffer, data + part1, dataLen - part1);
        }
        else {
            memcpy(&_buffer[_writecursor], data, dataLen);
        }
        _occupiedBytes += dataLen;
        _writecursor = nextCursorPos;
    }
}

template<uint32_t CAPACITY, typename TChunkLength>
void Cache<CAPACITY, TChunkLength>::readRing(uint8_t* dst, uint32_t dataLen, bool peek) 
{
    if (dataLen < CAPACITY) {
        uint32_t nextCursorPos = (_readcursor + dataLen) % CAPACITY;
        // swap ring buffer
        if (nextCursorPos < _readcursor) {
            int part1 = CAPACITY - _readcursor;
            memcpy(dst, &_buffer[_readcursor], part1);
            memcpy(dst + part1, _buffer, dataLen - part1);
        }
        else {
            memcpy(dst, &_buffer[_writecursor], dataLen);
        }
        if (!peek) {
            _readcursor = nextCursorPos;
            _occupiedBytes -= dataLen;
        }
    }
}

template<uint32_t CAPACITY, typename TChunkLength>
Cache<CAPACITY, TChunkLength>::Cache() 
{
    memset(_buffer, 0, CAPACITY);
}

template<uint32_t CAPACITY, typename TChunkLength>
bool Cache<CAPACITY, TChunkLength>::enqueue(const uint8_t* data, TChunkLength dataLen) 
{
    uint32_t alloc = dataLen + sizeof(TChunkLength);
    if (_occupiedBytes + alloc > CAPACITY) {
        return false;
    }

    Serial.println("Write header"); Serial.flush();
    writeRing(&dataLen, sizeof(TChunkLength));
    Serial.println("Write data"); Serial.flush();
    writeRing(data, dataLen);
    Serial.println("done"); Serial.flush();
    _chunksCount++;
    return true;
}

template<uint32_t CAPACITY, typename TChunkLength>
TChunkLength Cache<CAPACITY, TChunkLength>::dequeue(void* dst) 
{
    if (_chunksCount == 0) return 0;
    
    TChunkLength len;
    readRing((uint8_t*)&len, sizeof(TChunkLength), false);
    readRing((uint8_t*)dst, len, false);
    
    _chunksCount--;
    return len;
}

template<uint32_t CAPACITY, typename TChunkLength>
TChunkLength Cache<CAPACITY, TChunkLength>::peekNextLen() 
{
    if (_chunksCount == 0) return 0;
    TChunkLength len;
    readRing((uint8_t*)&len, sizeof(TChunkLength), true);
    return len;
}


#endif /* CACHE_H */
