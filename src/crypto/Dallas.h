#ifndef _DALLAS_H
#define _DALLAS_H

#include <stdint.h>

class Dallas
{
public:
    static uint8_t crc8(const uint8_t byteArray[], int startIndex, int endIndex);
};

#endif // _DALLAS_H