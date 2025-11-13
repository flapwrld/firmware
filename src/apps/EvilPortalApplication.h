#ifndef EVIL_PORTAL_APPLICATION_H
#define EVIL_PORTAL_APPLICATION_H

#include "Application.h"
#include "graphics/bitmaps.h"
#include <WiFi.h>
#include <WebServer.h>
#include <DNSServer.h>
#include <SD.h>

class EvilPortalApplication : public Application {
private:
    bool running;
    bool portalActive;
    bool sdAvailable;
    WebServer* webServer;
    DNSServer* dnsServer;
    File credentialsFile;
    int credentialCount;
    unsigned long lastActivity;
    bool captivePortalMode;
    
public:
    EvilPortalApplication();
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
    
    // Portal methods
    void startPortal();
    void stopPortal();
    void handleRoot();
    void handleLogin();
    void handleCredentialSubmission();
    void saveCredentials(const String& username, const String& password);
    void loadCredentials();
    void displayCredentials();
};

#endif // EVIL_PORTAL_APPLICATION_H