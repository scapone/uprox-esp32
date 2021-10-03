#include <Arduino.h>
#include "Button.h"
#include "System.h"

const uint8_t BTN_PIN = 0;
const bool BTN_LEVEL = LOW;

Button *Button::s_Button = NULL;

Button::Button()
{
    s_Button = this;
}

void Button::handleISR()
{
    s_Button->handle();
}

void Button::init()
{
    m_queue = xQueueCreate(32, sizeof(buttonstate_t));
    if (m_queue == NULL)
        System::halt("Error creating queue!");

    pinMode(BTN_PIN, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(BTN_PIN), Button::handleISR, CHANGE);
}

buttonstate_t Button::getState()
{
    buttonstate_t state;
    if (xQueueReceive(m_queue, &state, portMAX_DELAY) == pdTRUE)
        return state;
    return BTN_UNDEFINED;
}

void Button::handle()
{
    const uint32_t CLICK_TIME = 20;      // 20 ms
    const uint32_t LONGCLICK_TIME = 500; // 500 ms

    static uint32_t lastPressed = 0;

    uint32_t time = millis();
    buttonstate_t state;

    bool lastBtn = digitalRead(BTN_PIN) == BTN_LEVEL;
    if (lastBtn)
    {
        state = BTN_PRESSED;
        lastPressed = time;
    }
    else
    {
        if (time - lastPressed >= LONGCLICK_TIME)
            state = BTN_LONGCLICK;
        else if (time - lastPressed >= CLICK_TIME)
            state = BTN_CLICK;
        else
            state = BTN_RELEASED;
        lastPressed = 0;
    }

    xQueueSendFromISR(m_queue, &state, NULL);
}