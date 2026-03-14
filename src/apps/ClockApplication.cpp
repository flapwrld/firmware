#include "ClockApplication.h"

ClockApplication::ClockApplication() : running(false), lastUpdate(0), hours(12), minutes(0), seconds(0), format24h(true) {}

void ClockApplication::initialize() {
    running = true;
    lastUpdate = millis();
}

void ClockApplication::update() {
    unsigned long currentTime = millis();
    if (currentTime - lastUpdate >= 1000) {
        lastUpdate = currentTime;
        seconds++;
        if (seconds >= 60) {
            seconds = 0;
            minutes++;
            if (minutes >= 60) {
                minutes = 0;
                hours++;
                if (hours >= 24) {
                    hours = 0;
                }
            }
        }
    }
}

void ClockApplication::render(Display* display) {
    display->setTextSize(3);
    display->setCursor(10, 20);
    
    if (hours < 10) display->print("0");
    display->print(hours);
    display->print(":");
    if (minutes < 10) display->print("0");
    display->print(minutes);
    
    display->setTextSize(1);
    display->setCursor(100, 30);
    if (seconds < 10) display->print("0");
    display->print(seconds);
}

void ClockApplication::cleanup() {
    running = false;
}

void ClockApplication::onUpButton() { hours = (hours + 1) % 24; }
void ClockApplication::onDownButton() { hours = (hours - 1 + 24) % 24; }
void ClockApplication::onLeftButton() { minutes = (minutes - 1 + 60) % 60; }
void ClockApplication::onRightButton() { minutes = (minutes + 1) % 60; }
void ClockApplication::onOkButton() { format24h = !format24h; }
void ClockApplication::onBackButton() { running = false; }
void ClockApplication::onFunctionButton() { seconds = 0; }
void ClockApplication::onBackLongPress() { running = false; }

const char* ClockApplication::getName() { return "Clock"; }
bool ClockApplication::isRunning() { return running; }
