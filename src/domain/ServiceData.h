#ifndef _SERVICE_DATA_H
#define _SERVICE_DATA_H

#include <string>

class ServiceData
{
private:
    int8_t m_rssi;
    uint8_t m_gateId;
    int m_magicNumber;

public:
    ServiceData(std::string &serviceData);
    int getMagicNumber();
};

#endif // _SERVICE_DATA_H