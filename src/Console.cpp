#include "Console.h"

#include <Arduino.h>

void Console::printByteArray(const std::string data)
{
    Serial.print("0x");    
    
    for (uint8_t byte : data)
        Serial.printf("%02x", byte);
}