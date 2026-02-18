#include <Arduino.h>
#include "config.h"
#include "core/Display.h"
#include "core/Button.h"
#include "core/Navigation.h"
#include "core/ApplicationManager.h"
#include "apps/Application.h"
#include "utils/SerialCommandParser.h"
#include "apps/StartupScreen.h"
#include "apps/MenuApplication.h"
#include "apps/SettingsApplication.h"
#include "graphics/bitmaps.h"
#include <EEPROM.h>

// System components
Display display;
Button buttons[] = {
    Button(BUTTON_UP_PIN),
    Button(BUTTON_DOWN_PIN),
    Button(BUTTON_LEFT_PIN),
    Button(BUTTON_RIGHT_PIN),
    Button(BUTTON_OK_PIN),
    Button(BUTTON_BACK_PIN),
    Button(BUTTON_FUNCTION_PIN)
};
Navigation navigation(buttons);
ApplicationManager appManager;
StartupScreen startupScreen;
MenuApplication menuApplication;
SettingsApplication settingsApplication;

void setup() {
     // Initialize serial communication for debugging
     Serial.begin(115200);
     Serial.println("System starting...");
     
     // Initialize EEPROM with 512 bytes
     EEPROM.begin(512);
     
     // Initialize display
     display.initialize();
    
    // Initialize buttons with default pins
    navigation.initialize();
    
    // Set up the menu application with the application manager
    menuApplication.setApplicationManager(&appManager);
    
    // Register applications
    appManager.registerApplication(&startupScreen);
    appManager.registerApplication(&menuApplication);
    appManager.registerApplication(&settingsApplication);
    
    // Initialize application manager
    appManager.initialize(&display, &navigation);
    
    Serial.println("System initialized");
}

void loop() {
    // Handle button input
    navigation.update();
    
    // Update current application
    appManager.update();
    
    // Render display
    display.clear();
    appManager.render(&display);
    display.update();
    
    // Small delay to prevent excessive CPU usage
    delay(10);
}