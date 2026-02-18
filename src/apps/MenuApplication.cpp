#include "MenuApplication.h"
#include "../graphics/bitmaps.h"
#include "../config.h"

MenuApplication::MenuApplication() : running(false), selectedIndex(0), appManager(nullptr), scrollOffset(0), lastUpdateTime(0) {}

void MenuApplication::initialize() {
    running = true;
    // Start from index 1 to skip StartupScreen (index 0)
    selectedIndex = 1;
    scrollOffset = 0;
    lastUpdateTime = millis();
}

void MenuApplication::update() {
    // Smooth scrolling animation
    lastUpdateTime = millis();
}

void MenuApplication::render(Display* display) {
    display->clear();
    
    // Draw modern status bar
    display->fillRect(0, 0, 128, 11, 1);
    display->setTextColor(0, 1);
    display->setTextSize(1);
    display->drawString(2, 2, "MENU");
    
    // Draw time (placeholder)
    display->setTextColor(0, 1);
    display->setTextSize(1);
    display->drawString(95, 2, "12:34");
    
    // Reset to normal colors
    display->setTextColor(1, 0);
    
    // Draw separator line
    display->drawLine(0, 11, 128, 11, 1);
    
    // Draw menu items with modern card design
    if (appManager != nullptr) {
        int appCount = appManager->getApplicationCount();
        int visibleApps = 4; // Show 4 apps at a time
        int startIndex = max(0, selectedIndex - 1);
        startIndex = min(startIndex, max(0, appCount - visibleApps));
        
        for (int i = 0; i < visibleApps && (startIndex + i) < appCount; i++) {
            int appIndex = startIndex + i;
            Application* app = appManager->getApplication(appIndex);
            int yPos = 14 + i * 13;
            
            // Skip startup screen in menu
            if (strcmp(app->getName(), "Startup Screen") == 0) {
                continue;
            }
            
            bool isSelected = (appIndex == selectedIndex);
            
            // Draw card background
            if (isSelected) {
                display->fillRoundRect(2, yPos, 124, 11, 3, 1);
            } else {
                display->drawRoundRect(2, yPos, 124, 11, 3, 1);
            }
            
            // Draw icon with inverted color for selected
            const char* appName = app->getName();
            int iconX = 6;
            int iconY = yPos + 2;
            
            // Icon mapping
            if (strcmp(appName, "File Explorer") == 0) {
                display->drawBitmap(iconX, iconY - 1, explorerIcon, 8, 8, isSelected ? 0 : 1);
            } else if (strcmp(appName, "Enhanced WiFi Scanner") == 0) {
                display->drawBitmap(iconX, iconY - 1, enhancedWifiScannerIcon, 8, 8, isSelected ? 0 : 1);
            } else if (strcmp(appName, "WiFi Packet Capture") == 0) {
                display->drawBitmap(iconX, iconY - 1, wifiPacketCaptureIcon, 8, 8, isSelected ? 0 : 1);
            } else if (strcmp(appName, "WiFi Deauth Attack") == 0) {
                display->drawBitmap(iconX, iconY - 1, wifiDeauthAttackIcon, 8, 8, isSelected ? 0 : 1);
            } else if (strcmp(appName, "Evil Portal") == 0) {
                display->drawBitmap(iconX, iconY - 1, evilPortalIcon, 8, 8, isSelected ? 0 : 1);
            } else if (strcmp(appName, "Bluetooth Scanner") == 0) {
                display->drawBitmap(iconX, iconY - 1, bluetoothScannerIcon, 8, 8, isSelected ? 0 : 1);
            } else if (strcmp(appName, "Bluetooth Attack") == 0) {
                display->drawBitmap(iconX, iconY - 1, bluetoothAttackIcon, 8, 8, isSelected ? 0 : 1);
            } else if (strcmp(appName, "Settings") == 0) {
                display->drawBitmap(iconX, iconY - 1, settingsIcon, 8, 8, isSelected ? 0 : 1);
            } else if (strcmp(appName, "CC1101 Transceiver") == 0) {
                display->drawBitmap(iconX, iconY - 1, cc1101Icon, 8, 8, isSelected ? 0 : 1);
            } else if (strcmp(appName, "Binary Calculator") == 0) {
                display->drawBitmap(iconX, iconY - 1, binaryCalculatorIcon, 8, 8, isSelected ? 0 : 1);
            } else if (strcmp(appName, "IR TV Off") == 0) {
                display->drawBitmap(iconX, iconY - 1, irIcon, 8, 8, isSelected ? 0 : 1);
            } else if (strcmp(appName, "Stopwatch") == 0) {
                display->drawBitmap(iconX, iconY - 1, stopwatchIcon, 8, 8, isSelected ? 0 : 1);
            } else {
                display->drawBitmap(iconX, iconY - 1, fileIcon, 8, 8, isSelected ? 0 : 1);
            }
            
            // Draw application name with inverted color for selected
            display->setTextSize(1);
            display->setTextColor(isSelected ? 0 : 1, isSelected ? 1 : 0);
            String displayName = String(appName);
            if (displayName.length() > 18) {
                displayName = displayName.substring(0, 15) + "...";
            }
            display->drawString(18, yPos + 2, displayName);
            
            // Draw arrow for selected item
            if (isSelected) {
                display->fillTriangle(118, yPos + 4, 118, yPos + 8, 122, yPos + 6, 0);
            }
            
            // Reset text color
            display->setTextColor(1, 0);
        }
    }
    
    // Draw scroll indicator
    if (appManager != nullptr) {
        int appCount = appManager->getApplicationCount();
        if (appCount > 4) {
            int scrollBarHeight = 40;
            int scrollBarY = 14;
            int scrollPos = (selectedIndex * scrollBarHeight) / appCount;
            display->fillRect(127, scrollBarY + scrollPos, 1, 8, 1);
        }
    }
    
    display->update();
}

void MenuApplication::cleanup() {
    running = false;
}

// Navigation handlers
void MenuApplication::onUpButton() {
    if (appManager != nullptr && appManager->getApplicationCount() > 0) {
        do {
            selectedIndex--;
            if (selectedIndex < 0) {
                selectedIndex = appManager->getApplicationCount() - 1;
            }
            // Skip startup screen
            Application* app = appManager->getApplication(selectedIndex);
            if (strcmp(app->getName(), "Startup Screen") != 0) {
                break;
            }
        } while (true);
    }
}

void MenuApplication::onDownButton() {
    if (appManager != nullptr && appManager->getApplicationCount() > 0) {
        do {
            selectedIndex++;
            if (selectedIndex >= appManager->getApplicationCount()) {
                selectedIndex = 0;
            }
            // Skip startup screen
            Application* app = appManager->getApplication(selectedIndex);
            if (strcmp(app->getName(), "Startup Screen") != 0) {
                break;
            }
        } while (true);
    }
}

void MenuApplication::onLeftButton() {
    // Not used in menu
}

void MenuApplication::onRightButton() {
    // Not used in menu
}

void MenuApplication::onOkButton() {
    if (appManager != nullptr && selectedIndex < appManager->getApplicationCount()) {
        appManager->switchToApplication(selectedIndex);
    }
}

void MenuApplication::onBackButton() {
    // Not used in menu
}

void MenuApplication::onFunctionButton() {
    // Not used in menu
}

void MenuApplication::onBackLongPress() {
    // Not used in menu
}

// Metadata methods
const char* MenuApplication::getName() {
    return "Menu";
}

bool MenuApplication::isRunning() {
    return running;
}

// Set the application manager
void MenuApplication::setApplicationManager(ApplicationManager* manager) {
    appManager = manager;
}
