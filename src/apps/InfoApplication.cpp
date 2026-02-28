#include "InfoApplication.h"
#include <ESP.h>

InfoApplication::InfoApplication() : running(false), page(0) {}

void InfoApplication::initialize() {
    running = true;
    page = 0;
}

void InfoApplication::update() {}

void InfoApplication::render(Display* display) {
    display->setTextSize(1);
    
    if (page == 0) {
        display->setCursor(0, 0);
        display->print("System Info");
        display->setCursor(0, 15);
        display->print("Chip: ESP32");
        display->setCursor(0, 25);
        display->print("Freq: ");
        display->print(ESP.getCpuFreqMHz());
        display->print(" MHz");
        display->setCursor(0, 35);
        display->print("Flash: ");
        display->print(ESP.getFlashChipSize() / 1024 / 1024);
        display->print(" MB");
        display->setCursor(0, 45);
        display->print("Free RAM: ");
        display->print(ESP.getFreeHeap() / 1024);
        display->print(" KB");
    } else if (page == 1) {
        display->setCursor(0, 0);
        display->print("Memory Info");
        display->setCursor(0, 15);
        display->print("Heap: ");
        display->print(ESP.getHeapSize() / 1024);
        display->print(" KB");
        display->setCursor(0, 25);
        display->print("Free: ");
        display->print(ESP.getFreeHeap() / 1024);
        display->print(" KB");
        display->setCursor(0, 35);
        display->print("Usage: ");
        display->print(100 - (ESP.getFreeHeap() * 100 / ESP.getHeapSize()));
        display->print("%");
    }
    
    display->setCursor(0, 57);
    display->print("Page ");
    display->print(page + 1);
    display->print("/2");
}

void InfoApplication::cleanup() {
    running = false;
}

void InfoApplication::onUpButton() {}
void InfoApplication::onDownButton() {}
void InfoApplication::onLeftButton() { if (page > 0) page--; }
void InfoApplication::onRightButton() { if (page < 1) page++; }
void InfoApplication::onOkButton() {}
void InfoApplication::onBackButton() { running = false; }
void InfoApplication::onFunctionButton() {}
void InfoApplication::onBackLongPress() { running = false; }

const char* InfoApplication::getName() { return "System Info"; }
bool InfoApplication::isRunning() { return running; }
