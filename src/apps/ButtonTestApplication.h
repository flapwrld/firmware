#ifndef BUTTON_TEST_APPLICATION_H
#define BUTTON_TEST_APPLICATION_H

#include "Application.h"
#include "graphics/bitmaps.h"

class ButtonTestApplication : public Application {
private:
    bool running;
    
public:
    ButtonTestApplication();
    void initialize() override;
    void update() override;
    void render(Display* display) override;
    void cleanup() override;
    
    // Navigation handlers
    void onUpButton() override;
    void onDownButton() override;
    void onLeftButton() override;
    void onRightButton() override;
    void onOkButton() override;
    void onBackButton() override;
    void onFunctionButton() override;
    void onBackLongPress() override;
    
    // Metadata methods
    const char* getName() override;
    bool isRunning() override;
};

#endif // BUTTON_TEST_APPLICATION_H