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

void Task::createBlink()
{
    TaskHandle_t handle;
    if (xTaskCreate(task, "blink", 1024, this, 1, &handle) != pdPASS)
        System::halt("Error creating blink task!");

    m_blink = handle;
}

void Task::createScanner(const uint32_t usStackDepth)
{
    if (xTaskCreate(task, "scanner", usStackDepth, this, 1, NULL) != pdPASS)
        System::halt("Error creating scan task!");
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
