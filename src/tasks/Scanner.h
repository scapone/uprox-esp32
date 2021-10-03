#ifndef SCANNER_H_
#define SCANNER_H_

#include "Task.h"

class Scanner : Task
{
public:
    Scanner() = default;
    ~Scanner() = default;
    void start();
    virtual void run();
};

#endif // SCANNER_H_