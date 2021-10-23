#ifndef _CONSOLE_H
#define _CONSOLE_H

#include <array>

class Console
{
public:
    static void print(const char c[]);
    static void println();
    static void println(const char c[]);
    static void println(int n);
    static void println(uint64_t n, int base);
    static void printByteArray(uint8_t data[], size_t size);
    template <typename T, std::size_t N> 
    static void printByteArray(std::array<T, N>& data);
    static void printByteArray(std::string data);    
};

#endif // _CONSOLE_H