#include "SettingsApplication.h"
#include "core/ApplicationManager.h"
#include "core/Navigation.h"
#include "config.h"
#include "core/Button.h"
#include <EEPROM.h>

extern ApplicationManager appManager;
extern Navigation navigation;
extern Button buttons[];

SettingsApplication settingsApp;

SettingsApplication::SettingsApplication() {
     running = false;
     selectedSetting = 0;
     batteryDisplayMode = 0; // Default to icon only
     buttonRebindingMode = false;
     rebindingButtonIndex = -1;
     
     // Initialize default button mapping (button indices 0-6)
     for (int i = 0; i < 7; i++) {
         buttonMapping[i] = i; // Default mapping: button index maps to itself
     }
 }

void SettingsApplication::initialize() {
    running = true;
    selectedSetting = 0;
    buttonRebindingMode = false;
    rebindingButtonIndex = -1;
    
    // Load settings from storage (EEPROM/Flash) if available
    loadSettings();
}

void SettingsApplication::update() {
     // Check for button presses during rebinding mode
     if (buttonRebindingMode && rebindingButtonIndex >= 0) {
         // Check which physical button was pressed and map it to the selected function
         for (int i = 0; i < 7; i++) {
             if (buttons[i].wasPressed()) {
                 // Map the pressed button to the selected function
                 buttonMapping[rebindingButtonIndex] = i; // Store the button index
                 
                 // Move to next button to rebind or exit rebinding mode
                 rebindingButtonIndex++;
                 if (rebindingButtonIndex >= 7) {
                     // Finished rebinding all buttons
                     buttonRebindingMode = false;
                     rebindingButtonIndex = -1;
                 }
                 break;
             }
         }
     }
 }

void SettingsApplication::render(Display* display) {
    // Clear display
    display->clear();
    
    // Draw title with icon
    display->drawBitmap(0, 0, settingsIcon, SETTINGS_ICON_WIDTH, SETTINGS_ICON_HEIGHT, 1);
    display->drawString(20, 5, "Settings");
    
    if (buttonRebindingMode) {
        // Show button rebinding interface
        display->drawString(0, 20, "Press button to rebind");
        
        // Show which function is being rebound
        const char* functionNames[] = {"UP", "DOWN", "LEFT", "RIGHT", "OK", "BACK", "FUNCTION"};
        if (rebindingButtonIndex >= 0 && rebindingButtonIndex < 7) {
            display->drawString(0, 30, functionNames[rebindingButtonIndex]);
        }
        
        display->drawString(0, 40, "BACK: Cancel");
    } else {
        // Show settings menu
        display->drawString(0, 20, "Battery Display:");
        if (batteryDisplayMode == 0) {
            display->drawString(0, 30, "Icon Only");
        } else {
            display->drawString(0, 30, "Percentage");
        }
        
        display->drawString(0, 40, "Button Rebinding");
        display->drawString(0, 50, "Reset to Defaults");
        
        // Highlight selected setting
        switch (selectedSetting) {
            case 0:
                display->drawRect(0, 28, 128, 10, 1);
                break;
            case 1:
                display->drawRect(0, 38, 128, 10, 1);
                break;
            case 2:
                display->drawRect(0, 48, 128, 10, 1);
                break;
        }
    }
    
    // Update display
    display->update();
}

void SettingsApplication::cleanup() {
    running = false;
    
    // Save settings to storage (EEPROM/Flash) if available
    saveSettings();
}

// Navigation handlers
void SettingsApplication::onUpButton() {
    if (buttonRebindingMode) {
        // In rebinding mode, UP doesn't do anything special
        return;
    }
    
    if (selectedSetting > 0) {
        selectedSetting--;
    }
}

void SettingsApplication::onDownButton() {
    if (buttonRebindingMode) {
        // In rebinding mode, DOWN doesn't do anything special
        return;
    }
    
    if (selectedSetting < 2) {
        selectedSetting++;
    }
}

void SettingsApplication::onLeftButton() {
    if (buttonRebindingMode) {
        // In rebinding mode, LEFT doesn't do anything special
        return;
    }
    
    if (selectedSetting == 0 && batteryDisplayMode > 0) {
        batteryDisplayMode--;
    }
}

void SettingsApplication::onRightButton() {
    if (buttonRebindingMode) {
        // In rebinding mode, RIGHT doesn't do anything special
        return;
    }
    
    if (selectedSetting == 0 && batteryDisplayMode < 1) {
        batteryDisplayMode++;
    }
}

