#ifndef SETTINGS_APPLICATION_H
#define SETTINGS_APPLICATION_H

#include "Application.h"
#include "graphics/bitmaps.h"

class SettingsApplication : public Application {
private:
    bool running;
    int selectedSetting;
    int batteryDisplayMode; // 0 = icon only, 1 = percentage
    bool buttonRebindingMode;
    int rebindingButtonIndex;
    
    // Button mapping (default configuration)
    int buttonMapping[7]; // UP, DOWN, LEFT, RIGHT, OK, BACK, FUNCTION
    
public:
    SettingsApplication();
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
    
    // Settings methods
    void saveSettings();
    void loadSettings();
    int getBatteryDisplayMode();
    void setBatteryDisplayMode(int mode);
    int getButtonMapping(int buttonIndex);
    void setButtonMapping(int buttonIndex, int newMapping);
    void resetToDefaults();
    int getMappedButtonPin(int buttonIndex);
};

// Global settings instance
extern SettingsApplication settingsApp;

#endif // SETTINGS_APPLICATION_H