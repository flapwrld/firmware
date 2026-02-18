#include "SettingsApplication.h"
#include "core/ApplicationManager.h"
#include "../graphics/bitmaps.h"

extern ApplicationManager appManager;

SettingsApplication::SettingsApplication() {
    running = false;
    selectedIndex = 0;
    menuState = 0;
    wifiConnected = false;
    wifiScanResults = 0;
    selectedNetwork = 0;
    passwordLength = 0;
    cursorPosition = 0;
    currentChar = 'a';
}

void SettingsApplication::initialize() {
    running = true;
    selectedIndex = 0;
    menuState = 0;
    
    // Check WiFi status
    wifiConnected = WiFi.status() == WL_CONNECTED;
    if (wifiConnected) {
        wifiSSID = WiFi.SSID();
    }
}

void SettingsApplication::update() {
    // Update WiFi status
    wifiConnected = WiFi.status() == WL_CONNECTED;
}

void SettingsApplication::render(Display* display) {
    display->clear();
    
    switch (menuState) {
        case 0:
            drawMainMenu(display);
            break;
        case 1:
            drawWiFiList(display);
            break;
        case 2:
            drawPasswordInput(display);
            break;
        case 3:
            drawAboutScreen(display);
            break;
    }
    
    display->update();
}

void SettingsApplication::drawMainMenu(Display* display) {
    // Status bar
    display->fillRect(0, 0, 128, 11, 1);
    display->setTextColor(0, 1);
    display->setTextSize(1);
    display->drawString(2, 2, "SETTINGS");
    
    // WiFi status indicator
    if (wifiConnected) {
        display->drawBitmap(110, 2, wifiIcon, 8, 8, 0);
    }
    
    display->setTextColor(1, 0);
    display->drawLine(0, 11, 128, 11, 1);
    
    // Menu items
    const char* menuItems[] = {"WiFi", "Display", "About"};
    
    for (int i = 0; i < MENU_COUNT; i++) {
        int yPos = 14 + i * 13;
        bool isSelected = (i == selectedIndex);
        
        if (isSelected) {
            display->fillRoundRect(2, yPos, 124, 11, 3, 1);
        } else {
            display->drawRoundRect(2, yPos, 124, 11, 3, 1);
        }
        
        // Draw icon
        display->setTextColor(isSelected ? 0 : 1, isSelected ? 1 : 0);
        
        if (i == MENU_WIFI) {
            display->drawBitmap(6, yPos + 2, wifiIcon, 8, 8, isSelected ? 0 : 1);
            // Show connection status
            if (wifiConnected) {
                display->drawString(18, yPos + 2, "WiFi: " + wifiSSID);
            } else {
                display->drawString(18, yPos + 2, "WiFi: Not connected");
            }
        } else if (i == MENU_DISPLAY) {
            display->drawBitmap(6, yPos + 2, settingsIcon, 8, 8, isSelected ? 0 : 1);
            display->drawString(18, yPos + 2, menuItems[i]);
        } else if (i == MENU_ABOUT) {
            display->drawBitmap(6, yPos + 2, infoIcon, 8, 8, isSelected ? 0 : 1);
            display->drawString(18, yPos + 2, menuItems[i]);
        }
        
        if (isSelected) {
            display->fillTriangle(118, yPos + 4, 118, yPos + 8, 122, yPos + 6, 0);
        }
    }
    
    display->setTextColor(1, 0);
}

