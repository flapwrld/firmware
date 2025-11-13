#include "BluetoothScannerApplication.h"
#include "core/Display.h"
#include <Arduino.h>

BluetoothScannerApplication::BluetoothScannerApplication() {
    running = false;
    scanning = false;
    deviceCount = 0;
    selectedDevice = 0;
    lastScanTime = 0;
    bleScan = nullptr;
    
    // Initialize devices
    for (int i = 0; i < MAX_DEVICES; i++) {
        memset(devices[i].name, 0, sizeof(devices[i].name));
        memset(devices[i].address, 0, sizeof(devices[i].address));
        memset(devices[i].deviceType, 0, sizeof(devices[i].deviceType));
        devices[i].rssi = 0;
        devices[i].lastSeen = 0;
    }
}

void BluetoothScannerApplication::initialize() {
    running = true;
    Serial.println("Bluetooth Scanner Application initialized");
}

void BluetoothScannerApplication::update() {
    if (!running) return;
    
    // Automatically scan every 15 seconds
    if (millis() - lastScanTime > 15000) {
        scanDevices();
        lastScanTime = millis();
    }
}

void BluetoothScannerApplication::render(Display* display) {
    if (!running) return;
    
    if (deviceCount == 0) {
        display->drawString(0, 0, "Bluetooth Scanner");
        display->drawString(0, 10, "Scanning for devices...");
        display->drawString(0, 20, "Please wait...");
        return;
    }
    
    if (selectedDevice < deviceCount) {
        // Display detailed information for selected device
        display->drawString(0, 0, devices[selectedDevice].name);
        display->drawString(0, 10, "RSSI: " + String(devices[selectedDevice].rssi));
        display->drawString(0, 20, "Type: " + String(devices[selectedDevice].deviceType));
        
        // Display MAC address
        char addrStr[18];
        snprintf(addrStr, sizeof(addrStr), "%02X:%02X:%02X:%02X:%02X:%02X",
                 devices[selectedDevice].address[0], devices[selectedDevice].address[1],
                 devices[selectedDevice].address[2], devices[selectedDevice].address[3],
                 devices[selectedDevice].address[4], devices[selectedDevice].address[5]);
        display->drawString(0, 30, addrStr);
        
        display->drawString(0, 50, "UP/DOWN to navigate");
    } else {
        display->drawString(0, 0, "Bluetooth Scanner");
        display->drawString(0, 10, "Devices: " + String(deviceCount));
        display->drawString(0, 20, "No devices found");
    }
}

void BluetoothScannerApplication::cleanup() {
    running = false;
    scanning = false;
    Serial.println("Bluetooth Scanner Application cleaned up");
}

void BluetoothScannerApplication::onUpButton() {
    if (deviceCount > 0) {
        selectedDevice = (selectedDevice - 1 + deviceCount) % deviceCount;
    }
}

void BluetoothScannerApplication::onDownButton() {
    if (deviceCount > 0) {
        selectedDevice = (selectedDevice + 1) % deviceCount;
    }
}

void BluetoothScannerApplication::onLeftButton() {
    // Not used in this application
}

void BluetoothScannerApplication::onRightButton() {
    // Not used in this application
}

void BluetoothScannerApplication::onOkButton() {
    // Refresh the device list
    scanDevices();
}

void BluetoothScannerApplication::onBackButton() {
    // Exit application
    running = false;
}

void BluetoothScannerApplication::onFunctionButton() {
    // Refresh the device list
    scanDevices();
}

void BluetoothScannerApplication::onBackLongPress() {
    // Exit application
    running = false;
}

const char* BluetoothScannerApplication::getName() {
    return "Bluetooth Scanner";
}

bool BluetoothScannerApplication::isRunning() {
    return running;
}

void BluetoothScannerApplication::scanDevices() {
    scanning = true;
    
    // Simulate finding devices
    deviceCount = random(2, 8);
    
    for (int i = 0; i < deviceCount && i < MAX_DEVICES; i++) {
        // Random device names
        const char* deviceNames[] = {"iPhone", "Android Phone", "Laptop", "Headphones", "Speaker", "Watch", "Fitness Tracker"};
        int nameIndex = random(0, 7);
        strncpy(devices[i].name, deviceNames[nameIndex], sizeof(devices[i].name));
        
        devices[i].rssi = random(-90, -40);
        devices[i].lastSeen = millis();
        
        // Generate random MAC address
        for (int j = 0; j < 6; j++) {
            devices[i].address[j] = random(0, 256);
        }
        
        // Random device type
        const char* deviceTypes[] = {"Phone", "Audio", "Computer", "Wearable", "IoT"};
        int typeIndex = random(0, 5);
        strncpy(devices[i].deviceType, deviceTypes[typeIndex], sizeof(devices[i].deviceType));
    }
    
    scanning = false;
    Serial.println("Scanned for Bluetooth devices");
}

void BluetoothScannerApplication::refreshDeviceList() {
    scanDevices();
}

void BluetoothScannerApplication::displayDeviceDetails(int index) {
    if (index >= 0 && index < deviceCount) {
        selectedDevice = index;
    }
}