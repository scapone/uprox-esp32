#include <Arduino.h>
#include "Blink.h"
#include "System.h"

enum ledmode_t : uint8_t { LED_OFF, LED_ON, LED_1HZ, LED_2HZ, LED_4HZ };

const uint32_t LED_PULSE = 25; // 25 ms
const uint8_t LED_PIN = LED_BUILTIN;
const bool LED_LEVEL = HIGH;

void blinkTask(void *pvParam)
{
  ledmode_t ledmode = LED_OFF;
  
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, !LED_LEVEL);

  while (true)
  {
    uint32_t notifyValue;
    TickType_t tickType = ledmode < LED_1HZ ? portMAX_DELAY : 0;

    if (xTaskNotifyWait(0, 0, &notifyValue, tickType) == pdTRUE)
    {
      ledmode = (ledmode_t)notifyValue;

      if (ledmode == LED_OFF)
        digitalWrite(LED_PIN, !LED_LEVEL);
      else if (ledmode == LED_ON)
        digitalWrite(LED_PIN, LED_LEVEL);
    }

    if (ledmode >= LED_1HZ)
    {
      digitalWrite(LED_PIN, LED_LEVEL);
      vTaskDelay(pdMS_TO_TICKS(LED_PULSE));
      digitalWrite(LED_PIN, !LED_LEVEL);
      
      uint32_t period = ledmode == LED_1HZ ? 1000 : ledmode == LED_2HZ ? 500 : 250;
      vTaskDelay(pdMS_TO_TICKS(period - LED_PULSE));
    }
  }
}

void Blink::start()
{
    if (xTaskCreate(blinkTask, "blink", 1024, NULL, 1, NULL) != pdPASS)
        System::halt("Error creating blink task!");
}
