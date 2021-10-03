#include <Arduino.h>
#include "System.h"
#include "controls/Button.h"
#include "tasks/Blink.h"
#include "tasks/Scanner.h"

Button button;
Blink blink;
Scanner scanner;

void setup()
{
    Serial.begin(115200);
    Serial.println();

    button.init();
    blink.start();
    scanner.start();
}

void loop()
{
    switch (button.getState())
    {
    case BTN_RELEASED:
        Serial.println("Button released");
        break;
    case BTN_PRESSED:
        Serial.println("Button pressed");
        break;
    case BTN_CLICK:
        Serial.println("Button clicked");
        break;
    case BTN_LONGCLICK:
        Serial.println("Button longclicked");
        break;
    default:
        break;
    }
}