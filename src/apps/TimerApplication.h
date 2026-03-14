#ifndef TIMER_APPLICATION_H
#define TIMER_APPLICATION_H

#include "Application.h"

class TimerApplication : public Application {
private:
    bool running;
    bool timerRunning;
    unsigned long startTime;
    unsigned long elapsedTime;
    unsigned long pausedTime;
    
public:
    TimerApplication();
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
