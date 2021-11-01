#include "AdvertisedDeviceCallbacks.h"

#include <Arduino.h>

#include "crypto/Encrypt.h"
#include "domain/ServiceData.h"
#include "domain/ManufacturerData.h"
#include "Advertiser.h"
#include "Blink.h"

// The remote service we wish to connect to.
static const BLEUUID SERVICE_UUID((uint16_t)0x1101);
const int8_t TARGET_RSSI = -89;

void AdvertisedDeviceCallbacks::onResult(BLEAdvertisedDevice advertisedDevice)
{
    if (advertisedDevice.isAdvertisingService(SERVICE_UUID))
    {
        // Filter to 0x1101 service uuid
        log_i("Advertised Device: %s", advertisedDevice.toString().c_str());
        onDiscover(advertisedDevice);
    }
}

void AdvertisedDeviceCallbacks::onDiscover(BLEAdvertisedDevice advertisedDevice)
{
    Blink::setBlinkMode(LED_PULSE);

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

    if (manufacturerData.getMinor() != 0 && m_acceptCode != 0)
    {
        if (manufacturerData.getMinor() == m_acceptCode)
        {
            log_i("Received accept code: %d - ACCEPTED", m_acceptCode);
            //clearInterval(this.timer);
            Blink::setBlinkMode(LED_ON);
            advertisedDevice.getScan()->stop();
            m_acceptCode = 0;
            return;
        }
        else
        {
            log_i("Accept code %d doesn't match %d - continue", manufacturerData.getMinor(), m_acceptCode);
        }
    }

    // Must be after accept code check
    int rssi = advertisedDevice.getRSSI();
    if (rssi < TARGET_RSSI)
    {
        log_i("Peripheral RSSI %d < target RSSI %d - skipping", rssi, TARGET_RSSI);
        return;
    }

    log_i("Peripheral RSSI %d >= target RSSI %d - continue", rssi, TARGET_RSSI);

    advertise(serviceData.getMagicNumber());
}

void AdvertisedDeviceCallbacks::advertise(int magicNumber)
{
    if (m_magicNumber == magicNumber)
    {
        log_i("Magic number %d was advertised already - skipping", magicNumber);
        return;
    }

    BLEUUID parcelUuid = Encrypt::createParcelUuid(magicNumber);

    // Calculate accept code
    m_acceptCode = (parcelUuid.getNative()->uuid.uuid128[15] << 8) | 0x04;
    log_i("Expected accept code: %d", m_acceptCode);

    Advertiser::advertise(parcelUuid);
    m_magicNumber = magicNumber;
}

