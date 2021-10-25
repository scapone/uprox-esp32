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
    int8_t m_rssi;
    uint8_t m_gateId;
    int m_magicNumber;
};

#endif // _SERVICE_DATA_H