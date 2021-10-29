#ifndef BLINK_H_
#define BLINK_H_

#include "Task.h"

enum LedMode_t : uint8_t
{
    LED_OFF,
    LED_ON,
    LED_PULSE,
    LED_1HZ,
    LED_2HZ,
    LED_4HZ
};

class Blink : Task
{
public:
    void start();
    virtual void run();
    static void setBlinkMode(LedMode_t ledmode);
private:
    static TaskHandle_t m_blink;
};

#endif // BLINK_H_