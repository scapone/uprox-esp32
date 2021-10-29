#ifndef TASK_H_
#define TASK_H_

#include <Arduino.h>

const uint32_t DEFAULT_STACK_SIZE = 2048;

class Task
{
protected:
    TaskHandle_t createTask(const char *pcName, const uint32_t usStackDepth);
    virtual void start() = 0;
    virtual void run() = 0;

private:
    static void run(void *pvParam);
};

#endif // TASK_H_