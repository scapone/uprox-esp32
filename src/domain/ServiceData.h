#ifndef _SERVICE_DATA_H
#define _SERVICE_DATA_H

#include <string>

class ServiceData
{
public:
    ServiceData();
    int getMagicNumber();
    int8_t getRssi();
    bool isValid();
    static ServiceData fromString(std::string serviceData);

private:
    ServiceData(std::string &serviceData);
    int8_t m_rssi = 0;
    uint8_t m_gateId = 0;
    int m_magicNumber = 0;
};

#endif // _SERVICE_DATA_H