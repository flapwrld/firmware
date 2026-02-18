#include "Navigation.h"

Navigation::Navigation(Button* buttonArray) {
    buttons = buttonArray;
    externalEvent = NAV_NONE;
}

void Navigation::initialize() {
    // Initialize all buttons
    for (int i = 0; i < 7; i++) {
        buttons[i].initialize();
    }
}

void Navigation::update() {
    // Update all buttons
    for (int i = 0; i < 7; i++) {
        buttons[i].update();
    }
}

NavigationEvent Navigation::getEvent() {
    // Check for external events first (they have priority)
    if (externalEvent != NAV_NONE) {
        NavigationEvent event = externalEvent;
        clearExternalEvent(); // Clear the external event after retrieving it
        return event;
    }
    
    // Check for long press on back button first (button index 5)
    if (buttons[5].wasLongPressed()) {
        return NAV_BACK_LONG;
    }
    
    // Check for regular button events
    if (buttons[0].wasPressed()) {
        return NAV_UP;
    }
    if (buttons[1].wasPressed()) {
        return NAV_DOWN;
    }
    if (buttons[2].wasPressed()) {
        return NAV_LEFT;
    }
    if (buttons[3].wasPressed()) {
        return NAV_RIGHT;
    }
    if (buttons[4].wasPressed()) {
        return NAV_OK;
    }
    if (buttons[5].wasPressed()) {
        return NAV_BACK;
    }
    if (buttons[6].wasPressed()) {
        return NAV_FUNCTION;
    }
    
    return NAV_NONE;
}

bool Navigation::isButtonPressed(int buttonIndex) {
    if (buttonIndex >= 0 && buttonIndex < 7) {
        return buttons[buttonIndex].isPressed();
    }
    return false;
}

bool Navigation::isButtonReleased(int buttonIndex) {
    if (buttonIndex >= 0 && buttonIndex < 7) {
        return buttons[buttonIndex].isReleased();
    }
    return false;
}

bool Navigation::isButtonLongPressed(int buttonIndex) {
    if (buttonIndex >= 0 && buttonIndex < 7) {
        return buttons[buttonIndex].isLongPressed();
    }
    return false;
}

// Methods to handle external events
void Navigation::setExternalEvent(NavigationEvent event) {
    externalEvent = event;
}

NavigationEvent Navigation::getExternalEvent() {
    return externalEvent;
}

void Navigation::clearExternalEvent() {
    externalEvent = NAV_NONE;
}