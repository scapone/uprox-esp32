#include "Console.h"

#include <Arduino.h>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <iterator>

void Console::print(const char c[])
{
    std::cout << c;
}

void Console::println()
{
    std::cout << std::endl;
}

void Console::println(const char c[])
{
    print(c);
    println();
}

void Console::println(int n)
{
    std::cout << n << std::endl;
}

void Console::println(uint64_t n, int base)
{
    if (base == 16)
        std::cout << std::hex << std::showbase << n << std::noshowbase << std::dec;
    else
        std::cout << n;
    std::cout << std::endl;
}

void Console::printByteArray(uint8_t data[], size_t size)
{
    std::reverse(data, data + size);
    std::cout << "0x" << std::hex << std::setw(2) << std::setfill('0');
    //std::copy(data, data + size, std::ostream_iterator<int>(std::cout));
    std::copy_n(data, size, std::ostream_iterator<int>(std::cout));
    std::cout << std::endl;
}

template <typename T, std::size_t N> 
void Console::printByteArray(std::array<T, N>& data)
{
    std::reverse(data.begin(), data.end());
    std::cout << "0x" << std::hex << std::setw(2) << std::setfill('0');
    std::copy(data.begin(), data.end(), std::ostream_iterator<int>(std::cout));
    std::cout << std::endl;
}

void Console::printByteArray(const std::string data)
{
    Serial.print("0x");    
    
    for (uint8_t byte : data)
        Serial.printf("%02x", byte);
}