void SettingsApplication::drawWiFiList(Display* display) {
    // Status bar
    display->fillRect(0, 0, 128, 11, 1);
    display->setTextColor(0, 1);
    display->setTextSize(1);
    display->drawString(2, 2, "WiFi Networks");
    display->setTextColor(1, 0);
    display->drawLine(0, 11, 128, 11, 1);
    
    if (wifiScanResults == 0) {
        display->drawCenteredString(30, "Scanning...");
    } else {
        // Show networks
        int visibleNetworks = min(4, wifiScanResults);
        int startIndex = max(0, selectedNetwork - 1);
        startIndex = min(startIndex, max(0, wifiScanResults - visibleNetworks));
        
        for (int i = 0; i < visibleNetworks; i++) {
            int netIndex = startIndex + i;
            int yPos = 14 + i * 12;
            bool isSelected = (netIndex == selectedNetwork);
            
            if (isSelected) {
                display->fillRoundRect(2, yPos, 124, 10, 2, 1);
                display->setTextColor(0, 1);
            } else {
                display->setTextColor(1, 0);
            }
            
            // Draw WiFi icon
            display->drawBitmap(4, yPos + 1, wifiIcon, 8, 8, isSelected ? 0 : 1);
            
            // Draw SSID (truncate if needed)
            String ssid = wifiNetworks[netIndex];
            if (ssid.length() > 14) {
                ssid = ssid.substring(0, 11) + "...";
            }
            display->drawString(14, yPos + 1, ssid);
            
            // Draw signal strength
            int rssi = wifiRSSI[netIndex];
            String signal = String(rssi) + "dB";
            display->drawString(100, yPos + 1, signal);
        }
        
        display->setTextColor(1, 0);
    }
}

void SettingsApplication::drawPasswordInput(Display* display) {
    // Status bar
    display->fillRect(0, 0, 128, 11, 1);
    display->setTextColor(0, 1);
    display->setTextSize(1);
    display->drawString(2, 2, "WiFi Password");
    display->setTextColor(1, 0);
    display->drawLine(0, 11, 128, 11, 1);
    
    // Network name
    display->drawString(2, 14, "SSID:");
    String ssid = wifiNetworks[selectedNetwork];
    if (ssid.length() > 15) {
        ssid = ssid.substring(0, 12) + "...";
    }
    display->drawString(30, 14, ssid);
    
    // Password input
    display->drawString(2, 26, "Pass:");
    display->drawRoundRect(30, 24, 96, 12, 2, 1);
    
    // Show password (masked)
    String maskedPassword = "";
    for (int i = 0; i < passwordLength; i++) {
        maskedPassword += "*";
    }
    display->drawString(32, 26, maskedPassword);
    
    // Character selector
    display->drawString(2, 42, "Char:");
    display->fillRoundRect(30, 40, 12, 12, 2, 1);
    display->setTextColor(0, 1);
    display->drawString(34, 42, String(currentChar));
    display->setTextColor(1, 0);
    
    // Instructions
    display->setTextSize(1);
    display->drawString(2, 56, "UP/DN:char OK:add");
}

void SettingsApplication::drawAboutScreen(Display* display) {
    // Status bar
    display->fillRect(0, 0, 128, 11, 1);
    display->setTextColor(0, 1);
    display->setTextSize(1);
    display->drawString(2, 2, "ABOUT");
    display->setTextColor(1, 0);
    display->drawLine(0, 11, 128, 11, 1);
    
    // Logo
    display->fillRoundRect(44, 14, 40, 16, 4, 1);
    display->fillRoundRect(46, 16, 36, 12, 3, 0);
    display->setTextSize(1);
    display->drawCenteredString(20, "HAKLES");
    
    // Info
    display->setTextSize(1);
    display->drawCenteredString(34, "Security Device");
    display->drawCenteredString(44, "v1.0.0");
    display->drawCenteredString(54, "ESP32 Platform");
}

void SettingsApplication::scanWiFiNetworks() {
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);
    
    wifiScanResults = WiFi.scanNetworks();
    
    for (int i = 0; i < wifiScanResults && i < 20; i++) {
        wifiNetworks[i] = WiFi.SSID(i);
        wifiRSSI[i] = WiFi.RSSI(i);
    }
    
    selectedNetwork = 0;
}

void SettingsApplication::connectToWiFi() {
    WiFi.begin(wifiNetworks[selectedNetwork].c_str(), passwordBuffer);
    
    // Wait for connection (timeout 10 seconds)
    int timeout = 0;
    while (WiFi.status() != WL_CONNECTED && timeout < 20) {
        delay(500);
        timeout++;
    }
    
    wifiConnected = (WiFi.status() == WL_CONNECTED);
    if (wifiConnected) {
        wifiSSID = WiFi.SSID();
    }
}

