#include "Scanner.h"

#include <Arduino.h>
#include <BLEDevice.h>

#include "Blink.h"
#include "AdvertisedDeviceCallbacks.h"

const int scanTime = 5; //In seconds

void Scanner::start()
{
    createTask("scanner", DEFAULT_STACK_SIZE);
}

void Scanner::run()
{
    BLEScan *pBLEScan = BLEDevice::getScan(); //create new scan
    pBLEScan->setAdvertisedDeviceCallbacks(new AdvertisedDeviceCallbacks());
    pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster
    pBLEScan->setInterval(100);
    pBLEScan->setWindow(99); // less or equal setInterval value

    while (true)
    {
        Serial.println("Scanning...");
        Blink::setBlinkMode(LED_1HZ);
        // put your main code here, to run repeatedly:
        BLEScanResults foundDevices = pBLEScan->start(scanTime, false);
        Serial.print("Devices found: ");
        Serial.println(foundDevices.getCount());
        Serial.println("Scan done!");
        pBLEScan->clearResults(); // delete results fromBLEScan buffer to release memory
        Blink::setBlinkMode(LED_OFF);
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}
