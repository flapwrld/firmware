# HAKLESMY Flipper Zero-like Device User Manual

## Table of Contents
1. [Device Overview](#device-overview)
2. [Hardware Setup](#hardware-setup)
3. [Getting Started](#getting-started)
4. [Navigation Controls](#navigation-controls)
5. [Applications](#applications)
   - [DOOM](#doom)
   - [WiFi Scanner](#wifi-scanner)
   - [Explorer](#explorer)
   - [Tamagotchi](#tamagotchi)
   - [Stopwatch](#stopwatch)
   - [Calculator](#calculator)
6. [SD Card Usage](#sd-card-usage)
7. [Troubleshooting](#troubleshooting)
8. [Remote Control](#remote-control)

## Device Overview

The HAKLESMY is a Flipper Zero-like device based on the ESP32 microcontroller with an SH1106 OLED display (128x64 pixels). It features a carousel-style menu system and several built-in applications for security research, entertainment, and utility purposes.

## Hardware Setup

### Components
- ESP32 development board
- SH1106 OLED display (128x64)
- MicroSD card module
- 7 push buttons (UP, DOWN, LEFT, RIGHT, OK, BACK, RESET)
- Jumper wires
- Breadboard (optional)

### Wiring Connections
- Display SDA -> ESP32 GPIO21
- Display SCL -> ESP32 GPIO22
- SD Card MOSI -> ESP32 GPIO23
- SD Card MISO -> ESP32 GPIO19
- SD Card SCK -> ESP32 GPIO18
- SD Card CS -> ESP32 GPIO5
- UP Button -> ESP32 GPIO12
- DOWN Button -> ESP32 GPIO14
- LEFT Button -> ESP32 GPIO27
- RIGHT Button -> ESP32 GPIO26
- OK Button -> ESP32 GPIO25
- BACK Button -> ESP32 GPIO33
- RESET Button -> ESP32 RST

## Getting Started

1. Insert a microSD card (formatted as FAT32) into the SD card module
2. Connect the device to power via USB
3. The device will boot and display the startup screen
4. Press the OK button to enter the main menu

## Navigation Controls

- UP: Navigate up in menus, access menu in DOOM, feed pet in Tamagotchi
- DOWN: Navigate down in menus, move forward in DOOM, play with pet in Tamagotchi
- LEFT: Turn left in DOOM, clean pet in Tamagotchi
- RIGHT: Turn right in DOOM
- OK: Select items, confirm actions
- BACK: Return to previous screen, cancel actions, exit applications

## Applications

### DOOM

A simplified pseudo-3D first-person shooter game inspired by the classic DOOM.

**Controls:**
- UP: Move forward
- DOWN: Move backward
- LEFT: Turn left
- RIGHT: Turn right
- UP (in game): Access menu
- BACK: Return to main menu

**Features:**
- Raycasting-based 3D environment
- Simple enemy entities
- Health and ammo display
- In-game menu system

### Slots

A casino-style slot machine game.

**Features:**
- Three spinning reels with different symbols
- Betting system with credits
- Win detection and payout calculation
- Simple and intuitive interface

**Controls:**
- UP: Increase bet amount
- DOWN: Decrease bet amount
- OK: Spin the reels
- BACK: Return to main menu

### WiFi Scanner

Scans for available WiFi networks and displays information about them.

**Features:**
- Real-time WiFi scanning
- Network strength indicators
- Network information display (SSID, encryption type)
- Simulated connection to networks

**Usage:**
1. Launch the application
2. Wait for scanning to complete
3. Select a network to view details
4. Press OK to simulate connection

### Explorer

Browse files and directories on the SD card.

**Features:**
- File and directory listing
- File content viewing
- Directory navigation

**Usage:**
1. Launch the application
2. Navigate directories with UP/DOWN
3. Select directories to enter with OK
4. Select files to view contents
5. Press BACK to return to parent directory

### Tamagotchi

A virtual pet simulation game.

**Features:**
- Pet status monitoring (hunger, happiness, cleanliness)
- Feeding, playing, and cleaning actions
- Pet state changes over time

**Controls:**
- UP: Feed pet
- DOWN: Play with pet
- LEFT: Clean pet
- OK: Check pet status
- BACK: Return to main menu

### Stopwatch

A simple stopwatch application.

**Features:**
- Start/Stop functionality
- Lap time recording
- Reset function

**Controls:**
- OK: Start/Stop timer
- UP: Record lap time
- DOWN: Reset timer
- BACK: Return to main menu

### Calculator

A basic calculator with arithmetic operations.

**Features:**
- Addition, subtraction, multiplication, division
- Decimal point support
- Clear function

**Controls:**
- UP/DOWN: Navigate number pad
- LEFT/RIGHT: Navigate operation buttons
- OK: Select/confirm
- BACK: Clear entry/return to menu

## SD Card Usage

The device supports FAT32 formatted microSD cards up to 32GB.

**Supported Operations:**
- Reading files
- Browsing directories
- Viewing text file contents

**File Recommendations:**
- Keep filenames short (8.3 format recommended)
- Use plain text files for best compatibility
- Organize files in directories for easier navigation

## Troubleshooting

### Display Issues
- Check all wiring connections to the display
- Ensure the display is properly powered
- Verify SDA/SCL connections to GPIO21/GPIO22

### SD Card Problems
- Ensure the SD card is properly inserted
- Check SD card wiring connections
- Verify the SD card is formatted as FAT32
- Try a different SD card

### Button Responsiveness
- Check button wiring connections
- Ensure buttons are properly connected to ground
- Verify pull-up resistors are used or enabled

### WiFi Scanner Not Finding Networks
- Ensure the device is in an area with WiFi networks
- Check that the WiFi antenna (if any) is properly connected
- Restart the application

### Device Not Powering On
- Check USB power connection
- Verify the ESP32 board is functioning
- Check for short circuits in wiring

### Firmware Issues
- Re-flash the firmware using PlatformIO
- Check for compilation errors
- Verify all dependencies are installed

## Remote Control

The HAKLESMY firmware supports serial commands that can replace physical button presses, allowing you to control the device remotely through a serial interface. This feature is useful for testing, automation, or controlling the device from a computer.

### Serial Command Interface

The device accepts the following commands via the serial interface (115200 baud rate):
- `UP` - Simulate pressing the UP button
- `DOWN` - Simulate pressing the DOWN button
- `LEFT` - Simulate pressing the LEFT button
- `RIGHT` - Simulate pressing the RIGHT button
- `OK` - Simulate pressing the OK button
- `BACK` - Simulate pressing the BACK button
- `FUNCTION` - Simulate pressing the FUNCTION button
- `BACK_LONG` - Simulate a long press on the BACK button

Each command should be sent on its own line followed by a newline character. Commands are case-sensitive.

For detailed information about the serial command protocol, see [SERIAL_COMMANDS.md](SERIAL_COMMANDS.md).

### ESP Controller Application

A Python GUI application (`esp_controller_gui.py`) is provided to make remote control easier. It features:
- Cross-shaped d-pad with UP, DOWN, LEFT, RIGHT buttons
- OK button in the center
- FUNCTION and BACK buttons
- BACK LONG button for long press simulation
- Serial communication to send commands to the ESP device
- Automatic port detection
- Keyboard shortcuts for all commands (Arrow keys, Enter, Escape, F1)
- Visual connection status indicator (red/green circle)
- Device display visualization showing real-time screen content (128x64 pixels)

To use the controller:
1. Connect your ESP device to your computer via USB
2. Install the required dependencies: `pip install -r requirements.txt`
3. Run the controller application: `python esp_controller_gui.py`
4. Select the appropriate serial port from the dropdown
5. Set the baud rate to 115200 (default)
6. Click "Connect"
7. Use the d-pad buttons or keyboard shortcuts to control your device

Keyboard shortcuts:
- Arrow Keys: UP, DOWN, LEFT, RIGHT
- Enter: OK
- Escape: BACK
- F1: FUNCTION

For detailed information about the GUI controller, see [ESP_CONTROLLER_GUI_README.md](ESP_CONTROLLER_GUI_README.md).

### Command Line Interface

A command-line interface is also available for sending serial commands:
1. Connect your ESP device to your computer via USB
2. Run the command-line tool: `python test_serial_commands.py`
3. Follow the prompts to select a serial port and enter commands

### Building Executables

The ESP Controller application can be built into standalone executables for different platforms. See [BUILDING_EXECUTABLES.md](BUILDING_EXECUTABLES.md) for detailed instructions on creating executables for:
- Windows (.exe)
- Linux
- Android

This allows you to distribute the controller application without requiring users to install Python or dependencies.

The Python controller can be built into standalone executables for easy distribution without requiring Python installation:
- Windows (.exe) using PyInstaller or cx_Freeze
- Linux executables using PyInstaller or cx_Freeze
- Android APK using Kivy + Buildozer (requires conversion)