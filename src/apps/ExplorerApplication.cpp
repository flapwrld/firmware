#include "ExplorerApplication.h"
#include "core/ApplicationManager.h"
#include <SD.h>
#include <SPI.h>
#include "config.h"

extern ApplicationManager appManager;

ExplorerApplication::ExplorerApplication() {
    running = false;
    currentIndex = 0;
    sdInitialized = false;
}

void ExplorerApplication::initialize() {
    running = true;
    currentIndex = 0;
    
    // Initialize SPI with custom pins
    SPI.begin(SD_SCK_PIN, SD_MISO_PIN, SD_MOSI_PIN, SD_CS_PIN);
    
    // Initialize SD card
    if (!SD.begin(SD_CS_PIN)) {
        Serial.println("SD card initialization failed!");
        sdInitialized = false;
    } else {
        Serial.println("SD card initialized.");
        sdInitialized = true;
        root = SD.open("/");
    }
}

void ExplorerApplication::update() {
    // Nothing to update continuously
}

void ExplorerApplication::render(Display* display) {
    // Clear display
    display->clear();
    
    // Draw title with icon
    display->drawBitmap(0, 0, explorerIcon, EXPLORER_ICON_WIDTH, EXPLORER_ICON_HEIGHT, 1);
    display->drawString(20, 5, "File Explorer");
    
    if (!sdInitialized) {
        display->drawString(10, 30, "SD Card Not Found");
        display->drawString(15, 40, "Insert SD Card");
    } else {
        // Draw file/folder list from SD card
        File root = SD.open("/");
        if (!root) {
            display->drawString(10, 30, "Cannot open root");
            root.close();
        } else {
            File file = root.openNextFile();
            const int maxItems = 6;
            const char* items[maxItems];
            bool isDirectory[maxItems];
            int itemCount = 0;
            
            // Read up to maxItems files/directories
            while (file && itemCount < maxItems) {
                items[itemCount] = file.name();
                isDirectory[itemCount] = file.isDirectory();
                itemCount++;
                file = root.openNextFile();
            }
            file.close();
            root.close();
            
            int startY = 20;
            int itemHeight = 10;
            
            // Show up to 4 items at a time with scrolling
            int startIndex = max(0, currentIndex - 1);
            int endIndex = min(startIndex + 4, itemCount);
            
            for (int i = startIndex; i < endIndex; i++) {
                int yPos = startY + (i - startIndex) * itemHeight;
                
                // Highlight selected item
                if (i == currentIndex) {
                    display->fillRect(0, yPos - 1, 128, itemHeight, 1);
                    // Draw text in black (0) on white background
                    display->setTextColor(0, 1);
                    display->drawString(15, yPos, (char*)items[i]);
                    display->setTextColor(1, 0); // Reset to normal
                    // Draw selection indicator
                    display->drawBitmap(5, yPos, fileIcon, FILE_ICON_WIDTH, FILE_ICON_HEIGHT, 0); // Inverted color
                } else {
                    display->drawString(15, yPos, (char*)items[i]);
                    // Draw icon based on item type
                    if (isDirectory[i]) {
                        display->drawBitmap(5, yPos, folderIcon, FOLDER_ICON_WIDTH, FOLDER_ICON_HEIGHT, 1);
                    } else {
                        display->drawBitmap(5, yPos, fileIcon, FILE_ICON_WIDTH, FILE_ICON_HEIGHT, 1);
                    }
                }
            }
        }
    }
    
    // Draw navigation hint
    display->drawString(10, 55, "Up/Down: Navigate");
    display->drawString(15, 65, "Back: Return");
    
    // Update display
    display->update();
}

void ExplorerApplication::cleanup() {
    running = false;
    if (sdInitialized) {
        root.close();
    }
}

// Navigation handlers
void ExplorerApplication::onUpButton() {
    if (sdInitialized && currentIndex > 0) {
        currentIndex--;
    }
}

void ExplorerApplication::onDownButton() {
    if (sdInitialized) {
        // Count items in SD card root directory
        File root = SD.open("/");
        if (root) {
            int itemCount = 0;
            File file = root.openNextFile();
            while (file && itemCount < 6) {
                itemCount++;
                file = root.openNextFile();
            }
            file.close();
            root.close();
            
            if (currentIndex < itemCount - 1) {
                currentIndex++;
            }
        }
    }
}

void ExplorerApplication::onLeftButton() {
    // Do nothing
}

void ExplorerApplication::onRightButton() {
    // Do nothing
}

void ExplorerApplication::onOkButton() {
    if (sdInitialized) {
        // Get the selected item
        File root = SD.open("/");
        if (root) {
            File file;
            int itemCount = 0;
            
            // Navigate to the selected item
            while ((file = root.openNextFile()) && itemCount < currentIndex) {
                itemCount++;
            }
            
            if (file) {
                if (file.isDirectory()) {
                    // For this example, we'll just print to serial
                    Serial.print("Opening directory: ");
                    Serial.println(file.name());
                } else {
                    // For this example, we'll just print to serial
                    Serial.print("Opening file: ");
                    Serial.println(file.name());
                }
                file.close();
            }
            root.close();
        }
    }
}

void ExplorerApplication::onBackButton() {
    // Go back to menu
    appManager.switchToApplication(1);
}

void ExplorerApplication::onFunctionButton() {
    // Do nothing
}

void ExplorerApplication::onBackLongPress() {
    // Do nothing
}

// Metadata methods
const char* ExplorerApplication::getName() {
    return "File Explorer";
}

bool ExplorerApplication::isRunning() {
    return running;
}