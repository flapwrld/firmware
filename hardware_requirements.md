# Hardware Requirements for Bruce Firmware Features

## Overview
This document outlines the hardware requirements for implementing all WiFi and Bluetooth functions from the Bruce firmware in the current ESP32-based system.

## Current Hardware Platform
- **Microcontroller**: ESP32 (ESP32-WROOM-32 or similar)
- **Display**: OLED display (128x64 pixels)
- **Buttons**: 7 buttons (Up, Down, Left, Right, OK, Back, Function)
- **SD Card Slot**: SPI-based SD card reader
- **Power Supply**: 3.3V regulated power supply

## WiFi Functionality Requirements

### WiFi Packet Capture
- **WiFi Radio**: ESP32 integrated WiFi (2.4GHz only)
- **Memory**: Sufficient RAM for packet buffering (minimum 4MB PSRAM recommended)
- **Storage**: SD card for saving captured packets (optional but recommended)

### WiFi Deauthentication Attack
- **WiFi Radio**: ESP32 integrated WiFi with raw frame sending capability
- **Processing Power**: Sufficient CPU for frame generation and sending
- **Memory**: RAM for frame buffers

### Enhanced WiFi Scanning
- **WiFi Radio**: ESP32 integrated WiFi
- **Memory**: RAM for storing network information (20+ networks)
- **Processing Power**: CPU for channel hopping and analysis

### Evil Portal
- **WiFi Radio**: ESP32 integrated WiFi with AP mode capability
- **Memory**: RAM for web server operation and credential storage
- **Processing Power**: CPU for handling web requests
- **Storage**: SD card for exporting credentials (optional)

## Bluetooth Functionality Requirements

### Bluetooth Scanning
- **Bluetooth Radio**: ESP32 integrated Bluetooth Classic and BLE
- **Memory**: RAM for storing device information (15+ devices)
- **Processing Power**: CPU for continuous scanning

### Bluetooth Attack/Analysis
- **Bluetooth Radio**: ESP32 integrated Bluetooth Classic and BLE
- **Memory**: RAM for service discovery and connection data
- **Processing Power**: CPU for vulnerability analysis
- **Stack**: Complete Bluetooth stack support in ESP-IDF/Arduino framework

## Additional Hardware Considerations

### Antenna Requirements
- **WiFi Antenna**: External antenna recommended for better range and packet capture
- **Bluetooth Antenna**: External antenna can improve Bluetooth scanning range

### Power Considerations
- **Current Draw**: WiFi and Bluetooth operations can significantly increase power consumption
- **Battery Life**: Consider power management for portable applications
- **Heat Dissipation**: Continuous RF operations may generate heat

### Optional Enhancements
- **External Flash**: Additional flash storage for firmware updates and data logging
- **External RAM**: PSRAM for larger packet buffers and data storage
- **Ethernet**: For wired network testing capabilities
- **USB**: For direct packet injection or as a USB attack platform

## Hardware Limitations

### ESP32 Limitations
- **WiFi Frequency**: Limited to 2.4GHz band only (no 5GHz support)
- **Memory Constraints**: Limited RAM (520KB) and flash (4MB typical)
- **Processing Power**: May struggle with complex real-time operations
- **Simultaneous Operations**: WiFi and Bluetooth cannot operate simultaneously at full capacity

### Regulatory Considerations
- **RF Compliance**: Ensure operations comply with local RF regulations
- **Legal Restrictions**: Some features may be restricted in certain jurisdictions
- **Certification**: Commercial deployment may require additional certifications

## Recommended Hardware Configuration
1. **ESP32 Development Board**: ESP32-WROVER with integrated PSRAM
2. **External Antennas**: High-gain antennas for both WiFi and Bluetooth
3. **SD Card Module**: For data logging and export capabilities
4. **Power Supply**: Stable 3.3V supply with adequate current capacity
5. **Heat Sink**: For extended operation periods