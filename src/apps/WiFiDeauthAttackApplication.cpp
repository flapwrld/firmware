#include "WiFiDeauthAttackApplication.h"
#include "core/Display.h"
#include <Arduino.h>

WiFiDeauthAttackApplication::WiFiDeauthAttackApplication() {
    running = false;
    attacking = false;
    targetCount = 0;
    selectedTarget = 0;
    confirmationNeeded = false;
    
    // Initialize targets
    for (int i = 0; i < MAX_TARGETS; i++) {
        memset(targets[i].ssid, 0, sizeof(targets[i].ssid));
        memset(targets[i].mac, 0, sizeof(targets[i].mac));
        targets[i].rssi = 0;
        targets[i].lastSeen = 0;
    }
}

void WiFiDeauthAttackApplication::initialize() {
    running = true;
    Serial.println("WiFi Deauth Attack Application initialized");
}

void WiFiDeauthAttackApplication::update() {
    if (!running) return;
    
    // Simulate target scanning
    if (!attacking && millis() % 5000 < 50) {
        scanTargets();
    }
}

void WiFiDeauthAttackApplication::render(Display* display) {
    if (!running) return;
    
    if (confirmationNeeded) {
        display->drawString(0, 0, "CONFIRM ATTACK");
        display->drawString(0, 10, "Target:");
        if (selectedTarget < targetCount) {
            display->drawString(0, 20, targets[selectedTarget].ssid);
        }
        display->drawString(0, 30, "OK=Confirm BACK=Cancel");
        return;
    }
    
    if (!attacking) {
        display->drawString(0, 0, "WiFi Deauth Attack");
        display->drawString(0, 10, "Targets: " + String(targetCount));
        
        if (targetCount > 0 && selectedTarget < targetCount) {
            display->drawString(0, 20, targets[selectedTarget].ssid);
            display->drawString(0, 30, "RSSI: " + String(targets[selectedTarget].rssi));
            display->drawString(0, 40, "Press OK to attack");
            display->drawString(0, 50, "UP/DOWN to select");
        } else {
            display->drawString(0, 20, "Scanning for targets...");
        }
    } else {
        display->drawString(0, 0, "ATTACK IN PROGRESS");
        if (selectedTarget < targetCount) {
            display->drawString(0, 10, targets[selectedTarget].ssid);
        }
        display->drawString(0, 20, "Packets sent:");
        display->drawString(0, 30, String(millis() / 100)); // Simulate packet count
        display->drawString(0, 50, "Press BACK to stop");
    }
}

void WiFiDeauthAttackApplication::cleanup() {
    running = false;
    attacking = false;
    confirmationNeeded = false;
    Serial.println("WiFi Deauth Attack Application cleaned up");
}

void WiFiDeauthAttackApplication::onUpButton() {
    if (confirmationNeeded || attacking) return;
    
    if (targetCount > 0) {
        selectedTarget = (selectedTarget - 1 + targetCount) % targetCount;
    }
}

void WiFiDeauthAttackApplication::onDownButton() {
    if (confirmationNeeded || attacking) return;
    
    if (targetCount > 0) {
        selectedTarget = (selectedTarget + 1) % targetCount;
    }
}

void WiFiDeauthAttackApplication::onLeftButton() {
    // Not used in this application
}

void WiFiDeauthAttackApplication::onRightButton() {
    // Not used in this application
}

void WiFiDeauthAttackApplication::onOkButton() {
    if (confirmationNeeded) {
        confirmationNeeded = false;
        startAttack();
        return;
    }
    
    if (!attacking && targetCount > 0) {
        confirmationNeeded = true;
    }
}

void WiFiDeauthAttackApplication::onBackButton() {
    if (confirmationNeeded) {
        confirmationNeeded = false;
        return;
    }
    
    if (attacking) {
        stopAttack();
    } else {
        // Exit application
        running = false;
    }
}

void WiFiDeauthAttackApplication::onFunctionButton() {
    // Not used in this application
}

void WiFiDeauthAttackApplication::onBackLongPress() {
    // Exit application
    running = false;
}

const char* WiFiDeauthAttackApplication::getName() {
    return "WiFi Deauth Attack";
}

bool WiFiDeauthAttackApplication::isRunning() {
    return running;
}

void WiFiDeauthAttackApplication::scanTargets() {
    // Simulate finding targets
    targetCount = random(1, 6);
    
    for (int i = 0; i < targetCount; i++) {
        snprintf(targets[i].ssid, sizeof(targets[i].ssid), "Network%d", i + 1);
        targets[i].rssi = random(-80, -40);
        targets[i].lastSeen = millis();
        
        // Generate random MAC address
        for (int j = 0; j < 6; j++) {
            targets[i].mac[j] = random(0, 256);
        }
    }
    
    Serial.println("Scanned for targets");
}

void WiFiDeauthAttackApplication::startAttack() {
    if (selectedTarget >= targetCount) return;
    
    attacking = true;
    Serial.print("Started attack on ");
    Serial.println(targets[selectedTarget].ssid);
}

void WiFiDeauthAttackApplication::stopAttack() {
    attacking = false;
    Serial.println("Stopped attack");
}

void WiFiDeauthAttackApplication::sendDeauthFrame(uint8_t* targetMac) {
    // This would send actual deauthentication frames in a real implementation
    Serial.print("Sending deauth frame to MAC: ");
    for (int i = 0; i < 6; i++) {
        if (i > 0) Serial.print(":");
        Serial.print(targetMac[i], HEX);
    }
    Serial.println();
}