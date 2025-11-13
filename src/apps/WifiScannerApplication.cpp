#include "WifiScannerApplication.h"
#include "core/ApplicationManager.h"
#include <WiFi.h>
#include <algorithm>

extern ApplicationManager appManager;

WifiScannerApplication::WifiScannerApplication() {
    running = false;
    currentIndex = 0;
    scanning = false;
    networkCount = 0;
    // Initialize network arrays
    for (int i = 0; i < MAX_NETWORKS; i++) {
        networkNames[i][0] = '\0';
        signalStrengths[i] = 0;
    }
}

void WifiScannerApplication::initialize() {
    running = true;
    currentIndex = 0;
    scanning = false;
    networkCount = 0;
    
    // Initialize WiFi in station mode
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();
    delay(100);
    
    // Trigger initial scan
    scanNetworks();
}

void WifiScannerApplication::update() {
    static unsigned long lastScan = 0;
    const unsigned long scanInterval = 10000; // 10 seconds
    
    // Scan for networks periodically
    if (!scanning && millis() - lastScan > scanInterval) {
        scanNetworks();
        lastScan = millis();
    }
}

void WifiScannerApplication::scanNetworks() {
    scanning = true;
    
    // Scan for available networks
    int n = WiFi.scanNetworks();
    
    // Clear previous networks
    networkCount = 0;
    for (int i = 0; i < MAX_NETWORKS; i++) {
        networkNames[i][0] = '\0';
        signalStrengths[i] = 0;
    }
    
    if (n > 0) {
        // Store network information (up to MAX_NETWORKS)
        networkCount = min(n, MAX_NETWORKS);
        for (int i = 0; i < networkCount; i++) {
            // Copy network name
            strncpy(networkNames[i], WiFi.SSID(i).c_str(), 31);
            networkNames[i][31] = '\0';  // Ensure null termination
            
            // Convert RSSI to signal strength (1-4 scale)
            int rssi = WiFi.RSSI(i);
            if (rssi >= -50) {
                signalStrengths[i] = 4;
            } else if (rssi >= -60) {
                signalStrengths[i] = 3;
            } else if (rssi >= -70) {
                signalStrengths[i] = 2;
            } else {
                signalStrengths[i] = 1;
            }
        }
    }
    
    scanning = false;
}

void WifiScannerApplication::render(Display* display) {
    // Clear display
    display->clear();
    
    // Draw title with icon
    display->drawBitmap(0, 0, wifiScannerIcon, WIFI_SCANNER_ICON_WIDTH, WIFI_SCANNER_ICON_HEIGHT, 1);
    display->drawString(20, 5, "WiFi Scanner");
    
    if (scanning) {
        // Show scanning animation
        display->drawString(30, 30, "Scanning...");
        // Draw scanning animation (simple dots)
        static int dotCount = 0;
        dotCount = (dotCount + 1) % 4;
        for (int i = 0; i < dotCount; i++) {
            display->drawString(80 + i * 5, 30, ".");
        }
    } else {
        // Draw WiFi networks list
        int startY = 20;
        int itemHeight = 12;
        
        // Show up to 3 items at a time with scrolling
        int startIndex = max(0, currentIndex - 1);
        int endIndex = min(startIndex + 3, networkCount);
        
        for (int i = startIndex; i < endIndex; i++) {
            int yPos = startY + (i - startIndex) * itemHeight;
            
            // Highlight selected item
            if (i == currentIndex) {
                display->fillRect(0, yPos - 1, 128, itemHeight, 1);
                // Draw text in black (0) on white background
                display->setTextColor(0, 1);
                display->drawString(15, yPos, networkNames[i]);
                display->setTextColor(1, 0); // Reset to normal
                // Draw selection indicator
                display->drawBitmap(5, yPos, wifiIcon, WIFI_ICON_WIDTH, WIFI_ICON_HEIGHT, 0); // Inverted color
            } else {
                display->drawString(15, yPos, networkNames[i]);
                // Draw WiFi icon
                display->drawBitmap(5, yPos, wifiIcon, WIFI_ICON_WIDTH, WIFI_ICON_HEIGHT, 1);
            }
            
            // Draw signal strength indicator
            for (int j = 0; j < signalStrengths[i]; j++) {
                display->fillRect(110 + j * 3, yPos + 5 - j, 2, j + 1, 1);
            }
        }
    }
    
    // Draw navigation hint
    if (scanning) {
        display->drawString(20, 55, "Please wait...");
    } else {
        display->drawString(10, 55, "Up/Down: Navigate");
        display->drawString(10, 65, "OK: Connect  Back: Return");
    }
    
    // Update display
    display->update();
}

void WifiScannerApplication::cleanup() {
    running = false;
}

// Navigation handlers
void WifiScannerApplication::onUpButton() {
    if (!scanning && currentIndex > 0) {
        currentIndex--;
    }
}

void WifiScannerApplication::onDownButton() {
    if (!scanning && networkCount > 0) {
        if (currentIndex < networkCount - 1) {
            currentIndex++;
        }
    }
}

void WifiScannerApplication::onLeftButton() {
    // Do nothing
}

void WifiScannerApplication::onRightButton() {
    // Do nothing
}

void WifiScannerApplication::onOkButton() {
    if (!scanning && networkCount > 0 && currentIndex < networkCount) {
        // In a real implementation, this would trigger actual WiFi connection
        // For now, we'll just print to serial for demonstration
        Serial.print("Connecting to: ");
        Serial.println(networkNames[currentIndex]);
        
        // Simulate connection process
        scanning = true;
        delay(1000); // Simulate connection time
        scanning = false;
        
        Serial.println("Connection simulation complete");
    }
}

void WifiScannerApplication::onBackButton() {
    if (!scanning) {
        // Go back to menu
        appManager.switchToApplication(1);
    }
}

void WifiScannerApplication::onFunctionButton() {
    // Do nothing
}

void WifiScannerApplication::onBackLongPress() {
    // Do nothing
}

// Metadata methods
const char* WifiScannerApplication::getName() {
    return "WiFi Scanner";
}

bool WifiScannerApplication::isRunning() {
    return running;
}