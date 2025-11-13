#include "ApplicationManager.h"

ApplicationManager::ApplicationManager() {
    applicationCount = 0;
    currentApplicationIndex = -1;
    display = nullptr;
    navigation = nullptr;
    
    // Initialize applications array to nullptr
    for (int i = 0; i < MAX_APPLICATIONS; i++) {
        applications[i] = nullptr;
    }
}

void ApplicationManager::initialize(Display* disp, Navigation* nav) {
    display = disp;
    navigation = nav;
    
    // Initialize serial command parser
    serialParser.initialize();
    
    // Initialize all registered applications
    for (int i = 0; i < applicationCount; i++) {
        if (applications[i] != nullptr) {
            applications[i]->initialize();
        }
    }
    
    // Switch to first application if available
    if (applicationCount > 0) {
        switchToApplication(0);
    }
}

void ApplicationManager::update() {
    // Handle serial commands
    NavigationEvent serialEvent = serialParser.parseCommand();
    if (serialEvent != NAV_NONE) {
        // Inject the serial event into the navigation system
        navigation->setExternalEvent(serialEvent);
    }
    
    // Handle navigation events (this will now include both button and serial events)
    NavigationEvent event = navigation->getEvent();
    
    switch (event) {
        case NAV_UP:
            if (currentApplicationIndex >= 0 && applications[currentApplicationIndex] != nullptr) {
                applications[currentApplicationIndex]->onUpButton();
            }
            break;
        case NAV_DOWN:
            if (currentApplicationIndex >= 0 && applications[currentApplicationIndex] != nullptr) {
                applications[currentApplicationIndex]->onDownButton();
            }
            break;
        case NAV_LEFT:
            if (currentApplicationIndex >= 0 && applications[currentApplicationIndex] != nullptr) {
                applications[currentApplicationIndex]->onLeftButton();
            }
            break;
        case NAV_RIGHT:
            if (currentApplicationIndex >= 0 && applications[currentApplicationIndex] != nullptr) {
                applications[currentApplicationIndex]->onRightButton();
            }
            break;
        case NAV_OK:
            if (currentApplicationIndex >= 0 && applications[currentApplicationIndex] != nullptr) {
                applications[currentApplicationIndex]->onOkButton();
            }
            break;
        case NAV_BACK:
            if (currentApplicationIndex >= 0 && applications[currentApplicationIndex] != nullptr) {
                applications[currentApplicationIndex]->onBackButton();
            }
            break;
        case NAV_FUNCTION:
            if (currentApplicationIndex >= 0 && applications[currentApplicationIndex] != nullptr) {
                applications[currentApplicationIndex]->onFunctionButton();
            }
            break;
        case NAV_BACK_LONG:
            if (currentApplicationIndex >= 0 && applications[currentApplicationIndex] != nullptr) {
                applications[currentApplicationIndex]->onBackLongPress();
            }
            break;
        case NAV_GET_DISPLAY:
            // Send display data over serial
            if (display != nullptr) {
                uint8_t buffer[1024];
                display->getDisplayBuffer(buffer, sizeof(buffer));
                
                // Send display data as binary over serial
                Serial.write(buffer, sizeof(buffer));
            }
            break;
        default:
            break;
    }
    
    // Update current application
    if (currentApplicationIndex >= 0 && applications[currentApplicationIndex] != nullptr) {
        applications[currentApplicationIndex]->update();
    }
}

void ApplicationManager::render(Display* display) {
    // Render current application
    if (currentApplicationIndex >= 0 && applications[currentApplicationIndex] != nullptr) {
        applications[currentApplicationIndex]->render(display);
    }
}

void ApplicationManager::registerApplication(Application* app) {
    if (applicationCount < MAX_APPLICATIONS) {
        applications[applicationCount] = app;
        applicationCount++;
    }
}

void ApplicationManager::switchToApplication(int index) {
    if (index >= 0 && index < applicationCount && applications[index] != nullptr) {
        // Cleanup current application if exists
        if (currentApplicationIndex >= 0 && applications[currentApplicationIndex] != nullptr) {
            applications[currentApplicationIndex]->cleanup();
        }
        
        // Switch to new application
        currentApplicationIndex = index;
        
        // Initialize the new application
        applications[currentApplicationIndex]->initialize();
    }
}

int ApplicationManager::getApplicationCount() {
    return applicationCount;
}

Application* ApplicationManager::getCurrentApplication() {
    if (currentApplicationIndex >= 0 && currentApplicationIndex < applicationCount) {
        return applications[currentApplicationIndex];
    }
    return nullptr;
}

Application* ApplicationManager::getApplication(int index) {
    if (index >= 0 && index < applicationCount) {
        return applications[index];
    }
    return nullptr;
}