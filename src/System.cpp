#include <Arduino.h>
#include "System.h"

void System::halt(const char *msg)
{
    Serial.println(msg);
    Serial.flush();

    esp_deep_sleep_start();
}