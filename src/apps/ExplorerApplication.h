#ifndef EXPLORER_APPLICATION_H
#define EXPLORER_APPLICATION_H

#include "Application.h"
#include "graphics/bitmaps.h"
#include <SD.h>
#include "config.h"

class ExplorerApplication : public Application {
private:
    bool running;
    int currentIndex;
    bool sdInitialized;
    File root;
    
public:
    ExplorerApplication();
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

#endif // EXPLORER_APPLICATION_H