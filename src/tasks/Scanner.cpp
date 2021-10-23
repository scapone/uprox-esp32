#include "Scanner.h"

#include <Arduino.h>
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

#include "System.h"
#include "crypto/Encrypt.h"
#include "Console.h"
#include "domain/ServiceData.h"

const uint32_t DEFAULT_STACK_SIZE = 2048;

// The remote service we wish to connect to.
static BLEUUID serviceUUID((uint16_t)0x1101);
int scanTime = 5; //In seconds

class PeripheralDeviceCallbacks : public BLEAdvertisedDeviceCallbacks
{
    void onResult(BLEAdvertisedDevice advertisedDevice)
    {
        if (!advertisedDevice.isAdvertisingService(serviceUUID))
        {
            return;
        }

        Serial.printf("Advertised Device: %s \n", advertisedDevice.toString().c_str());
        
        if (!advertisedDevice.haveServiceData())
        {
            return;
        }

        std::string serviceData = advertisedDevice.getServiceData(); 
        if (serviceData.length() != 6)
        {
            return;
        }

        Serial.printf("ServiceData::ServiceData -> ServiceData - Length: %d, Data: ", serviceData.length());
        Console::printByteArray(serviceData);
        Serial.println();

        ServiceData sd(serviceData);
        Encrypt::createParcelUuid(sd.getMagicNumber());

        Serial.println("Found our device - Stop scanning!");
        advertisedDevice.getScan()->stop();
    }
};

void Scanner::start()
{
    createScanner(DEFAULT_STACK_SIZE);
}

void Scanner::run()
{
    BLEDevice::init("");
    BLEScan *pBLEScan = BLEDevice::getScan(); //create new scan
    pBLEScan->setAdvertisedDeviceCallbacks(new PeripheralDeviceCallbacks());
    pBLEScan->setActiveScan(true); //active scan uses more power, but get results faster
    pBLEScan->setInterval(100);
    pBLEScan->setWindow(99); // less or equal setInterval value

    while (true)
    {
        Serial.println("Scanning...");
        setBlinkMode(LED_4HZ);
        // put your main code here, to run repeatedly:
        BLEScanResults foundDevices = pBLEScan->start(scanTime, false);
        Serial.print("Devices found: ");
        Serial.println(foundDevices.getCount());
        Serial.println("Scan done!");
        pBLEScan->clearResults(); // delete results fromBLEScan buffer to release memory
        setBlinkMode(LED_OFF);
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}
