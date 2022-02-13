#include "Blink.h"
#include <Arduino.h>

const uint32_t LED_PULSE_MS = 25; // 25 ms
const uint8_t LED_PIN = LED_BUILTIN;
const bool LED_LEVEL = HIGH;

TaskHandle_t Blink::m_blink = 0;

void Blink::start()
{
    m_blink = createTask("blink", 1024);
}

void Blink::run()
{
    LedMode_t ledmode = LED_OFF;

    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, !LED_LEVEL);

    while (true)
    {
        TickType_t tickType = (ledmode == LED_OFF || ledmode == LED_ON) ? portMAX_DELAY : 0;

        uint32_t notifyValue;
        if (xTaskNotifyWait(0, 0, &notifyValue, tickType) == pdTRUE)
        {
            ledmode = (LedMode_t)notifyValue;

            if (ledmode == LED_OFF)
                digitalWrite(LED_PIN, !LED_LEVEL);
            else if (ledmode == LED_ON)
                digitalWrite(LED_PIN, LED_LEVEL);
        }

        if (ledmode >= LED_PULSE)
        {
            digitalWrite(LED_PIN, LED_LEVEL);
            vTaskDelay(pdMS_TO_TICKS(LED_PULSE_MS));
            digitalWrite(LED_PIN, !LED_LEVEL);

            if (ledmode == LED_PULSE)
            {
                ledmode = LED_OFF;
                vTaskDelay(pdMS_TO_TICKS(LED_PULSE_MS));
            }
            else
            {
                uint32_t periodMs = ledmode == LED_1HZ ? 1000 : ledmode == LED_2HZ ? 500 : 250;
                vTaskDelay(pdMS_TO_TICKS(periodMs - LED_PULSE_MS));
            }            
        }
    }
}

void Blink::setBlinkMode(LedMode_t ledmode)
{
    if (m_blink == NULL)
    {
        log_e("Blink task must be created first!");
        return;
    }

    if (xTaskNotify(m_blink, ledmode, eSetValueWithOverwrite) != pdPASS)
        log_e("Error setting LED mode!");
}
