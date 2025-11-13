#ifndef BLUETOOTH_ATTACK_APPLICATION_H
#define BLUETOOTH_ATTACK_APPLICATION_H

#include "Application.h"
#include "graphics/bitmaps.h"
#include <BLEDevice.h>
#include <BLEUtils.h>
#include <BLEScan.h>
#include <BLEAdvertisedDevice.h>

class BluetoothAttackApplication : public Application {
private:
    bool running;
    bool attacking;
    int targetCount;
    static const int MAX_TARGETS = 10;
    struct TargetInfo {
        char name[32];
        uint8_t address[6];
        int rssi;
        char deviceType[16];
        unsigned long lastSeen;
        bool vulnerable;
    };
    TargetInfo targets[MAX_TARGETS];
    int selectedTarget;
    bool confirmationNeeded;
    unsigned long lastScanTime;
    BLEScan* bleScan;
    
public:
    BluetoothAttackApplication();
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
    void refreshTargetList();
    void startAttack();
    void stopAttack();
    void analyzeDevice(int index);
    void displayAttackResults(int index);
};

#endif // BLUETOOTH_ATTACK_APPLICATION_H