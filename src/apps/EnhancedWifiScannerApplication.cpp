#include "EnhancedWifiScannerApplication.h"
#include "core/Display.h"
#include <Arduino.h>

EnhancedWifiScannerApplication::EnhancedWifiScannerApplication() {
    running = false;
    scanning = false;
    networkCount = 0;
    selectedNetwork = 0;
    lastScanTime = 0;
    
    // Initialize networks
    for (int i = 0; i < MAX_NETWORKS; i++) {
        memset(networks[i].ssid, 0, sizeof(networks[i].ssid));
        memset(networks[i].mac, 0, sizeof(networks[i].mac));
        memset(networks[i].encryption, 0, sizeof(networks[i].encryption));
        networks[i].rssi = 0;
        networks[i].channel = 0;
        networks[i].lastSeen = 0;
    }
}

void EnhancedWifiScannerApplication::initialize() {
    running = true;
    Serial.println("Enhanced WiFi Scanner Application initialized");
}

void EnhancedWifiScannerApplication::update() {
    if (!running) return;
    
    // Automatically scan every 10 seconds
    if (millis() - lastScanTime > 10000) {
        scanNetworks();
        lastScanTime = millis();
    }
}

void EnhancedWifiScannerApplication::render(Display* display) {
    if (!running) return;
    
    if (networkCount == 0) {
        display->drawString(0, 0, "Enhanced WiFi Scanner");
        display->drawString(0, 10, "Scanning for networks...");
        display->drawString(0, 20, "Please wait...");
        return;
    }
    
    if (selectedNetwork < networkCount) {
        // Display detailed information for selected network
        display->drawString(0, 0, networks[selectedNetwork].ssid);
        display->drawString(0, 10, "RSSI: " + String(networks[selectedNetwork].rssi));
        display->drawString(0, 20, "Channel: " + String(networks[selectedNetwork].channel));
        display->drawString(0, 30, "Encryption: " + String(networks[selectedNetwork].encryption));
        
        // Display MAC address
        char macStr[18];
        snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X",
                 networks[selectedNetwork].mac[0], networks[selectedNetwork].mac[1],
                 networks[selectedNetwork].mac[2], networks[selectedNetwork].mac[3],
                 networks[selectedNetwork].mac[4], networks[selectedNetwork].mac[5]);
        display->drawString(0, 40, macStr);
        
        display->drawString(0, 50, "UP/DOWN to navigate");
    } else {
        display->drawString(0, 0, "Enhanced WiFi Scanner");
        display->drawString(0, 10, "Networks: " + String(networkCount));
        display->drawString(0, 20, "No networks found");
    }
}

void EnhancedWifiScannerApplication::cleanup() {
    running = false;
    scanning = false;
    Serial.println("Enhanced WiFi Scanner Application cleaned up");
}

void EnhancedWifiScannerApplication::onUpButton() {
    if (networkCount > 0) {
        selectedNetwork = (selectedNetwork - 1 + networkCount) % networkCount;
    }
}

void EnhancedWifiScannerApplication::onDownButton() {
    if (networkCount > 0) {
        selectedNetwork = (selectedNetwork + 1) % networkCount;
    }
}

void EnhancedWifiScannerApplication::onLeftButton() {
    // Not used in this application
}

void EnhancedWifiScannerApplication::onRightButton() {
    // Not used in this application
}

void EnhancedWifiScannerApplication::onOkButton() {
    // Refresh the network list
    scanNetworks();
}

void EnhancedWifiScannerApplication::onBackButton() {
    // Exit application
    running = false;
}

void EnhancedWifiScannerApplication::onFunctionButton() {
    // Refresh the network list
    scanNetworks();
}

void EnhancedWifiScannerApplication::onBackLongPress() {
    // Exit application
    running = false;
}

const char* EnhancedWifiScannerApplication::getName() {
    return "Enhanced WiFi Scanner";
}

bool EnhancedWifiScannerApplication::isRunning() {
    return running;
}

void EnhancedWifiScannerApplication::scanNetworks() {
    scanning = true;
    
    // Simulate finding networks
    networkCount = random(3, 10);
    
    for (int i = 0; i < networkCount && i < MAX_NETWORKS; i++) {
        snprintf(networks[i].ssid, sizeof(networks[i].ssid), "Network%d", i + 1);
        networks[i].rssi = random(-90, -30);
        networks[i].channel = random(1, 12);
        networks[i].lastSeen = millis();
        
        // Generate random MAC address
        for (int j = 0; j < 6; j++) {
            networks[i].mac[j] = random(0, 256);
        }
        
        // Random encryption type
        int encType = random(0, 3);
        switch (encType) {
            case 0:
                strncpy(networks[i].encryption, "Open", sizeof(networks[i].encryption));
                break;
            case 1:
                strncpy(networks[i].encryption, "WEP", sizeof(networks[i].encryption));
                break;
            case 2:
                strncpy(networks[i].encryption, "WPA", sizeof(networks[i].encryption));
                break;
            default:
                strncpy(networks[i].encryption, "WPA2", sizeof(networks[i].encryption));
                break;
        }
    }
    
    scanning = false;
    Serial.println("Scanned for networks");
}

void EnhancedWifiScannerApplication::refreshNetworkList() {
    scanNetworks();
}

void EnhancedWifiScannerApplication::displayNetworkDetails(int index) {
    if (index >= 0 && index < networkCount) {
        selectedNetwork = index;
    }
}