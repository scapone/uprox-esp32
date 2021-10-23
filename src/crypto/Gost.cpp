#include "Gost.h"
#include <stdint.h>

const uint8_t sboxArray[8][16] = {
    { 13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7 },
    { 4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1 },
    { 12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11 },
    { 2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9 },
    { 7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15 },
    { 10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8 },
    { 15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10 },
    { 14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7 }
};

const uint8_t encryptArray[32] = {
  0, 1, 2, 3, 4, 5, 6, 7,
  0, 1, 2, 3, 4, 5, 6, 7,
  0, 1, 2, 3, 4, 5, 6, 7,
  7, 6, 5, 4, 3, 2, 1, 0 
};

const uint8_t decryptArray[32] = {
  0, 1, 2, 3, 4, 5, 6, 7,
  7, 6, 5, 4, 3, 2, 1, 0,
  7, 6, 5, 4, 3, 2, 1, 0,
  7, 6, 5, 4, 3, 2, 1, 0
};

Gost::Gost(int magicNumber) :
    m_subkeyArray{magicNumber, 1620462276, -1490187195, 1124710742, -1374507497, -2067643655, -1440596042, -591548382}
{
}

uint64_t Gost::encrypt(uint64_t dataBlock)
{
    return process(dataBlock, encryptArray);
}

uint64_t Gost::process(uint64_t dataBlock, const uint8_t cipherArray[])
{
    uint32_t rightHalf = dataBlock;
    uint32_t leftHalf = dataBlock >> 32;

    for (int round = 0; round < 32; round++)
    {
        const int subkey = m_subkeyArray[cipherArray[round]];
      
        uint32_t input = rightHalf + subkey;
        uint32_t output = 0;

        for (int i = 0; i < 8; i++) {
            const uint32_t sboxOutput = sboxArray[i][(input & 0xF)];
            output = sboxOutput << i * 4 | output;

            input = input >> 4;
        } 
        
        output = (output << 11) | (output >> 21); // rotate 11 bit left for Integer (32 bit)
        output = leftHalf ^ output;

        leftHalf = rightHalf;
        rightHalf = output;           
    }

    dataBlock = (uint64_t)rightHalf << 32 | leftHalf;
    return dataBlock;
}
