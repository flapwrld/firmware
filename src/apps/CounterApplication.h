#ifndef COUNTER_APPLICATION_H
#define COUNTER_APPLICATION_H

#include "Application.h"

class CounterApplication : public Application {
private:
    bool running;
    int counter;
    int step;
    
public:
    CounterApplication();
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
