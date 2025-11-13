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
    int deviceCount;
    static const int MAX_DEVICES = 15;
    struct DeviceInfo {
        char name[32];
        uint8_t address[6];
        int rssi;
        char deviceType[16];
        unsigned long lastSeen;
    };
    DeviceInfo devices[MAX_DEVICES];
    int selectedDevice;
    unsigned long lastScanTime;
    BLEScan* bleScan;
    
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
    void scanDevices();
    void refreshDeviceList();
    void displayDeviceDetails(int index);
};

#endif // BLUETOOTH_SCANNER_APPLICATION_H