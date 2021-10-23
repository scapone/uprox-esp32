#include "Console.h"

#include <Arduino.h>

void Console::printByteArray(const std::string data)
{
    if (data.length() == 0)
    {
        Serial.print("NULL");
        return;
    }
    
    Serial.print("0x"); 
    
    for (uint8_t byte : data)
        Serial.printf("%02x", byte);
}