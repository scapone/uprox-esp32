#include "Advertiser.h"
#include <Arduino.h>
#include "System.h"

TaskHandle_t Advertiser::m_advertiser = NULL;
QueueHandle_t Advertiser::m_queue = NULL;

void Advertiser::start()
{
    m_queue = xQueueCreate(1, sizeof(BLEUUID));
    if (m_queue == NULL)
    {
        log_e("Error creating queue!");
        System::halt();
    }

    
    m_advertiser = createTask("advertiser", DEFAULT_STACK_SIZE);
}

void Advertiser::run()
{
    while (true)
    {
        BLEUUID parcelUuid;
        if (xQueueReceive(m_queue, &parcelUuid, portMAX_DELAY) == pdTRUE)
        {
        }
    }
}

void Advertiser::advertise(BLEUUID parcelUuid)
{
    if (m_queue == NULL)
    {
        log_w("Advertiser queue must be created first!");
        return;
    }

    if (xQueueOverwrite(m_queue, &parcelUuid) != pdPASS)
        log_e("Error sending parcel UUID!");
}

