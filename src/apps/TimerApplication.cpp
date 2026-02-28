#include "TimerApplication.h"

TimerApplication::TimerApplication() : running(false), timerRunning(false), startTime(0), elapsedTime(0), pausedTime(0) {}

void TimerApplication::initialize() {
    running = true;
    timerRunning = false;
    elapsedTime = 0;
    pausedTime = 0;
}

void TimerApplication::update() {
    if (timerRunning) {
        elapsedTime = millis() - startTime + pausedTime;
    }
}

void TimerApplication::render(Display* display) {
    display->setTextSize(2);
    display->setCursor(20, 5);
    display->print("Timer");
    
    unsigned long seconds = elapsedTime / 1000;
    unsigned long minutes = seconds / 60;
    unsigned long hours = minutes / 60;
    
    display->setTextSize(2);
    display->setCursor(10, 25);
    if (hours < 10) display->print("0");
    display->print(hours);
    display->print(":");
    if (minutes % 60 < 10) display->print("0");
    display->print(minutes % 60);
    display->print(":");
    if (seconds % 60 < 10) display->print("0");
    display->print(seconds % 60);
    
    display->setTextSize(1);
    display->setCursor(20, 50);
    display->print(timerRunning ? "Running" : "Stopped");
}

void TimerApplication::cleanup() {
    running = false;
}

void TimerApplication::onUpButton() {}
void TimerApplication::onDownButton() {}
void TimerApplication::onLeftButton() {}
void TimerApplication::onRightButton() {}

void TimerApplication::onOkButton() {
    if (timerRunning) {
        timerRunning = false;
        pausedTime = elapsedTime;
    } else {
        timerRunning = true;
        startTime = millis();
    }
}

void TimerApplication::onBackButton() { running = false; }

void TimerApplication::onFunctionButton() {
    timerRunning = false;
    elapsedTime = 0;
    pausedTime = 0;
}

void TimerApplication::onBackLongPress() { running = false; }

const char* TimerApplication::getName() { return "Timer"; }
bool TimerApplication::isRunning() { return running; }
