#include "BluetoothAttackApplication.h"
#include "core/Display.h"
#include <Arduino.h>

BluetoothAttackApplication::BluetoothAttackApplication() {
    running = false;
    attacking = false;
    targetCount = 0;
    selectedTarget = 0;
    confirmationNeeded = false;
    lastScanTime = 0;
    bleScan = nullptr;
    
    // Initialize targets
    for (int i = 0; i < MAX_TARGETS; i++) {
        memset(targets[i].name, 0, sizeof(targets[i].name));
        memset(targets[i].address, 0, sizeof(targets[i].address));
        memset(targets[i].deviceType, 0, sizeof(targets[i].deviceType));
        targets[i].rssi = 0;
        targets[i].lastSeen = 0;
        targets[i].vulnerable = false;
    }
}

void BluetoothAttackApplication::initialize() {
    running = true;
    Serial.println("Bluetooth Attack Application initialized");
}

void BluetoothAttackApplication::update() {
    if (!running) return;
    
    // Automatically scan for targets every 20 seconds
    if (millis() - lastScanTime > 20000) {
        scanTargets();
        lastScanTime = millis();
    }
}

void BluetoothAttackApplication::render(Display* display) {
    if (!running) return;
    
    if (confirmationNeeded) {
        display->drawString(0, 0, "CONFIRM ATTACK");
        display->drawString(0, 10, "Target:");
        if (selectedTarget < targetCount) {
            display->drawString(0, 20, targets[selectedTarget].name);
        }
        display->drawString(0, 30, "OK=Confirm BACK=Cancel");
        return;
    }
    
    if (!attacking) {
        display->drawString(0, 0, "Bluetooth Attack");
        display->drawString(0, 10, "Targets: " + String(targetCount));
        
        if (targetCount > 0 && selectedTarget < targetCount) {
            display->drawString(0, 20, targets[selectedTarget].name);
            display->drawString(0, 30, "RSSI: " + String(targets[selectedTarget].rssi));
            display->drawString(0, 40, "Vuln: " + String(targets[selectedTarget].vulnerable ? "YES" : "NO"));
            display->drawString(0, 50, "OK=Attack UP/DOWN=Select");
        } else {
            display->drawString(0, 20, "Scanning for targets...");
        }
    } else {
        display->drawString(0, 0, "ATTACK IN PROGRESS");
        if (selectedTarget < targetCount) {
            display->drawString(0, 10, targets[selectedTarget].name);
        }
        display->drawString(0, 20, "Analysis:");
        display->drawString(0, 30, "Checking vulnerabilities...");
        display->drawString(0, 40, "Progress: " + String((millis() / 100) % 100) + "%");
        display->drawString(0, 50, "Press BACK to stop");
    }
}

void BluetoothAttackApplication::cleanup() {
    running = false;
    attacking = false;
    confirmationNeeded = false;
    Serial.println("Bluetooth Attack Application cleaned up");
}

void BluetoothAttackApplication::onUpButton() {
    if (confirmationNeeded || attacking) return;
    
    if (targetCount > 0) {
        selectedTarget = (selectedTarget - 1 + targetCount) % targetCount;
    }
}

void BluetoothAttackApplication::onDownButton() {
    if (confirmationNeeded || attacking) return;
    
    if (targetCount > 0) {
        selectedTarget = (selectedTarget + 1) % targetCount;
    }
}

void BluetoothAttackApplication::onLeftButton() {
    // Not used in this application
}

void BluetoothAttackApplication::onRightButton() {
    // Not used in this application
}

void BluetoothAttackApplication::onOkButton() {
    if (confirmationNeeded) {
        confirmationNeeded = false;
        startAttack();
        return;
    }
    
    if (!attacking && targetCount > 0) {
        confirmationNeeded = true;
    }
}

void BluetoothAttackApplication::onBackButton() {
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

void BluetoothAttackApplication::onFunctionButton() {
    if (!attacking && targetCount > 0) {
        analyzeDevice(selectedTarget);
    }
}

void BluetoothAttackApplication::onBackLongPress() {
    // Exit application
    running = false;
}

const char* BluetoothAttackApplication::getName() {
    return "Bluetooth Attack";
}

bool BluetoothAttackApplication::isRunning() {
    return running;
}

void BluetoothAttackApplication::scanTargets() {
    // Simulate finding targets
    targetCount = random(1, 6);
    
    for (int i = 0; i < targetCount; i++) {
        // Random device names
        const char* deviceNames[] = {"iPhone", "Android Phone", "Laptop", "Headphones", "Speaker", "Watch"};
        int nameIndex = random(0, 6);
        strncpy(targets[i].name, deviceNames[nameIndex], sizeof(targets[i].name));
        
        targets[i].rssi = random(-80, -40);
        targets[i].lastSeen = millis();
        targets[i].vulnerable = (random(0, 2) == 1); // 50% chance of being vulnerable
        
        // Generate random MAC address
        for (int j = 0; j < 6; j++) {
            targets[i].address[j] = random(0, 256);
        }
        
        // Random device type
        const char* deviceTypes[] = {"Phone", "Audio", "Computer", "Wearable"};
        int typeIndex = random(0, 4);
        strncpy(targets[i].deviceType, deviceTypes[typeIndex], sizeof(targets[i].deviceType));
    }
    
    Serial.println("Scanned for Bluetooth targets");
}

void BluetoothAttackApplication::refreshTargetList() {
    scanTargets();
}

void BluetoothAttackApplication::startAttack() {
    if (selectedTarget >= targetCount) return;
    
    attacking = true;
    Serial.print("Started attack on ");
    Serial.println(targets[selectedTarget].name);
}

void BluetoothAttackApplication::stopAttack() {
    attacking = false;
    Serial.println("Stopped attack");
}

void BluetoothAttackApplication::analyzeDevice(int index) {
    if (index < 0 || index >= targetCount) return;
    
    // Simulate vulnerability analysis
    targets[index].vulnerable = (random(0, 2) == 1);
    Serial.print("Analyzed device: ");
    Serial.println(targets[index].name);
}

void BluetoothAttackApplication::displayAttackResults(int index) {
    if (index >= 0 && index < targetCount) {
        selectedTarget = index;
    }
}