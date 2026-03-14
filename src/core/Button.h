#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>
#include "config.h"

class Button {
private:
    uint8_t pin;
    bool lastState;
    bool currentState;
    unsigned long lastDebounceTime;
    bool pressed;
    bool released;
    unsigned long pressStartTime;
    bool longPressed;
    
public:
    Button(uint8_t buttonPin);
    void initialize();
    void update();
    bool isPressed();
    bool isReleased();
    bool isLongPressed();
    bool wasPressed();
    bool wasReleased();
    bool wasLongPressed();
    void setPin(uint8_t newPin);  // Add method to change pin
};

#endif // BUTTON_H