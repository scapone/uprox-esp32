#include "Task.h"
#include "System.h"

TaskHandle_t Task::createTask(const char *pcName, const uint32_t usStackDepth)
{
    TaskHandle_t handle;
    if (xTaskCreate(Task::run, pcName, usStackDepth, this, 1, &handle) != pdPASS)
        System::halt("Error creating blink task!");

    return handle;
}

void Task::run(void *pvParam)
{
    if (pvParam == NULL)
    {
        System::halt("Invalid task parameter!");
    }

    ((Task *)pvParam)->run();
}
