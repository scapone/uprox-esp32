#include <Arduino.h>

#include "Scanner.h"

Scanner scanner;

void setup() {
  Serial.begin(115200);

  scanner.start();
}

void loop() {
  delay(1000);
}