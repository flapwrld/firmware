#include "MenuApplication.h"
#include "../graphics/bitmaps.h"
#include "../config.h"

MenuApplication::MenuApplication() : running(false), selectedIndex(0), appManager(nullptr) {}

void MenuApplication::initialize() {
    running = true;
    selectedIndex = 0;
}

void MenuApplication::update() {
    // Menu navigation is handled by button events
}

void MenuApplication::render(Display* display) {
    display->clear();
    
    // Draw title
    display->drawString(0, 0, "Applications");
    
    // Draw menu items
    if (appManager != nullptr) {
        int appCount = appManager->getApplicationCount();
        int visibleApps = min(appCount, 5); // Show up to 5 apps at a time
        int startIndex = max(0, selectedIndex - 2); // Center the selected item
        startIndex = min(startIndex, appCount - visibleApps);
        
        for (int i = 0; i < visibleApps; i++) {
            int appIndex = startIndex + i;
            if (appIndex < appCount) {
                Application* app = appManager->getApplication(appIndex);
                int yPos = 15 + i * 10;
                
                // Highlight selected item
                if (appIndex == selectedIndex) {
                    display->drawRect(0, yPos - 1, OLED_WIDTH - 1, 9, 1);
                }
                
                // Draw application name
                display->drawString(25, yPos, app->getName());
                
                // Draw icon based on application name
                const char* appName = app->getName();
                if (strcmp(appName, "File Explorer") == 0) {
                    display->drawBitmap(5, yPos, explorerIcon, EXPLORER_ICON_WIDTH, EXPLORER_ICON_HEIGHT, 1);
                } else if (strcmp(appName, "WiFi Scanner") == 0) {
                    display->drawBitmap(5, yPos, wifiScannerIcon, WIFI_SCANNER_ICON_WIDTH, WIFI_SCANNER_ICON_HEIGHT, 1);
                } else if (strcmp(appName, "Tamagotchi") == 0) {
                    display->drawBitmap(5, yPos, tamagotchiIcon, TAMAGOTCHI_ICON_WIDTH, TAMAGOTCHI_ICON_HEIGHT, 1);
                } else if (strcmp(appName, "Stopwatch") == 0) {
                    display->drawBitmap(5, yPos, stopwatchIcon, STOPWATCH_ICON_WIDTH, STOPWATCH_ICON_HEIGHT, 1);
                } else if (strcmp(appName, "Calculator") == 0) {
                    display->drawBitmap(5, yPos, calculatorIcon, CALCULATOR_ICON_WIDTH, CALCULATOR_ICON_HEIGHT, 1);
                } else if (strcmp(appName, "DOOM") == 0) {
                    display->drawBitmap(5, yPos, doomIcon, DOOM_ICON_WIDTH, DOOM_ICON_HEIGHT, 1);
                } else if (strcmp(appName, "Slots") == 0) {
                    display->drawBitmap(5, yPos, slotsIcon, SLOTS_ICON_WIDTH, SLOTS_ICON_HEIGHT, 1);
                } else if (strcmp(appName, "Flappy Bird") == 0) {
                    display->drawBitmap(5, yPos, flappyBirdIcon, FLAPPY_BIRD_ICON_WIDTH, FLAPPY_BIRD_ICON_HEIGHT, 1);
                } else if (strcmp(appName, "Paint") == 0) {
                    display->drawBitmap(5, yPos, paintIcon, PAINT_ICON_WIDTH, PAINT_ICON_HEIGHT, 1);
                } else if (strcmp(appName, "WiFi Packet Capture") == 0) {
                    display->drawBitmap(5, yPos, wifiPacketCaptureIcon, WIFI_PACKET_CAPTURE_ICON_WIDTH, WIFI_PACKET_CAPTURE_ICON_HEIGHT, 1);
                } else if (strcmp(appName, "WiFi Deauth Attack") == 0) {
                    display->drawBitmap(5, yPos, wifiDeauthAttackIcon, WIFI_DEAUTH_ATTACK_ICON_WIDTH, WIFI_DEAUTH_ATTACK_ICON_HEIGHT, 1);
                } else if (strcmp(appName, "Enhanced WiFi Scanner") == 0) {
                    display->drawBitmap(5, yPos, enhancedWifiScannerIcon, ENHANCED_WIFI_SCANNER_ICON_WIDTH, ENHANCED_WIFI_SCANNER_ICON_HEIGHT, 1);
                } else if (strcmp(appName, "Evil Portal") == 0) {
                    display->drawBitmap(5, yPos, evilPortalIcon, EVIL_PORTAL_ICON_WIDTH, EVIL_PORTAL_ICON_HEIGHT, 1);
                } else if (strcmp(appName, "Bluetooth Scanner") == 0) {
                    display->drawBitmap(5, yPos, bluetoothScannerIcon, BLUETOOTH_SCANNER_ICON_WIDTH, BLUETOOTH_SCANNER_ICON_HEIGHT, 1);
                } else if (strcmp(appName, "Bluetooth Attack") == 0) {
                    display->drawBitmap(5, yPos, bluetoothAttackIcon, BLUETOOTH_ATTACK_ICON_WIDTH, BLUETOOTH_ATTACK_ICON_HEIGHT, 1);
                } else if (strcmp(appName, "Settings") == 0) {
                    display->drawBitmap(5, yPos, settingsIcon, SETTINGS_ICON_WIDTH, SETTINGS_ICON_HEIGHT, 1);
                } else if (strcmp(appName, "Button Test") == 0) {
                    display->drawBitmap(5, yPos, buttonTestIcon, BUTTON_TEST_ICON_WIDTH, BUTTON_TEST_ICON_HEIGHT, 1);
                } else if (strcmp(appName, "CC1101 Transceiver") == 0) {
                    display->drawBitmap(5, yPos, cc1101Icon, CC1101_ICON_WIDTH, CC1101_ICON_HEIGHT, 1);
                } else if (strcmp(appName, "Binary Calculator") == 0) {
                    display->drawBitmap(5, yPos, binaryCalculatorIcon, BINARY_CALCULATOR_ICON_WIDTH, BINARY_CALCULATOR_ICON_HEIGHT, 1);
                } else if (strcmp(appName, "IR TV Off") == 0) {
                    display->drawBitmap(5, yPos, irIcon, IR_ICON_WIDTH, IR_ICON_HEIGHT, 1);
                } else {
                    display->drawBitmap(5, yPos, fileIcon, FILE_ICON_WIDTH, FILE_ICON_HEIGHT, 1);
                }
            }
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
        selectedIndex--;
        if (selectedIndex < 0) {
            selectedIndex = appManager->getApplicationCount() - 1;
        }
    }
}

void MenuApplication::onDownButton() {
    if (appManager != nullptr && appManager->getApplicationCount() > 0) {
        selectedIndex++;
        if (selectedIndex >= appManager->getApplicationCount()) {
            selectedIndex = 0;
        }
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