#include "StartupScreen.h"
#include "core/ApplicationManager.h"

extern ApplicationManager appManager;

StartupScreen::StartupScreen() {
    running = false;
}

void StartupScreen::initialize() {
    running = true;
}

void StartupScreen::update() {
    // Nothing to update in startup screen
}

void StartupScreen::render(Display* display) {
    // Clear display
    display->clear();
    
    // Draw startup bitmap (using fileIcon as example, can be changed to a custom logo)
    display->drawBitmap(56, 24, fileIcon, FILE_ICON_WIDTH, FILE_ICON_HEIGHT, 1);
    
    // Draw instruction text
    display->drawString(20, 50, "Press OK to continue");
    
    // Update display
    display->update();
}

void StartupScreen::cleanup() {
    running = false;
}

// Navigation handlers
void StartupScreen::onUpButton() {
    // Do nothing
}

void StartupScreen::onDownButton() {
    // Do nothing
}

void StartupScreen::onLeftButton() {
    // Do nothing
}

void StartupScreen::onRightButton() {
    // Do nothing
}

void StartupScreen::onOkButton() {
    // Switch to the first application in the menu (index 1, assuming index 0 is this startup screen)
    appManager.switchToApplication(1);
}

void StartupScreen::onBackButton() {
    // Do nothing
}

void StartupScreen::onFunctionButton() {
    // Do nothing
}

void StartupScreen::onBackLongPress() {
    // Do nothing
}

// Metadata methods
const char* StartupScreen::getName() {
    return "Startup Screen";
}

bool StartupScreen::isRunning() {
    return running;
}