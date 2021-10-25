#include "ServiceData.h"

#include <Arduino.h>
#include <BLEUtils.h>

//#pragma pack(push, 1)

typedef struct
{
    int8_t rssi;
    uint8_t gateId;
    int magicNumber;
} __attribute__((packed)) ServiceData_t;

//#pragma pack(pop)

ServiceData::ServiceData() : m_rssi(0), m_gateId(0), m_magicNumber(0)
{
}

ServiceData::ServiceData(std::string &serviceData) : ServiceData()
{
    ServiceData_t *data = (ServiceData_t*)serviceData.data();

    m_rssi = data->rssi;
    m_gateId = data->gateId;
    m_magicNumber = data->magicNumber;

    log_i("RSSI: %d, Gate ID: 0x%x, Magic Number: %d", m_rssi, m_gateId, m_magicNumber);
}

int ServiceData::getMagicNumber()
{
    return m_magicNumber;
}

int8_t ServiceData::getRssi()
{
    return m_rssi;
}

bool ServiceData::isValid()
{
    if (m_magicNumber == 0)
    {
        log_i("Magic number is 0 - skipping");
        return false;
    }

    return true;
}

ServiceData ServiceData::fromString(std::string serviceData)
{
    char *pHex = BLEUtils::buildHexData(nullptr, (uint8_t *)serviceData.data(), serviceData.length());
    log_i("Service data: 0x%s", pHex);
    free(pHex);

    if (serviceData.length() == 6)
    {
        return ServiceData(serviceData);
    }

    log_i("Not supported ServiceData length: %d instead of 6", serviceData.length());
    return ServiceData();
}
