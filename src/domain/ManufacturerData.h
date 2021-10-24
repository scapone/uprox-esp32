#ifndef _MANUFACTURER_DATA_H
#define _MANUFACTURER_DATA_H

#include <string>
#include <BLEUUID.h>

class ManufacturerData
{
public:
    ManufacturerData();
    static ManufacturerData fromString(std::string manufacturerData);
    bool validate();
private:
    ManufacturerData(std::string manufacturerData);
    uint16_t m_companyId;
    uint8_t m_type;
    uint8_t m_length;
    BLEUUID m_uuid;
    uint16_t m_major;
    uint16_t m_minor;
    int8_t m_rssi;
};

#endif // _MANUFACTURER_DATA_H