#ifndef MENU_APPLICATION_H
#define MENU_APPLICATION_H

#include "Application.h"
#include "core/ApplicationManager.h"

class MenuApplication : public Application {
private:
    bool running;
    int selectedIndex;
    ApplicationManager* appManager;
    int scrollOffset;
    unsigned long lastUpdateTime;
    
public:
    MenuApplication();
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
    
    // Set the application manager
    void setApplicationManager(ApplicationManager* manager);
};

#endif // MENU_APPLICATION_H