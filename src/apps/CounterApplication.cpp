#include "CounterApplication.h"

CounterApplication::CounterApplication() : running(false), counter(0), step(1) {}

void CounterApplication::initialize() {
    running = true;
}

void CounterApplication::update() {}

void CounterApplication::render(Display* display) {
    display->setTextSize(2);
    display->setCursor(10, 10);
    display->print("Counter");
    
    display->setTextSize(3);
    display->setCursor(20, 30);
    display->print(counter);
    
    display->setTextSize(1);
    display->setCursor(10, 55);
    display->print("Step: ");
    display->print(step);
}

void CounterApplication::cleanup() {
    running = false;
}

void CounterApplication::onUpButton() { counter += step; }
void CounterApplication::onDownButton() { counter -= step; }
void CounterApplication::onLeftButton() { if (step > 1) step--; }
void CounterApplication::onRightButton() { step++; }
void CounterApplication::onOkButton() { counter = 0; }
void CounterApplication::onBackButton() { running = false; }
void CounterApplication::onFunctionButton() { step = 1; }
void CounterApplication::onBackLongPress() { running = false; }

const char* CounterApplication::getName() { return "Counter"; }
bool CounterApplication::isRunning() { return running; }
