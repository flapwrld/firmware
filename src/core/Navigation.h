#ifndef NAVIGATION_H
#define NAVIGATION_H

#include <Arduino.h>
#include "Button.h"
#include "config.h"

// Button indices
#define BUTTON_UP_INDEX 0
#define BUTTON_DOWN_INDEX 1
#define BUTTON_LEFT_INDEX 2
#define BUTTON_RIGHT_INDEX 3
#define BUTTON_OK_INDEX 4
#define BUTTON_BACK_INDEX 5
#define BUTTON_FUNCTION_INDEX 6

// Navigation events
enum NavigationEvent {
    NAV_NONE,
    NAV_UP,
    NAV_DOWN,
    NAV_LEFT,
    NAV_RIGHT,
    NAV_OK,
    NAV_BACK,
    NAV_FUNCTION,
    NAV_BACK_LONG,
    NAV_GET_DISPLAY
};

class Navigation {
private:
    Button* buttons;
    NavigationEvent externalEvent;
    
public:
    Navigation(Button* buttonArray);
    void initialize();
    void update();
    NavigationEvent getEvent();
    bool isButtonPressed(int buttonIndex);
    bool isButtonReleased(int buttonIndex);
    bool isButtonLongPressed(int buttonIndex);
    
    // Method to inject external events
    void setExternalEvent(NavigationEvent event);
    NavigationEvent getExternalEvent();
    void clearExternalEvent();
};

#endif // NAVIGATION_H