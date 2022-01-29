#ifndef SCANNER_H_
#define SCANNER_H_

#include "Task.h"
#include "tasks/Semaphore.h"

class Scanner : Task
{
public:
    Scanner(Semaphore &semaphore);
    void start();
    void run();

private:
    Semaphore &m_semaphore;
};

#endif // SCANNER_H_