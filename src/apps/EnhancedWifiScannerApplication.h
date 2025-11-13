#ifndef ENHANCED_WIFI_SCANNER_APPLICATION_H
#define ENHANCED_WIFI_SCANNER_APPLICATION_H

#include "Application.h"
#include "graphics/bitmaps.h"
#include <WiFi.h>

class EnhancedWifiScannerApplication : public Application {
private:
    bool running;
    bool scanning;
    int networkCount;
    static const int MAX_NETWORKS = 20;
    struct NetworkInfo {
        char ssid[32];
        uint8_t mac[6];
        int rssi;
        int channel;
        char encryption[16];
        unsigned long lastSeen;
    };
    NetworkInfo networks[MAX_NETWORKS];
    int selectedNetwork;
    unsigned long lastScanTime;
    
public:
    EnhancedWifiScannerApplication();
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
    void refreshNetworkList();
    void displayNetworkDetails(int index);
};

#endif // ENHANCED_WIFI_SCANNER_APPLICATION_H