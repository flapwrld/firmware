#ifndef APPLICATION_H
#define APPLICATION_H

#include <Arduino.h>
#include "core/Display.h"
#include "core/Navigation.h"

class Application {
public:
    virtual ~Application() {}
    
    // Lifecycle methods
    virtual void initialize() = 0;
    virtual void update() = 0;
    virtual void render(Display* display) = 0;
    virtual void cleanup() = 0;
    
    // Navigation handlers
    virtual void onUpButton() = 0;
    virtual void onDownButton() = 0;
    virtual void onLeftButton() = 0;
    virtual void onRightButton() = 0;
    virtual void onOkButton() = 0;
    virtual void onBackButton() = 0;
    virtual void onFunctionButton() = 0;
    virtual void onBackLongPress() = 0;
    
    // Metadata methods
    virtual const char* getName() = 0;
    virtual bool isRunning() = 0;
};

#endif // APPLICATION_H