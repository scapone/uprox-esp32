#ifndef _MANUFACTURER_DATA_H
#define _MANUFACTURER_DATA_H

#include <string>
#include <BLEUUID.h>

class ManufacturerData
{
public:
    ManufacturerData();
    bool isValid();
    int8_t getRssi();
    uint16_t getMinor();
    static ManufacturerData fromString(std::string manufacturerData);

private:
    ManufacturerData(std::string manufacturerData);
    uint16_t m_companyId = 0;
    uint8_t m_type = 0;
    uint8_t m_length = 0;
    BLEUUID m_uuid;
    uint16_t m_major = 0;
    uint16_t m_minor = 0;
    int8_t m_rssi = 0;
};

#endif // _MANUFACTURER_DATA_H