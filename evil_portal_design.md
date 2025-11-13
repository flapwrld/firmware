# Evil Portal Application Design

## Overview
This application will implement an Evil Portal functionality for security testing purposes. It will create a fake captive portal to capture user credentials.

## Features
- Create fake WiFi access point
- Serve captive portal web page
- Capture and display submitted credentials
- Multiple portal templates (login pages for popular services)
- Credential logging and export
- Access point configuration options

## Class Definition
```cpp
#ifndef EVIL_PORTAL_APPLICATION_H
#define EVIL_PORTAL_APPLICATION_H

#include "Application.h"
#include "graphics/bitmaps.h"
#include <WiFi.h>
#include <WebServer.h>
#include <DNSServer.h>

class EvilPortalApplication : public Application {
private:
    bool running;
    bool apRunning;
    bool portalActive;
    WebServer* webServer;
    DNSServer* dnsServer;
    
    static const int MAX_CREDENTIALS = 10;
    struct Credential {
        char username[32];
        char password[32];
        char service[20];
        unsigned long timestamp;
    };
    
    Credential credentials[MAX_CREDENTIALS];
    int credentialCount;
    int currentIndex;
    int selectedTemplate; // 0=generic, 1=Facebook, 2=Google, 3=Starbucks
    char apName[32];
    char apPassword[32];
    
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
    void startAccessPoint();
    void stopAccessPoint();
    void startPortal();
    void stopPortal();
    void handleRoot();
    void handleLogin();
    void handleCredential();
    void saveCredentials();
    
    // Web server handlers
    static void handleRootStatic();
    static void handleLoginStatic();
    static void handleCredentialStatic();
};

#endif // EVIL_PORTAL_APPLICATION_H
```

## Implementation Plan
1. Implement WiFi access point creation
2. Set up web server and DNS server for captive portal
3. Create multiple portal templates
4. Implement credential capture and storage
5. Create user interface for configuration and monitoring
6. Add credential export functionality

## Dependencies
- ESP32 WiFi library
- ESP32 WebServer library
- ESP32 DNSServer library
- SD card library (for exporting credentials)
- Display library (already available in the project)

## Hardware Requirements
- ESP32 with WiFi capability
- SD card slot (optional, for exporting credentials)

## Safety Considerations
- Include clear warnings about the purpose and legality of this tool
- Require explicit user confirmation before starting the portal
- Implement safeguards to prevent accidental deployment
- Limit credential storage to prevent privacy issues
- Provide clear instructions on proper and legal usage