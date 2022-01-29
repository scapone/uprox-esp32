#ifndef ADVERTISER_H_
#define ADVERTISER_H_

#include <BLEUUID.h>
#include "Task.h"
#include "tasks/Semaphore.h"

class Advertiser : Task
{
public:
    Advertiser(Semaphore &semaphore);
    void start();
    void run();
    static void advertise(BLEUUID uuid);

private:
    // TODO: make both members non-static
    static TaskHandle_t m_advertiser;
    static QueueHandle_t m_queue;
    Semaphore &m_semaphore;
};

#endif // ADVERTISER_H_