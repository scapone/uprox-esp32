#ifndef _ADVERTISED_DEVICE_CALLBACKS_H
#define _ADVERTISED_DEVICE_CALLBACKS_H

#include <BLEAdvertisedDevice.h>

class AdvertisedDeviceCallbacks : public BLEAdvertisedDeviceCallbacks
{
private:
    uint16_t m_acceptCode = 0;
    void onResult(BLEAdvertisedDevice advertisedDevice);
    void onDiscover(BLEAdvertisedDevice advertisedDevice);
};

#endif // _ADVERTISED_DEVICE_CALLBACKS_H
