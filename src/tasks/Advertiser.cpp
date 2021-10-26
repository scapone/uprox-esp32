#include "Advertiser.h"
#include <Arduino.h>

void Advertiser::start()
{
    createTask("advertiser", DEFAULT_STACK_SIZE);
}

void Advertiser::run()
{
    while (true)
    {
        uint32_t notifyValue;
        if (xTaskNotifyWait(0, 0, &notifyValue, portMAX_DELAY) == pdTRUE)
        {
        }
    }
}
