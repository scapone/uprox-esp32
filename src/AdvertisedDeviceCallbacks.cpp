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
        log_i("Advertised Device: %s", advertisedDevice.toString().c_str());
        onDiscover(advertisedDevice);
    }
}

void AdvertisedDeviceCallbacks::onDiscover(BLEAdvertisedDevice advertisedDevice)
{
    ManufacturerData manufacturerData = ManufacturerData::fromString(advertisedDevice.getManufacturerData());
    if (!manufacturerData.isValid())
        return;

    ServiceData serviceData = ServiceData::fromString(advertisedDevice.getServiceData());
    if (!serviceData.isValid())
    {
        return;
    }

    if (manufacturerData.getRssi() != serviceData.getRssi())
        log_w("RSSI from ServiceData %d doesn't match ManufacturerData %d - continue", serviceData.getRssi(), manufacturerData.getRssi());


    if (manufacturerData.getMinor() != 0 && m_acceptCode != 0) {
      if (manufacturerData.getMinor() == m_acceptCode) {
        log_i("Received accept code: %d - ACCEPTED", m_acceptCode);
        //clearInterval(this.timer);
        advertisedDevice.getScan()->stop();
        m_acceptCode = 0;
        return;
      }
      else {
        log_i("Accept code %d doesn't match %d - continue", manufacturerData.getMinor(), m_acceptCode);
      }
    }

    if (advertisedDevice.getRSSI() < -75) {
      log_i("Peripheral RSSI ${peripheral.rssi} less than -75 - skipping");
      return;
    }

    Encrypt::createParcelUuid(serviceData.getMagicNumber());
    
    //log_i("Found our device - Stop scanning!");
    //advertisedDevice.getScan()->stop();
}
