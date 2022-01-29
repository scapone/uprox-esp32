#include "Scanner.h"

#include <Arduino.h>
#include <BLEDevice.h>

#include "Blink.h"
#include "AdvertisedDeviceCallbacks.h"

const int scanTime = 5; //In seconds, 0 - infinite

Scanner::Scanner(Semaphore &semaphore) : m_semaphore(semaphore)
{
}

void Scanner::start()
{
    createTask("scanner", DEFAULT_STACK_SIZE);
}

void Scanner::run()
{
    log_i("Free heap size is %u bytes", esp_get_free_heap_size());
    BLEScan *pBLEScan = BLEDevice::getScan(); //create new scan
    
    AdvertisedDeviceCallbacks callbacks;
    pBLEScan->setAdvertisedDeviceCallbacks(&callbacks, true);
    pBLEScan->setActiveScan(true);
    pBLEScan->setInterval(120); // make sure that scanning window is more than the advertising interval + 10ms to guarantee discovery
    pBLEScan->setWindow(120); // less or equal setInterval value

    while (true)
    {
        m_semaphore.give();

        Serial.println("Scanning...");
        Blink::setBlinkMode(LED_1HZ);
        // put your main code here, to run repeatedly:
        BLEScanResults foundDevices = pBLEScan->start(scanTime, false);
        Serial.println("Scan done!");
        pBLEScan->clearResults(); // delete results fromBLEScan buffer to release memory
        
        m_semaphore.take(2000);
        log_i("Free heap size is %u bytes", esp_get_free_heap_size());
    }
}
