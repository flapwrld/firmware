#include "StartupScreen.h"
#include "core/ApplicationManager.h"

extern ApplicationManager appManager;

StartupScreen::StartupScreen() {
    running = false;
    startTime = 0;
    animationFrame = 0;
}

void StartupScreen::initialize() {
    running = true;
    startTime = millis();
    animationFrame = 0;
}

void StartupScreen::update() {
    // Update animation frame
    unsigned long elapsed = millis() - startTime;
    animationFrame = (elapsed / 50) % 100; // 50ms per frame, loop at 100
}

void StartupScreen::render(Display* display) {
    display->clear();
    
    // Calculate progress (0-100 over 2 seconds)
    unsigned long elapsed = millis() - startTime;
    uint8_t progress = (uint8_t)min((unsigned long)100, (elapsed * 100) / 2000);
    
    // Draw modern logo area with rounded rectangle
    display->fillRoundRect(34, 10, 60, 30, 8, 1);
    display->fillRoundRect(36, 12, 56, 26, 6, 0);
    
    // Draw "HAKLES" text in logo
    display->setTextSize(1);
    display->setTextColor(1, 0);
    display->drawCenteredString(20, "HAKLES");
    
    // Draw subtitle
    display->setTextSize(1);
    display->setTextColor(1, 0);
    display->drawCenteredString(46, "Security Device");
    
    // Draw animated progress bar
    display->drawProgressBar(24, 54, 80, 6, progress);
    
    // Pulsing dot animation
    if (animationFrame % 20 < 10) {
        display->fillCircle(64, 58, 1, 1);
    }
    
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
    // Switch to menu
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