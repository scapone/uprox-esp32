#ifndef BUTTON_H_
#define BUTTON_H_

#include <Arduino.h>

enum buttonstate_t : uint8_t
{
    BTN_UNDEFINED,
    BTN_RELEASED,
    BTN_PRESSED,
    BTN_CLICK,
    BTN_LONGCLICK
};

class Button
{
public:
    Button();
    ~Button() = default;
    void init();
    buttonstate_t getState();

private:
    static Button *s_Button;
    static void IRAM_ATTR handleISR();
    QueueHandle_t m_queue;
    void handle();
};

#endif // BUTTON_H_