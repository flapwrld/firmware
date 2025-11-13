#ifndef WIFI_PACKET_CAPTURE_APPLICATION_H
#define WIFI_PACKET_CAPTURE_APPLICATION_H

#include "Application.h"
#include "graphics/bitmaps.h"
#include <WiFi.h>

class WiFiPacketCaptureApplication : public Application {
private:
    bool running;
    bool capturing;
    int packetCount;
    int managementPackets;
    int controlPackets;
    int dataPackets;
    static const int MAX_DISPLAY_PACKETS = 5;
    struct PacketInfo {
        char ssid[32];
        uint8_t mac[6];
        int rssi;
        unsigned long timestamp;
        int type; // 0=management, 1=control, 2=data
    };
    PacketInfo recentPackets[MAX_DISPLAY_PACKETS];
    int recentPacketIndex;
    
public:
    WiFiPacketCaptureApplication();
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
    
    // Packet capture methods
    void startCapture();
    void stopCapture();
    void processPacket();
};

#endif // WIFI_PACKET_CAPTURE_APPLICATION_H