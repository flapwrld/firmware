#include "Navigation.h"
#include "apps/SettingsApplication.h"

// External settings application instance
extern SettingsApplication settingsApplication;

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
    
    // Get the physical button index for the back button
    int backButtonPhysicalIndex = settingsApplication.getButtonMapping(BUTTON_BACK_INDEX);
    
    // Check for long press on back button first
    if (buttons[backButtonPhysicalIndex].wasLongPressed()) {
        return NAV_BACK_LONG;
    }
    
    // Check for regular button events using mapped indices
    int upButtonPhysicalIndex = settingsApplication.getButtonMapping(BUTTON_UP_INDEX);
    int downButtonPhysicalIndex = settingsApplication.getButtonMapping(BUTTON_DOWN_INDEX);
    int leftButtonPhysicalIndex = settingsApplication.getButtonMapping(BUTTON_LEFT_INDEX);
    int rightButtonPhysicalIndex = settingsApplication.getButtonMapping(BUTTON_RIGHT_INDEX);
    int okButtonPhysicalIndex = settingsApplication.getButtonMapping(BUTTON_OK_INDEX);
    int functionButtonPhysicalIndex = settingsApplication.getButtonMapping(BUTTON_FUNCTION_INDEX);
    
    if (buttons[upButtonPhysicalIndex].wasPressed()) {
        return NAV_UP;
    }
    if (buttons[downButtonPhysicalIndex].wasPressed()) {
        return NAV_DOWN;
    }
    if (buttons[leftButtonPhysicalIndex].wasPressed()) {
        return NAV_LEFT;
    }
    if (buttons[rightButtonPhysicalIndex].wasPressed()) {
        return NAV_RIGHT;
    }
    if (buttons[okButtonPhysicalIndex].wasPressed()) {
        return NAV_OK;
    }
    if (buttons[backButtonPhysicalIndex].wasPressed()) {
        return NAV_BACK;
    }
    if (buttons[functionButtonPhysicalIndex].wasPressed()) {
        return NAV_FUNCTION;
    }
    
    return NAV_NONE;
}

bool Navigation::isButtonPressed(int buttonIndex) {
    if (buttonIndex >= 0 && buttonIndex < 7) {
        int physicalIndex = settingsApplication.getButtonMapping(buttonIndex);
        return buttons[physicalIndex].isPressed();
    }
    return false;
}

bool Navigation::isButtonReleased(int buttonIndex) {
    if (buttonIndex >= 0 && buttonIndex < 7) {
        int physicalIndex = settingsApplication.getButtonMapping(buttonIndex);
        return buttons[physicalIndex].isReleased();
    }
    return false;
}

bool Navigation::isButtonLongPressed(int buttonIndex) {
    if (buttonIndex >= 0 && buttonIndex < 7) {
        int physicalIndex = settingsApplication.getButtonMapping(buttonIndex);
        return buttons[physicalIndex].isLongPressed();
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