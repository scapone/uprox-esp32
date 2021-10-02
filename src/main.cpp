#include <Arduino.h>
#include "System.h"
#include "Scanner.h"

enum buttonstate_t : uint8_t { BTN_RELEASED, BTN_PRESSED, BTN_CLICK, BTN_LONGCLICK };

QueueHandle_t queue;
Scanner scanner;

void setup() {
  Serial.begin(115200);
  Serial.println();

  scanner.start();
  queue = xQueueCreate(32, sizeof(buttonstate_t));
  if (queue == NULL)
    System::halt("Error creating queue!");
}

void loop() {
  buttonstate_t state;
  if (xQueueReceive(queue, &state, portMAX_DELAY) == pdTRUE)
  {
    Serial.print("Button ");
    switch (state)
    {
    case BTN_RELEASED:
      Serial.println("released");
      break;
    case BTN_PRESSED:
      Serial.println("pressed");
      break;
    case BTN_CLICK:
      Serial.println("clicked");
      break;
    case BTN_LONGCLICK:
      Serial.println("longclicked");
      break;    
    default:
      break;
    }
  }
}