#include "StopwatchApplication.h"
#include "core/ApplicationManager.h"

extern ApplicationManager appManager;

StopwatchApplication::StopwatchApplication() {
    running = false;
    stopwatchRunning = false;
    startTime = 0;
    elapsedTime = 0;
    lastUpdateTime = 0;
}

void StopwatchApplication::initialize() {
    running = true;
    stopwatchRunning = false;
    startTime = 0;
    elapsedTime = 0;
    lastUpdateTime = millis();
}

void StopwatchApplication::update() {
    // Update the display every 100ms for smooth time updates
    if (stopwatchRunning && millis() - lastUpdateTime > 100) {
        lastUpdateTime = millis();
    }
}

void StopwatchApplication::render(Display* display) {
    // Clear display
    display->clear();
    
    // Draw title with icon
    display->drawBitmap(0, 0, stopwatchIcon, STOPWATCH_ICON_WIDTH, STOPWATCH_ICON_HEIGHT, 1);
    display->drawString(20, 5, "Stopwatch");
    
    // Format and display time
    char timeBuffer[16];
    unsigned long totalTime = elapsedTime;
    
    if (stopwatchRunning) {
        totalTime += (millis() - startTime);
    }
    
    // Convert to minutes, seconds, and centiseconds
    int minutes = totalTime / 60000;
    int seconds = (totalTime % 60000) / 1000;
    int centiseconds = (totalTime % 1000) / 10;
    
    sprintf(timeBuffer, "%02d:%02d.%02d", minutes, seconds, centiseconds);
    
    // Display time in large font (centered)
    display->drawString(30, 25, timeBuffer);
    
    // Draw status
    if (stopwatchRunning) {
        display->drawString(45, 40, "RUNNING");
    } else {
        display->drawString(45, 40, "STOPPED");
    }
    
    // Draw controls
    display->drawString(10, 55, "OK:Start/Stop");
    display->drawString(10, 65, "Fn:Reset  Back:Exit");
    
    // Update display
    display->update();
}

void StopwatchApplication::cleanup() {
    running = false;
}

// Navigation handlers
void StopwatchApplication::onUpButton() {
    // Do nothing
}

void StopwatchApplication::onDownButton() {
    // Do nothing
}

void StopwatchApplication::onLeftButton() {
    // Do nothing
}

void StopwatchApplication::onRightButton() {
    // Do nothing
}

void StopwatchApplication::onOkButton() {
    if (stopwatchRunning) {
        stopStopwatch();
    } else {
        startStopwatch();
    }
}

void StopwatchApplication::onBackButton() {
    // Go back to menu
    appManager.switchToApplication(1);
}

void StopwatchApplication::onFunctionButton() {
    resetStopwatch();
}

void StopwatchApplication::onBackLongPress() {
    // Do nothing
}

// Metadata methods
const char* StopwatchApplication::getName() {
    return "Stopwatch";
}

bool StopwatchApplication::isRunning() {
    return running;
}

// Stopwatch methods
void StopwatchApplication::startStopwatch() {
    if (!stopwatchRunning) {
        startTime = millis();
        stopwatchRunning = true;
    }
}

void StopwatchApplication::stopStopwatch() {
    if (stopwatchRunning) {
        elapsedTime += (millis() - startTime);
        stopwatchRunning = false;
    }
}

void StopwatchApplication::resetStopwatch() {
    elapsedTime = 0;
    startTime = 0;
    stopwatchRunning = false;
}