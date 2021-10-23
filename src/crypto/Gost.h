#ifndef GOST_H_
#define GOST_H_

#include <stdint.h>

class Gost
{
private:
    int m_subkeyArray[8];
    uint64_t process(uint64_t dataBlock, const uint8_t cipherArray[]);
public:
    Gost(int magicNumber);
    uint64_t encrypt(const uint64_t dataBlock);
};

#endif // GOST_H_