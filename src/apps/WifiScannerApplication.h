#ifndef WIFI_SCANNER_APPLICATION_H
#define WIFI_SCANNER_APPLICATION_H

#include "Application.h"
#include "graphics/bitmaps.h"
#include <WiFi.h>

class WifiScannerApplication : public Application {
private:
    bool running;
    int currentIndex;
    bool scanning;
    static const int MAX_NETWORKS = 10;
    char networkNames[MAX_NETWORKS][32];
    int signalStrengths[MAX_NETWORKS];
    int networkCount;
    
public:
    WifiScannerApplication();
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
        
        // WiFi methods
        void scanNetworks();
    };

#endif // WIFI_SCANNER_APPLICATION_H