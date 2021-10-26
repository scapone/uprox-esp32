#ifndef BLINK_H_
#define BLINK_H_

#include "Task.h"

class Blink : Task
{
public:
    void start();
    virtual void run();
    static void setBlinkMode(ledmode_t ledmode);
private:
    static TaskHandle_t m_blink;
};

#endif // BLINK_H_