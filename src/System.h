#ifndef SYSTEM_H_
#define SYSTEM_H_

class System
{
public:
    System() = delete;
    ~System() = delete;
    static void halt(const char *msg);
};

#endif  // SYSTEM_H_