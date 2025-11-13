#include "EvilPortalApplication.h"
#include "core/Display.h"
#include <Arduino.h>

EvilPortalApplication::EvilPortalApplication() {
    running = false;
    portalActive = false;
    sdAvailable = false;
    webServer = nullptr;
    dnsServer = nullptr;
    credentialCount = 0;
    lastActivity = 0;
    captivePortalMode = false;
}

void EvilPortalApplication::initialize() {
    running = true;
    Serial.println("Evil Portal Application initialized");
    
    // Check if SD card is available
    // In a real implementation, this would check for actual SD card presence
    sdAvailable = true;
    
    if (sdAvailable) {
        loadCredentials();
    }
}

void EvilPortalApplication::update() {
    if (!running) return;
    
    // Simulate portal activity
    if (portalActive && millis() - lastActivity > 5000) {
        lastActivity = millis();
        // In a real implementation, this would handle web server requests
    }
}

void EvilPortalApplication::render(Display* display) {
    if (!running) return;
    
    if (!portalActive) {
        display->drawString(0, 0, "Evil Portal");
        display->drawString(0, 10, "Press OK to start");
        display->drawString(0, 20, "portal");
        display->drawString(0, 30, "SD Card: " + String(sdAvailable ? "OK" : "N/A"));
        display->drawString(0, 40, "Credentials: " + String(credentialCount));
    } else {
        display->drawString(0, 0, "PORTAL ACTIVE");
        display->drawString(0, 10, "Waiting for victims...");
        display->drawString(0, 20, "Credentials: " + String(credentialCount));
        display->drawString(0, 30, "Mode: " + String(captivePortalMode ? "Captive" : "Normal"));
        display->drawString(0, 50, "Press BACK to stop");
    }
}

void EvilPortalApplication::cleanup() {
    if (portalActive) {
        stopPortal();
    }
    
    running = false;
    Serial.println("Evil Portal Application cleaned up");
}

void EvilPortalApplication::onUpButton() {
    // Not used in this application
}

void EvilPortalApplication::onDownButton() {
    // Not used in this application
}

void EvilPortalApplication::onLeftButton() {
    if (portalActive) {
        captivePortalMode = !captivePortalMode;
    }
}

void EvilPortalApplication::onRightButton() {
    if (portalActive) {
        captivePortalMode = !captivePortalMode;
    }
}

void EvilPortalApplication::onOkButton() {
    if (!portalActive) {
        startPortal();
    }
}

void EvilPortalApplication::onBackButton() {
    if (portalActive) {
        stopPortal();
    } else {
        // Exit application
        running = false;
    }
}

void EvilPortalApplication::onFunctionButton() {
    if (portalActive) {
        displayCredentials();
    }
}

void EvilPortalApplication::onBackLongPress() {
    // Exit application
    running = false;
}

const char* EvilPortalApplication::getName() {
    return "Evil Portal";
}

bool EvilPortalApplication::isRunning() {
    return running;
}

void EvilPortalApplication::startPortal() {
    portalActive = true;
    lastActivity = millis();
    credentialCount = 0;
    
    // In a real implementation, this would start the web server and DNS server
    Serial.println("Evil Portal started");
}

void EvilPortalApplication::stopPortal() {
    portalActive = false;
    
    // In a real implementation, this would stop the web server and DNS server
    Serial.println("Evil Portal stopped");
}

void EvilPortalApplication::handleRoot() {
    // In a real implementation, this would serve the fake login page
    Serial.println("Serving root page");
}

void EvilPortalApplication::handleLogin() {
    // In a real implementation, this would serve the login page
    Serial.println("Serving login page");
}

void EvilPortalApplication::handleCredentialSubmission() {
    // In a real implementation, this would handle form submissions
    credentialCount++;
    Serial.println("Credential submitted");
    
    if (sdAvailable) {
        saveCredentials("user" + String(credentialCount), "pass" + String(credentialCount));
    }
}

void EvilPortalApplication::saveCredentials(const String& username, const String& password) {
    // In a real implementation, this would save to SD card
    Serial.print("Saving credentials: ");
    Serial.print(username);
    Serial.print(" / ");
    Serial.println(password);
}

void EvilPortalApplication::loadCredentials() {
    // In a real implementation, this would load from SD card
    credentialCount = random(0, 5);
    Serial.println("Loaded credentials from SD card");
}

void EvilPortalApplication::displayCredentials() {
    // In a real implementation, this would display saved credentials
    Serial.println("Displaying saved credentials");
}