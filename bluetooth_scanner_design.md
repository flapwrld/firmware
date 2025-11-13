# Bluetooth Scanner Application Design

## Overview
This application will implement Bluetooth scanning functionality to detect and analyze nearby Bluetooth devices.

## Features
- Bluetooth device discovery
- Display device information (name, MAC address, RSSI)
- Device classification (classic, BLE, unknown)
- Continuous scanning mode
- Device history and statistics
- Export scan results to SD card

## Class Definition
```cpp
#ifndef BLUETOOTH_SCANNER_APPLICATION_H
#define BLUETOOTH_SCANNER_APPLICATION_H

#include "Application.h"
#include "graphics/bitmaps.h"
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

class BluetoothScannerApplication : public Application {
private:
    bool running;
    bool scanning;
    bool continuousScan;
    static const int MAX_DEVICES = 15;
    
    struct BluetoothDevice {
        char name[32];
        uint8_t address[6];
        int rssi;
        int deviceType; // 0=unknown, 1=classic, 2=BLE
        unsigned long lastSeen;
        int seenCount;
    };
    
    BluetoothDevice devices[MAX_DEVICES];
    int deviceCount;
    int currentIndex;
    int sortMode; // 0=by signal, 1=by name, 2=by type
    BLEScan* bleScanner;
    
public:
    BluetoothScannerApplication();
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
    void startScan();
    void stopScan();
    void scanDevices();
    void addDevice(BLEAdvertisedDevice device);
    void sortDevices();
};

#endif // BLUETOOTH_SCANNER_APPLICATION_H
```

## Implementation Plan
1. Initialize Bluetooth scanning capabilities
2. Implement device discovery and classification
3. Create data structures for storing device information
4. Implement continuous and periodic scanning modes
5. Create user interface for displaying scan results
6. Add device filtering and sorting options
7. Implement export functionality for scan results

## Dependencies
- ESP32 Bluetooth library (BLEDevice, BLEUtils, etc.)
- SD card library (for exporting results)
- Display library (already available in the project)

## Hardware Requirements
- ESP32 with Bluetooth capability
- SD card slot (optional, for exporting results)