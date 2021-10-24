#include "ServiceData.h"
#include <Arduino.h>

#pragma pack(push, 1)

typedef struct
{
    int8_t rssi;
    uint8_t gateId;
    int magicNumber;
} ServiceData_t;

#pragma pack(pop)

ServiceData::ServiceData(std::string &serviceData) : m_rssi(0), m_gateId(0), m_magicNumber(0)
{
    ServiceData_t *data = (ServiceData_t*)serviceData.data();

    m_rssi = data->rssi;
    m_gateId = data->gateId;
    m_magicNumber = data->magicNumber;

    Serial.printf("ServiceData::ServiceData -> RSSI: %d, Gate ID: 0x%02x, Magic Number: %d\n", m_rssi, m_gateId, m_magicNumber);
}

int ServiceData::getMagicNumber()
{
    return m_magicNumber;
}