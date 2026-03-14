#include "Button.h"

Button::Button(uint8_t buttonPin) {
    pin = buttonPin;
    lastState = BUTTON_RELEASED;
    currentState = BUTTON_RELEASED;
    lastDebounceTime = 0;
    pressed = false;
    released = false;
    longPressed = false;
    pressStartTime = 0;
}

void Button::initialize() {
    pinMode(pin, INPUT_PULLUP);
    lastState = digitalRead(pin);
    currentState = lastState;
}

void Button::update() {
    // Reset event flags
    pressed = false;
    released = false;
    longPressed = false;
    
    // Read the current state of the button
    bool reading = digitalRead(pin);
    
    // Check if the button state has changed
    if (reading != lastState) {
        lastDebounceTime = millis();
    }
    
    // Check if enough time has passed to debounce
    if ((millis() - lastDebounceTime) > BUTTON_DEBOUNCE_TIME) {
        // If the button state has changed
        if (reading != currentState) {
            currentState = reading;
            
            // Check if the button was pressed or released
            if (currentState == BUTTON_PRESSED) {
                pressed = true;
                pressStartTime = millis();
            } else {
                released = true;
                if ((millis() - pressStartTime) > 1000) { // 1 second for long press
                    longPressed = true;
                }
            }
        }
    }
    
    // Check for long press
    if (currentState == BUTTON_PRESSED && (millis() - pressStartTime) > 1000) {
        longPressed = true;
    }
    
    lastState = reading;
}

bool Button::isPressed() {
    return currentState == BUTTON_PRESSED;
}

bool Button::isReleased() {
    return currentState == BUTTON_RELEASED;
}

bool Button::isLongPressed() {
    return longPressed;
}

bool Button::wasPressed() {
    return pressed;
}

bool Button::wasReleased() {
    return released;
}

bool Button::wasLongPressed() {
    return longPressed;
}

void Button::setPin(uint8_t newPin) {
    pin = newPin;
    // Reinitialize the button with the new pin
    initialize();
}