#ifndef BLINK_H_
#define BLINK_H_

#include "tasks/Task.h"

class Blink : Task
{
public:
    Blink() = default;
    ~Blink() = default;
    void start();
    virtual void run();
};

#endif  // BLINK_H_