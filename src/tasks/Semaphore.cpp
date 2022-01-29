#include "tasks/Semaphore.h"
#include "System.h"

Semaphore::Semaphore()
{
    m_semaphore = xSemaphoreCreateBinary();

    if (m_semaphore == NULL)
    {
        log_e("Error creating semaphore!");
        System::halt();
    }
}

void Semaphore::give()
{
    if (m_semaphore == NULL)
    {
        log_e("Semaphore must be created first!");
        return;
    }

    if (xSemaphoreGive(m_semaphore) != pdTRUE)
    {
        log_e("Error giving semaphore!");
    }
}

bool Semaphore::take()
{
    if (m_semaphore == NULL)
    {
        log_e("Semaphore must be created first!");
        return false;
    }

    return xSemaphoreTake(m_semaphore, portMAX_DELAY) == pdTRUE;
}

bool Semaphore::take(uint32_t timeoutMs)
{
    if (m_semaphore == NULL)
    {
        log_e("Semaphore must be created first!");
        return false;
    }

    return xSemaphoreTake(m_semaphore, pdMS_TO_TICKS(timeoutMs)) == pdTRUE;
}
