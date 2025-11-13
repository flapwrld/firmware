#ifndef WIFI_DEAUTH_ATTACK_APPLICATION_H
#define WIFI_DEAUTH_ATTACK_APPLICATION_H

#include "Application.h"
#include "graphics/bitmaps.h"
#include <WiFi.h>

class WiFiDeauthAttackApplication : public Application {
private:
    bool running;
    bool attacking;
    int targetCount;
    static const int MAX_TARGETS = 10;
    struct TargetInfo {
        char ssid[32];
        uint8_t mac[6];
        int rssi;
        unsigned long lastSeen;
    };
    TargetInfo targets[MAX_TARGETS];
    int selectedTarget;
    bool confirmationNeeded;
    
public:
    WiFiDeauthAttackApplication();
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
    
    // Attack methods
    void scanTargets();
    void startAttack();
    void stopAttack();
    void sendDeauthFrame(uint8_t* targetMac);
};

#endif // WIFI_DEAUTH_ATTACK_APPLICATION_H