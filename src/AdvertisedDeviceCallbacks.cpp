#include "AdvertisedDeviceCallbacks.h"

#include <Arduino.h>

#include "crypto/Encrypt.h"
#include "Console.h"
#include "domain/ServiceData.h"
#include "domain/ManufacturerData.h"

// The remote service we wish to connect to.
static const BLEUUID serviceUUID((uint16_t)0x1101);

void AdvertisedDeviceCallbacks::onResult(BLEAdvertisedDevice advertisedDevice)
{
    if (advertisedDevice.isAdvertisingService(serviceUUID))
    {
        // Filter to 0x1101 service uuid
        Serial.printf("Advertised Device: %s\n", advertisedDevice.toString().c_str());
        onDiscover(advertisedDevice);
    }
}

void AdvertisedDeviceCallbacks::onDiscover(BLEAdvertisedDevice advertisedDevice)
{
    ManufacturerData manufacturerData = ManufacturerData::fromString(advertisedDevice.getManufacturerData());
    if (!manufacturerData.validate())
        return;

    if (!advertisedDevice.haveServiceData())
    {
        // No service data advertised
        return;
    }

    std::string serviceData = advertisedDevice.getServiceData(); 
    if (serviceData.length() != 6)
    {
        Serial.printf("AdvertisedDeviceCallbacks::onDiscover -> Not recognized ServiceData length: %d\n", serviceData.length());
        return;
    }

    Serial.print("AdvertisedDeviceCallbacks::onDiscover -> ServiceData: ");
    Console::printByteArray(serviceData);
    Serial.println();

    ServiceData sd(serviceData);
    Encrypt::createParcelUuid(sd.getMagicNumber());

    Serial.println("AdvertisedDeviceCallbacks::onDiscover -> Found our device - Stop scanning!");
    advertisedDevice.getScan()->stop();
}
