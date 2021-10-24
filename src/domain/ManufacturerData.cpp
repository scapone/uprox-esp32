#include "ManufacturerData.h"

#include <Arduino.h>
#include <BLEUtils.h>
#include <netinet/in.h>

static const BLEUUID targetUuid("6dba3e9e-f6e0-4b65-b6a8-1c259e306918");

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

ManufacturerData::ManufacturerData() : m_companyId(0), m_type(0), m_length(0), m_major(0), m_minor(0), m_rssi(0)
{
}

ManufacturerData::ManufacturerData(std::string manufacturerData) : ManufacturerData()
{
    ManufacturerData_t *data = (ManufacturerData_t*)manufacturerData.data();
    m_companyId = data->companyId;
    m_type = data->type;
    m_length = data->length;
    m_uuid = BLEUUID(data->uuid, sizeof(data->uuid), true);
    m_major = ntohs(data->major);
    m_minor = ntohs(data->minor);
    m_rssi = data->rssi;

    log_i("Company ID: 0x%x, Type: 0x%x, Length: %d", m_companyId, m_type, m_length);
    log_i("UUID: %s, Major: %d, Minor: %d, RSSI: %d", m_uuid.toString().c_str(), m_major, m_minor, m_rssi);
}

ManufacturerData ManufacturerData::fromString(std::string manufacturerData)
{
    char* pHex = BLEUtils::buildHexData(nullptr, (uint8_t*)manufacturerData.data(), manufacturerData.length());
    log_i("Manufacturer data: 0x%s", pHex);
	free(pHex);

    if (manufacturerData.length() == 25)
    {
        return ManufacturerData(manufacturerData);
    }

  	log_i("Not supported manufacturer data length: %d instead of 25", manufacturerData.length());
    return ManufacturerData();
}

bool ManufacturerData::validate()
{
    if (m_companyId != 0x4c)
    {
        log_i("Company ID 0x%x doesn't match 0x4c (Apple Inc.) - skipping", m_companyId);
        return false;
    }

    if (m_type != 0x2)
    {
        log_i("Type 0x%x doesn't match 0x2 (Beacon) - skipping", m_type);
        return false;
    }

    if (!m_uuid.equals(targetUuid))
    {
        log_i("UUID '%s' doesn't match target UUID - skipping", m_uuid.toString().c_str());
        return false;
    }

    return true;
}
