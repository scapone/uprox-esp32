#include "Advertiser.h"

#include <Arduino.h>
#include <BLEDevice.h>

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
        //BLEUUID parcelUuid("12d1b564-9595-bea5-1972-0939fb4a4dea");
        BLEUUID parcelUuid;
        if (xQueueReceive(m_queue, &parcelUuid, portMAX_DELAY) == pdTRUE)
        {
            BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
            pAdvertising->addServiceUUID(parcelUuid);
            pAdvertising->start();
            vTaskDelay(pdMS_TO_TICKS(1000));
            pAdvertising->stop();
        }
    }
}

void Advertiser::advertise(BLEUUID parcelUuid)
{
    if (m_queue == NULL)
    {
        log_e("Advertiser queue must be created first!");
        return;
    }

    if (xQueueOverwrite(m_queue, &parcelUuid) != pdPASS)
        log_e("Error sending parcel UUID!");
}

