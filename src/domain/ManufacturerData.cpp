#include "ManufacturerData.h"
#include <Arduino.h>
#include <BLEUtils.h>
#include <netinet/in.h>

#pragma pack(push, 1)

typedef struct
{
    uint16_t companyId;
    uint8_t type;
    uint8_t length;
    uint8_t uuid[16];
    uint16_t major;
    uint16_t minor;
    int8_t rssi;
} ManufacturerData_t;

#pragma pack(pop)

ManufacturerData::ManufacturerData(std::string manufacturerData)
{
    char* pHex = BLEUtils::buildHexData(nullptr, (uint8_t*)manufacturerData.data(), manufacturerData.length());
    log_d("Manufacturer data: %s", pHex);
	Serial.printf("ManufacturerData::ManufacturerData -> Manufacturer Data: 0x%s\n", pHex);
	free(pHex);

    if (manufacturerData.length() != 25)
    {
    	Serial.printf("ManufacturerData::ManufacturerData -> Invalid manufacturer data length %d instead of 25\n", manufacturerData.length());
        return;
    }

    ManufacturerData_t *data = (ManufacturerData_t*)manufacturerData.data();
    m_companyId = data->companyId;
    m_type = data->type;
    m_length = data->length;
    m_uuid = BLEUUID(data->uuid, sizeof(data->uuid), false);
    m_major = ntohs(data->major);
    m_minor = ntohs(data->minor);
    m_rssi = data->rssi;

    Serial.printf("ManufacturerData::ManufacturerData -> Company ID: 0x%x, Type: 0x%x, Length: %d\n", m_companyId, m_type, m_length);
    Serial.printf("ManufacturerData::ManufacturerData -> UUID: %s, Major: %d, Minor: %d, RSSI: %d\n", m_uuid.toString().c_str(), m_major, m_minor, m_rssi);
}