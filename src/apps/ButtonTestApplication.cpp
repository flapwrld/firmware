#include "ButtonTestApplication.h"
#include "core/ApplicationManager.h"
#include "core/Navigation.h"

extern ApplicationManager appManager;
extern Navigation navigation;

ButtonTestApplication::ButtonTestApplication() {
    running = false;
}

void ButtonTestApplication::initialize() {
    running = true;
}

void ButtonTestApplication::update() {
    // Nothing to update
}

void ButtonTestApplication::render(Display* display) {
    // Clear display
    display->clear();
    
    // Draw title
    display->drawString(0, 0, "Button Test");
    display->drawString(0, 10, "Press buttons to test");
    display->drawString(0, 20, "mapping functionality");
    
    // Show which buttons are currently pressed
    if (navigation.isButtonPressed(0)) {
        display->drawString(0, 30, "UP pressed");
    }
    if (navigation.isButtonPressed(1)) {
        display->drawString(0, 40, "DOWN pressed");
    }
    if (navigation.isButtonPressed(2)) {
        display->drawString(0, 50, "LEFT pressed");
    }
    
    // Update display
    display->update();
}

void ButtonTestApplication::cleanup() {
    running = false;
}

// Navigation handlers
void ButtonTestApplication::onUpButton() {
    // Do nothing
}

void ButtonTestApplication::onDownButton() {
    // Do nothing
}

void ButtonTestApplication::onLeftButton() {
    // Do nothing
}

void ButtonTestApplication::onRightButton() {
    // Do nothing
}

void ButtonTestApplication::onOkButton() {
    // Do nothing
}

void ButtonTestApplication::onBackButton() {
    // Go back to menu
    appManager.switchToApplication(1);
}

void ButtonTestApplication::onFunctionButton() {
    // Do nothing
}

void ButtonTestApplication::onBackLongPress() {
    // Do nothing
}

// Metadata methods
const char* ButtonTestApplication::getName() {
    return "Button Test";
}

bool ButtonTestApplication::isRunning() {
    return running;
}