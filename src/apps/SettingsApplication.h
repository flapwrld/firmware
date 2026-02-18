#ifndef SETTINGS_APPLICATION_H
#define SETTINGS_APPLICATION_H

#include "Application.h"
#include <WiFi.h>

class SettingsApplication : public Application {
private:
    bool running;
    int selectedIndex;
    int menuState; // 0 = main menu, 1 = wifi list, 2 = wifi password input
    
    // WiFi settings
    String wifiSSID;
    String wifiPassword;
    bool wifiConnected;
    int wifiScanResults;
    String wifiNetworks[20];
    int wifiRSSI[20];
    int selectedNetwork;
    
    // Password input
    char passwordBuffer[64];
    int passwordLength;
    int cursorPosition;
    char currentChar;
    
    // Menu items
    static const int MENU_WIFI = 0;
    static const int MENU_DISPLAY = 1;
    static const int MENU_ABOUT = 2;
    static const int MENU_COUNT = 3;
    
    void scanWiFiNetworks();
    void connectToWiFi();
    void drawMainMenu(Display* display);
    void drawWiFiList(Display* display);
    void drawPasswordInput(Display* display);
    void drawAboutScreen(Display* display);
    
public:
    SettingsApplication();
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
    
    // WiFi status
    bool isWiFiConnected();
    String getWiFiSSID();
};

#endif // SETTINGS_APPLICATION_H
