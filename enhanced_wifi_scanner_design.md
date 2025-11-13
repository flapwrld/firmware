# Enhanced WiFi Scanner Application Design

## Overview
This application will implement an enhanced WiFi scanning functionality with more detailed network information and analysis capabilities compared to the existing WiFi scanner.

## Features
- Detailed network information (SSID, BSSID, channel, security, signal strength)
- Network filtering and sorting options
- Channel hopping for comprehensive scanning
- Network history and statistics
- Export scan results to SD card
- Graphical representation of signal strengths

## Class Definition
```cpp
#ifndef ENHANCED_WIFI_SCANNER_APPLICATION_H
#define ENHANCED_WIFI_SCANNER_APPLICATION_H

#include "Application.h"
#include "graphics/bitmaps.h"
#include <WiFi.h>

class EnhancedWiFiScannerApplication : public Application {
private:
    bool running;
    bool scanning;
    int scanMode; // 0=normal, 1=channel hopping, 2=detailed view
    static const int MAX_NETWORKS = 20;
    
    struct EnhancedNetworkInfo {
        char ssid[32];
        uint8_t bssid[6];
        int channel;
        int rssi;
        int security; // 0=open, 1=WEP, 2=WPA, 3=WPA2
        unsigned long lastSeen;
        int seenCount;
    };
    
    EnhancedNetworkInfo networks[MAX_NETWORKS];
    int networkCount;
    int currentIndex;
    int sortMode; // 0=by signal, 1=by channel, 2=by SSID
    int filterMode; // 0=all, 1=open, 2=secured
    bool showGraph;
    
public:
    EnhancedWiFiScannerApplication();
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
    
    // Scanner methods
    void scanNetworks();
    void sortNetworks();
    void filterNetworks();
    void drawSignalGraph(Display* display, int x, int y, int width, int height);
};

#endif // ENHANCED_WIFI_SCANNER_APPLICATION_H
```

## Implementation Plan
1. Extend WiFi scanning with more detailed information
2. Implement channel hopping for comprehensive scanning
3. Add network filtering and sorting capabilities
4. Create enhanced user interface with detailed network information
5. Implement signal strength graphing
6. Add export functionality for scan results

## Dependencies
- ESP32 WiFi library
- SD card library (for exporting results)
- Display library (already available in the project)

## Hardware Requirements
- ESP32 with WiFi capability
- SD card slot (optional, for exporting results)