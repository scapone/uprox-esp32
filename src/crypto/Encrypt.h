#ifndef _ENCRYPT_H
#define _ENCRYPT_H

#include <BLEUUID.h>

class Encrypt
{
public:
    static BLEUUID createParcelUuid(int magicNumber);
};

#endif // _ENCRYPT_H