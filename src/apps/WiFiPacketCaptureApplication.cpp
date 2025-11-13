#include "WiFiPacketCaptureApplication.h"
#include "core/Display.h"
#include <Arduino.h>

WiFiPacketCaptureApplication::WiFiPacketCaptureApplication() {
    running = false;
    capturing = false;
    packetCount = 0;
    managementPackets = 0;
    controlPackets = 0;
    dataPackets = 0;
    recentPacketIndex = 0;
    
    // Initialize recent packets
    for (int i = 0; i < MAX_DISPLAY_PACKETS; i++) {
        memset(recentPackets[i].ssid, 0, sizeof(recentPackets[i].ssid));
        memset(recentPackets[i].mac, 0, sizeof(recentPackets[i].mac));
        recentPackets[i].rssi = 0;
        recentPackets[i].timestamp = 0;
        recentPackets[i].type = 0;
    }
}

void WiFiPacketCaptureApplication::initialize() {
    running = true;
    Serial.println("WiFi Packet Capture Application initialized");
}

void WiFiPacketCaptureApplication::update() {
    if (!running) return;
    
    // Simulate packet capture
    if (capturing && millis() % 1000 < 50) {
        processPacket();
    }
}

void WiFiPacketCaptureApplication::render(Display* display) {
    if (!running) return;
    
    
    if (!capturing) {
        display->drawString(0, 0, "WiFi Packet Capture");
        display->drawString(0, 10, "Press OK to start");
        display->drawString(0, 20, "capturing packets");
    } else {
        display->drawString(0, 0, "Capturing packets...");
        display->drawString(0, 10, "Total: " + String(packetCount));
        display->drawString(0, 20, "Mgmt: " + String(managementPackets));
        display->drawString(0, 30, "Ctrl: " + String(controlPackets));
        display->drawString(0, 40, "Data: " + String(dataPackets));
        display->drawString(0, 50, "Press BACK to stop");
    }
}

void WiFiPacketCaptureApplication::cleanup() {
    running = false;
    capturing = false;
    Serial.println("WiFi Packet Capture Application cleaned up");
}

void WiFiPacketCaptureApplication::onUpButton() {
    // Not used in this application
}

void WiFiPacketCaptureApplication::onDownButton() {
    // Not used in this application
}

void WiFiPacketCaptureApplication::onLeftButton() {
    // Not used in this application
}

void WiFiPacketCaptureApplication::onRightButton() {
    // Not used in this application
}

void WiFiPacketCaptureApplication::onOkButton() {
    if (!capturing) {
        startCapture();
    }
}

void WiFiPacketCaptureApplication::onBackButton() {
    if (capturing) {
        stopCapture();
    } else {
        // Exit application
        running = false;
    }
}

void WiFiPacketCaptureApplication::onFunctionButton() {
    // Not used in this application
}

void WiFiPacketCaptureApplication::onBackLongPress() {
    // Exit application
    running = false;
}

const char* WiFiPacketCaptureApplication::getName() {
    return "WiFi Packet Capture";
}

bool WiFiPacketCaptureApplication::isRunning() {
    return running;
}

void WiFiPacketCaptureApplication::startCapture() {
    capturing = true;
    packetCount = 0;
    managementPackets = 0;
    controlPackets = 0;
    dataPackets = 0;
    Serial.println("Started packet capture");
}

void WiFiPacketCaptureApplication::stopCapture() {
    capturing = false;
    Serial.println("Stopped packet capture");
}

void WiFiPacketCaptureApplication::processPacket() {
    packetCount++;
    
    // Simulate different packet types
    int packetType = random(0, 3);
    switch (packetType) {
        case 0:
            managementPackets++;
            break;
        case 1:
            controlPackets++;
            break;
        case 2:
            dataPackets++;
            break;
    }
    
    // Add to recent packets display
    recentPacketIndex = (recentPacketIndex + 1) % MAX_DISPLAY_PACKETS;
    snprintf(recentPackets[recentPacketIndex].ssid, sizeof(recentPackets[recentPacketIndex].ssid), "AP%d", packetCount % 100);
    recentPackets[recentPacketIndex].rssi = random(-90, -30);
    recentPackets[recentPacketIndex].timestamp = millis();
    recentPackets[recentPacketIndex].type = packetType;
    
    Serial.print("Processed packet #");
    Serial.println(packetCount);
}