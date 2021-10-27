#ifndef ADVERTISER_H_
#define ADVERTISER_H_

#include <BLEUUID.h>
#include "Task.h"

class Advertiser : Task
{
public:
    void start();
    void run();
    static void advertise(BLEUUID uuid);

private:
    // TODO: make both members non-static
    static TaskHandle_t m_advertiser;
    static QueueHandle_t m_queue;
};

#endif // ADVERTISER_H_