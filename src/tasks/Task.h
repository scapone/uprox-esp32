#ifndef TASK_H_
#define TASK_H_

#include <Arduino.h>

enum ledmode_t : uint8_t
{
    LED_OFF,
    LED_ON,
    LED_1HZ,
    LED_2HZ,
    LED_4HZ
};

class Task
{
private:
    static TaskHandle_t m_blink;

protected:
    Task() = default;
    ~Task() = default;
    TaskHandle_t createTask(const char *pcName, const uint32_t usStackDepth);
    void createBlink();
    void createScanner(const uint32_t usStackDepth);
    void setBlinkMode(ledmode_t ledmode);

public:
    virtual void run() = 0;
};

#endif // TASK_H_