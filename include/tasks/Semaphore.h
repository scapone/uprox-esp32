#ifndef SEMAPHORE_H_
#define SEMAPHORE_H_

#include <Arduino.h>

class Semaphore
{
public:
    Semaphore();
    void give();
    bool take();
    bool take(uint32_t timeoutMs);

private:
    SemaphoreHandle_t m_semaphore;
};

#endif // SEMAPHORE_H_