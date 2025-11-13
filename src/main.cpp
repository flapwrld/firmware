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
#include "apps/ExplorerApplication.h"
#include "apps/WifiScannerApplication.h"
#include "apps/TamagotchiApplication.h"
#include "apps/StopwatchApplication.h"
#include "apps/CalculatorApplication.h"
#include "apps/DoomApplication.h"
#include "apps/SlotsApplication.h"
#include "apps/FlappyBirdApplication.h"
#include "apps/PaintApplication.h"
#include "apps/WiFiPacketCaptureApplication.h"
#include "apps/WiFiDeauthAttackApplication.h"
#include "apps/EnhancedWifiScannerApplication.h"
#include "apps/EvilPortalApplication.h"
#include "apps/BluetoothScannerApplication.h"
#include "apps/BluetoothAttackApplication.h"
#include "apps/SettingsApplication.h"
#include "apps/ButtonTestApplication.h"
#include "apps/CC1101Application.h"
#include "apps/BinaryCalculatorApplication.h"
#include "apps/IRTVOffApplication.h"
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
ExplorerApplication explorerApplication;
WifiScannerApplication wifiScannerApplication;
TamagotchiApplication tamagotchiApplication;
StopwatchApplication stopwatchApplication;
DoomApplication doomApplication;
CalculatorApplication calculatorApplication;
SlotsApplication slotsApplication(&display, &navigation);
FlappyBirdApplication flappyBirdApplication;
PaintApplication paintApplication;
WiFiPacketCaptureApplication wifiPacketCaptureApplication;
WiFiDeauthAttackApplication wifiDeauthAttackApplication;
EnhancedWifiScannerApplication enhancedWifiScannerApplication;
EvilPortalApplication evilPortalApplication;
BluetoothScannerApplication bluetoothScannerApplication;
BluetoothAttackApplication bluetoothAttackApplication;
SettingsApplication settingsApplication;
ButtonTestApplication buttonTestApplication;
CC1101Application cc1101Application;
BinaryCalculatorApplication binaryCalculatorApplication;
IRTVOffApplication irTVOffApplication;

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
    appManager.registerApplication(&explorerApplication);
    appManager.registerApplication(&wifiScannerApplication);
    appManager.registerApplication(&tamagotchiApplication);
    appManager.registerApplication(&stopwatchApplication);
    appManager.registerApplication(&calculatorApplication);
    appManager.registerApplication(&doomApplication);
    appManager.registerApplication(&slotsApplication);
    appManager.registerApplication(&flappyBirdApplication);
    appManager.registerApplication(&paintApplication);
    appManager.registerApplication(&wifiPacketCaptureApplication);
    appManager.registerApplication(&wifiDeauthAttackApplication);
    appManager.registerApplication(&enhancedWifiScannerApplication);
    appManager.registerApplication(&evilPortalApplication);
    appManager.registerApplication(&bluetoothScannerApplication);
    appManager.registerApplication(&bluetoothAttackApplication);
    appManager.registerApplication(&settingsApplication);
    appManager.registerApplication(&buttonTestApplication);
    appManager.registerApplication(&cc1101Application);
    appManager.registerApplication(&binaryCalculatorApplication);
    appManager.registerApplication(&irTVOffApplication);
    
    // Initialize application manager
    appManager.initialize(&display, &navigation);
    
    // Reinitialize buttons with mapped pins from settings
    // UP button
    buttons[0].setPin(settingsApplication.getMappedButtonPin(0));
    // DOWN button
    buttons[1].setPin(settingsApplication.getMappedButtonPin(1));
    // LEFT button
    buttons[2].setPin(settingsApplication.getMappedButtonPin(2));
    // RIGHT button
    buttons[3].setPin(settingsApplication.getMappedButtonPin(3));
    // OK button
    buttons[4].setPin(settingsApplication.getMappedButtonPin(4));
    // BACK button
    buttons[5].setPin(settingsApplication.getMappedButtonPin(5));
    // FUNCTION button
    buttons[6].setPin(settingsApplication.getMappedButtonPin(6));
    
    // Reinitialize navigation with updated button pins
    navigation.initialize();
    
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