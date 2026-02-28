#ifndef CLOCK_APPLICATION_H
#define CLOCK_APPLICATION_H

#include "Application.h"

class ClockApplication : public Application {
private:
    bool running;
    unsigned long lastUpdate;
    int hours;
    int minutes;
    int seconds;
    bool format24h;
    
public:
    ClockApplication();
    void initialize() override;
    void update() override;
    void render(Display* display) override;
    void cleanup() override;
    
    void onUpButton() override;
    void onDownButton() override;
    void onLeftButton() override;
    void onRightButton() override;
    void onOkButton() override;
    void onBackButton() override;
    void onFunctionButton() override;
    void onBackLongPress() override;
    
    const char* getName() override;
    bool isRunning() override;
};

#endif