void SettingsApplication::cleanup() {
    running = false;
}

// Navigation handlers
void SettingsApplication::onUpButton() {
    if (menuState == 0) {
        // Main menu
        selectedIndex--;
        if (selectedIndex < 0) {
            selectedIndex = MENU_COUNT - 1;
        }
    } else if (menuState == 1) {
        // WiFi list
        selectedNetwork--;
        if (selectedNetwork < 0) {
            selectedNetwork = wifiScanResults - 1;
        }
    } else if (menuState == 2) {
        // Password input - change character
        currentChar++;
        if (currentChar > 'z') currentChar = 'a';
        if (currentChar > 'Z' && currentChar < 'a') currentChar = 'a';
    }
}

void SettingsApplication::onDownButton() {
    if (menuState == 0) {
        // Main menu
        selectedIndex++;
        if (selectedIndex >= MENU_COUNT) {
            selectedIndex = 0;
        }
    } else if (menuState == 1) {
        // WiFi list
        selectedNetwork++;
        if (selectedNetwork >= wifiScanResults) {
            selectedNetwork = 0;
        }
    } else if (menuState == 2) {
        // Password input - change character
        currentChar--;
        if (currentChar < 'A') currentChar = 'z';
        if (currentChar > 'Z' && currentChar < 'a') currentChar = 'Z';
    }
}

void SettingsApplication::onLeftButton() {
    if (menuState == 2) {
        // Toggle between lowercase and uppercase
        if (currentChar >= 'a' && currentChar <= 'z') {
            currentChar = currentChar - 'a' + 'A';
        } else if (currentChar >= 'A' && currentChar <= 'Z') {
            currentChar = currentChar - 'A' + 'a';
        }
    }
}

void SettingsApplication::onRightButton() {
    if (menuState == 2) {
        // Toggle between letters and numbers
        if (currentChar >= 'a' && currentChar <= 'z') {
            currentChar = '0';
        } else if (currentChar >= 'A' && currentChar <= 'Z') {
            currentChar = '0';
        } else if (currentChar >= '0' && currentChar <= '9') {
            currentChar = 'a';
        }
    }
}

void SettingsApplication::onOkButton() {
    if (menuState == 0) {
        // Main menu selection
        if (selectedIndex == MENU_WIFI) {
            menuState = 1;
            scanWiFiNetworks();
        } else if (selectedIndex == MENU_ABOUT) {
            menuState = 3;
        }
    } else if (menuState == 1) {
        // WiFi network selected
        menuState = 2;
        passwordLength = 0;
        currentChar = 'a';
        memset(passwordBuffer, 0, sizeof(passwordBuffer));
    } else if (menuState == 2) {
        // Add character to password
        if (passwordLength < 63) {
            passwordBuffer[passwordLength] = currentChar;
            passwordLength++;
            passwordBuffer[passwordLength] = '\0';
        }
    }
}

void SettingsApplication::onBackButton() {
    if (menuState == 0) {
        // Return to main menu
        appManager.switchToApplication(1);
    } else if (menuState == 1) {
        // Return to main menu
        menuState = 0;
    } else if (menuState == 2) {
        // Delete character or return to WiFi list
        if (passwordLength > 0) {
            passwordLength--;
            passwordBuffer[passwordLength] = '\0';
        } else {
            menuState = 1;
        }
    } else if (menuState == 3) {
        // Return to main menu
        menuState = 0;
    }
}

void SettingsApplication::onFunctionButton() {
    if (menuState == 2) {
        // Connect to WiFi
        connectToWiFi();
        menuState = 0;
    }
}

void SettingsApplication::onBackLongPress() {
    // Return to main menu
    appManager.switchToApplication(1);
}

// Metadata methods
const char* SettingsApplication::getName() {
    return "Settings";
}

bool SettingsApplication::isRunning() {
    return running;
}

bool SettingsApplication::isWiFiConnected() {
    return wifiConnected;
}

String SettingsApplication::getWiFiSSID() {
    return wifiSSID;
}
