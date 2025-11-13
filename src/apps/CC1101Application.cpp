#include "CC1101Application.h"
#include "graphics/bitmaps.h"
#include "config.h"

// CC1101 pin definitions
#define CC1101_GDO0 26  // GDO0 pin connected to ESP32 GPIO26
#define CC1101_SCK 18   // SCK pin connected to ESP32 GPIO18 (shared with SD card)
#define CC1101_MISO 19  // MISO pin connected to ESP32 GPIO19 (shared with SD card)
#define CC1101_MOSI 23  // MOSI pin connected to ESP32 GPIO23 (shared with SD card)
#define CC1101_CS 27    // CS pin connected to ESP32 GPIO27

CC1101Application::CC1101Application() {
    running = false;
    mode = 0; // RX mode by default
    frequency = 433; // MHz
    receivedData = "";
    transmittedData = "Hello World!";
    lastActionTime = 0;
}

void CC1101Application::initialize() {
    running = true;
    
    // Initialize CC1101 module
    ELECHOUSE_cc1101.setSpiPin(CC1101_SCK, CC1101_MISO, CC1101_MOSI, CC1101_CS);
    ELECHOUSE_cc1101.setGDO0(CC1101_GDO0);
    ELECHOUSE_cc1101.Init();
    
    // Set initial frequency
    ELECHOUSE_cc1101.setMHZ(frequency);
    
    // Set mode to RX
    if (mode == 0) {
        ELECHOUSE_cc1101.SetRx();
    } else {
        ELECHOUSE_cc1101.SetTx();
    }
}

void CC1101Application::update() {
    if (!running) return;
    
    // Check for received data in RX mode
    if (mode == 0) {
        if (ELECHOUSE_cc1101.CheckRxFifo(100)) { // Check if data is available
            byte data[100];
            byte len = ELECHOUSE_cc1101.ReceiveData(data);
            data[len] = '\0'; // Null terminate
            receivedData = String((char*)data);
            lastActionTime = millis();
        }
    }
    
    // Clear status messages after 3 seconds
    if (lastActionTime > 0 && millis() - lastActionTime > 3000) {
        lastActionTime = 0;
    }
}

void CC1101Application::render(Display* display) {
    display->clear();
    
    // Draw title
    display->drawString(0, 0, "CC1101 Transceiver");
    
    // Draw mode
    if (mode == 0) {
        display->drawString(0, 15, "Mode: RX");
    } else {
        display->drawString(0, 15, "Mode: TX");
    }
    
    // Draw frequency
    display->drawString(0, 25, ("Freq: " + String(frequency) + " MHz").c_str());
    
    // Draw data based on mode
    if (mode == 0) {
        // RX mode - show received data
        display->drawString(0, 35, "Received:");
        if (receivedData.length() > 0) {
            display->drawString(0, 45, receivedData.c_str());
        } else {
            display->drawString(0, 45, "No data");
        }
    } else {
        // TX mode - show data to transmit
        display->drawString(0, 35, "To Transmit:");
        display->drawString(0, 45, transmittedData.c_str());
    }
    
    // Show status message if any
    if (lastActionTime > 0) {
        if (mode == 0) {
            display->drawString(0, 55, "Data received!");
        } else {
            display->drawString(0, 55, "Data sent!");
        }
    }
    
    display->update();
}

void CC1101Application::cleanup() {
    running = false;
    ELECHOUSE_cc1101.SetRx(); // Reset to RX mode
}

// Navigation handlers
void CC1101Application::onUpButton() {
    if (mode == 1) {
        // In TX mode, change the data to transmit
        transmittedData += "A";
        if (transmittedData.length() > 20) {
            transmittedData = "Hello World!";
        }
    }
}

void CC1101Application::onDownButton() {
    if (mode == 1) {
        // In TX mode, change the data to transmit
        if (transmittedData.length() > 1) {
            transmittedData.remove(transmittedData.length() - 1);
        }
    }
}

void CC1101Application::onLeftButton() {
    changeFrequency(-1);
}

void CC1101Application::onRightButton() {
    changeFrequency(1);
}

void CC1101Application::onOkButton() {
    switchMode();
}

void CC1101Application::onBackButton() {
    // Exit application
    cleanup();
}

void CC1101Application::onFunctionButton() {
    if (mode == 1) {
        sendData();
    }
}

void CC1101Application::onBackLongPress() {
    // Do nothing
}

// Metadata methods
const char* CC1101Application::getName() {
    return "CC1101 Transceiver";
}

bool CC1101Application::isRunning() {
    return running;
}

// CC1101 specific methods
void CC1101Application::switchMode() {
    mode = 1 - mode; // Toggle between 0 and 1
    
    if (mode == 0) {
        ELECHOUSE_cc1101.SetRx();
    } else {
        ELECHOUSE_cc1101.SetTx();
    }
}

void CC1101Application::changeFrequency(int delta) {
    frequency += delta;
    
    // Limit frequency range
    if (frequency < 300) frequency = 300;
    if (frequency > 900) frequency = 900;
    
    ELECHOUSE_cc1101.setMHZ(frequency);
}

void CC1101Application::sendData() {
    if (mode == 1) {
        byte data[transmittedData.length() + 1];
        transmittedData.getBytes(data, transmittedData.length() + 1);
        ELECHOUSE_cc1101.SendData(data, transmittedData.length());
        lastActionTime = millis();
    }
}