#ifndef INFO_APPLICATION_H
#define INFO_APPLICATION_H

#include "Application.h"

class InfoApplication : public Application {
private:
    bool running;
    int page;
    
public:
    InfoApplication();
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
