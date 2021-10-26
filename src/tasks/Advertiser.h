#ifndef ADVERTISER_H_
#define ADVERTISER_H_

#include "Task.h"

class Advertiser : Task
{
public:
    void start();
    virtual void run();
};

#endif // ADVERTISER_H_