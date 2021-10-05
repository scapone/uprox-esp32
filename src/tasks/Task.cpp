#include "Task.h"
#include "System.h"

TaskHandle_t Task::m_blink = 0;

void task(void *pvParam)
{
    if (pvParam == NULL)
    {
        System::halt("Invalid task parameter!");
    }

    ((Task *)pvParam)->run();
}

TaskHandle_t Task::createTask(const char* pcName, const uint32_t usStackDepth)
{
    TaskHandle_t handle;
    if (xTaskCreate(task, pcName, usStackDepth, this, 1, &handle) != pdPASS)
        System::halt("Error creating blink task!");

    return handle;
}

void Task::createBlink()
{
    m_blink = createTask("blink", 1024);
}

void Task::createScanner(const uint32_t usStackDepth)
{
    createTask("scanner", usStackDepth);
}

void Task::setBlinkMode(ledmode_t ledmode)
{
    if (m_blink == NULL)
    {
        Serial.println("Blink task must be created first!");
        return;
    }

    if (xTaskNotify(m_blink, ledmode, eSetValueWithOverwrite) != pdPASS)
        Serial.println("Error setting LED mode!");
}