void SettingsApplication::onOkButton() {
    if (buttonRebindingMode) {
        // Exit rebinding mode
        buttonRebindingMode = false;
        rebindingButtonIndex = -1;
        return;
    }
    
    switch (selectedSetting) {
        case 0:
            // Toggle battery display mode
            batteryDisplayMode = (batteryDisplayMode + 1) % 2;
            break;
        case 1:
            // Enter button rebinding mode
            buttonRebindingMode = true;
            rebindingButtonIndex = 0; // Start with UP button
            break;
        case 2:
            // Reset to defaults
            resetToDefaults();
            break;
    }
}

void SettingsApplication::onBackButton() {
    if (buttonRebindingMode) {
        // Cancel rebinding mode
        buttonRebindingMode = false;
        rebindingButtonIndex = -1;
        return;
    }
    
    // Go back to menu
    appManager.switchToApplication(1);
}

void SettingsApplication::onFunctionButton() {
    // Do nothing
}

void SettingsApplication::onBackLongPress() {
    // Do nothing
}

// Metadata methods
const char* SettingsApplication::getName() {
    return "Settings";
}

bool SettingsApplication::isRunning() {
    return running;
}

// Settings methods
void SettingsApplication::saveSettings() {
    // Define EEPROM address offsets
    const int BATTERY_MODE_ADDR = 0;
    const int BUTTON_MAPPING_START_ADDR = 1;
    
    // Save battery display mode
    EEPROM.write(BATTERY_MODE_ADDR, batteryDisplayMode);
    
    // Save button mapping
    for (int i = 0; i < 7; i++) {
        EEPROM.write(BUTTON_MAPPING_START_ADDR + i, buttonMapping[i]);
    }
    
    // Commit changes to EEPROM
    EEPROM.commit();
}

void SettingsApplication::loadSettings() {
    // Define EEPROM address offsets
    const int BATTERY_MODE_ADDR = 0;
    const int BUTTON_MAPPING_START_ADDR = 1;
    
    // Load battery display mode
    batteryDisplayMode = EEPROM.read(BATTERY_MODE_ADDR);
    
    // Validate battery display mode
    if (batteryDisplayMode < 0 || batteryDisplayMode > 1) {
        batteryDisplayMode = 0; // Default to icon only
    }
    
    // Load button mapping
    for (int i = 0; i < 7; i++) {
        buttonMapping[i] = EEPROM.read(BUTTON_MAPPING_START_ADDR + i);
        
        // Validate button mapping
        if (buttonMapping[i] < 0 || buttonMapping[i] > 6) {
            // Reset to default mapping (button index maps to itself)
            buttonMapping[i] = i;
        }
    }
}

int SettingsApplication::getBatteryDisplayMode() {
    return batteryDisplayMode;
}

void SettingsApplication::setBatteryDisplayMode(int mode) {
    if (mode >= 0 && mode <= 1) {
        batteryDisplayMode = mode;
    }
}

int SettingsApplication::getButtonMapping(int buttonIndex) {
    if (buttonIndex >= 0 && buttonIndex < 7) {
        return buttonMapping[buttonIndex];
    }
    return -1; // Invalid index
}

void SettingsApplication::setButtonMapping(int buttonIndex, int newMapping) {
    if (buttonIndex >= 0 && buttonIndex < 7) {
        buttonMapping[buttonIndex] = newMapping;
    }
}

int SettingsApplication::getMappedButtonPin(int buttonIndex) {
    if (buttonIndex >= 0 && buttonIndex < 7) {
        // Get the mapped button index
        int mappedIndex = buttonMapping[buttonIndex];
        
        // Convert button index to GPIO pin
        switch (mappedIndex) {
            case 0: return BUTTON_UP_PIN;
            case 1: return BUTTON_DOWN_PIN;
            case 2: return BUTTON_LEFT_PIN;
            case 3: return BUTTON_RIGHT_PIN;
            case 4: return BUTTON_OK_PIN;
            case 5: return BUTTON_BACK_PIN;
            case 6: return BUTTON_FUNCTION_PIN;
            default: return -1; // Invalid index
        }
    }
    return -1; // Invalid index
}

void SettingsApplication::resetToDefaults() {
     batteryDisplayMode = 0;
     selectedSetting = 0;
     
     // Reset button mapping to defaults (button index maps to itself)
     for (int i = 0; i < 7; i++) {
         buttonMapping[i] = i;
     }
 }