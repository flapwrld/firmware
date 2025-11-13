#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H

#include <Arduino.h>
#include "apps/Application.h"
#include "core/Display.h"
#include "core/Navigation.h"
#include "utils/SerialCommandParser.h"

#define MAX_APPLICATIONS 25

class ApplicationManager {
private:
    Application* applications[MAX_APPLICATIONS];
    int applicationCount;
    int currentApplicationIndex;
    Display* display;
    Navigation* navigation;
    SerialCommandParser serialParser;
    
public:
    ApplicationManager();
    void initialize(Display* display, Navigation* navigation);
    void update();
    void render(Display* display);
    void registerApplication(Application* app);
    void switchToApplication(int index);
    int getApplicationCount();
    Application* getCurrentApplication();
    Application* getApplication(int index);
};

#endif // APPLICATION_MANAGER_H