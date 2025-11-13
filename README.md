# HAKLESMY - Flipper Zero-like Device

![Project Status](https://img.shields.io/badge/status-completed-brightgreen)
![Platform](https://img.shields.io/badge/platform-ESP32-blue)
![Display](https://img.shields.io/badge/display-SH1106-yellow)
![License](https://img.shields.io/badge/license-MIT-green)

A Flipper Zero-inspired multi-application device based on ESP32 with SH1106 OLED display. This project implements a firmware with multiple applications including a DOOM-like game, WiFi scanner, file explorer, and more.

## Features

- Carousel-style application menu
- DOOM-like pseudo-3D game
- WiFi network scanner
- SD card file explorer
- Virtual pet (Tamagotchi)
- Stopwatch
- Calculator
- Custom bitmap icons for all applications
- Intuitive button navigation

## Hardware Requirements

- ESP32 development board
- SH1106 OLED display (128x64 pixels)
- MicroSD card module
- 7 push buttons
- Jumper wires
- Breadboard (optional)

## Wiring Diagram

```
ESP32         SH1106 Display
-----         --------------
GPIO21  ----> SDA
GPIO22  ----> SCL
3.3V    ----> VCC
GND     ----> GND

ESP32         SD Card Module
-----         --------------
GPIO23  ----> MOSI
GPIO19  ----> MISO
GPIO18  ----> SCK
GPIO5   ----> CS
3.3V    ----> VCC
GND     ----> GND

ESP32         Buttons
-----         -------
GPIO12  ----> UP Button
GPIO14  ----> DOWN Button
GPIO27  ----> LEFT Button
GPIO26  ----> RIGHT Button
GPIO25  ----> OK Button
GPIO33  ----> BACK Button
RST     ----> RESET Button
```

## Installation

1. Clone this repository:
   ```bash
   git clone https://github.com/yourusername/haklesmy.git
   cd haklesmy
   ```

2. Install PlatformIO Core or use PlatformIO IDE

3. Install dependencies:
   ```bash
   pio lib install
   ```

4. Build the firmware:
   ```bash
   pio run
   ```

5. Upload to ESP32:
   ```bash
   pio run --target upload
   ```

## Applications

### DOOM
A simplified pseudo-3D first-person shooter inspired by the classic DOOM game. Features raycasting-based rendering, enemy entities, and a heads-up display.

### Slots
A casino-style slot machine game where you can bet credits and spin the reels to win prizes.

### WiFi Scanner
Scans for available WiFi networks and displays information about them including signal strength and encryption type.

### Explorer
Browse files and directories on the SD card. View text file contents and navigate through directory structures.

### Tamagotchi
A virtual pet simulation where you can feed, play with, and clean your digital pet. The pet's status changes over time.

### Stopwatch
A simple stopwatch with start/stop, lap time recording, and reset functionality.

### Calculator
A basic calculator supporting addition, subtraction, multiplication, and division operations.

## Controls

- UP: Navigate up / Move forward (DOOM) / Feed pet (Tamagotchi) / Lap time (Stopwatch)
- DOWN: Navigate down / Move backward (DOOM) / Play with pet (Tamagotchi) / Reset (Stopwatch)
- LEFT: Turn left (DOOM) / Clean pet (Tamagotchi)
- RIGHT: Turn right (DOOM)
- OK: Select / Confirm / Start/Stop (Stopwatch)
- BACK: Return / Cancel / Exit applications

## File Structure

```
src/
├── apps/              # Application implementations
│   ├── Application.h          # Base application class
│   ├── CalculatorApplication.* # Calculator app
│   ├── DoomApplication.*       # DOOM game app
│   ├── ExplorerApplication.*   # File explorer app
│   ├── MenuApplication.*       # Main menu app
│   ├── StartupScreen.*         # Startup screen app
│   ├── StopwatchApplication.*  # Stopwatch app
│   └── TamagotchiApplication.* # Virtual pet app
├── core/              # Core system components
│   ├── ApplicationManager.*    # App management
│   ├── Button.*                # Button handling
│   ├── Display.*               # Display abstraction
│   └── Navigation.*            # Navigation system
├── graphics/          # Graphics and bitmaps
│   ├── bitmaps.*               # Bitmap definitions
├── utils/             # Utility functions
│   ├── logger.*                # Logging system
├── config.h           # Configuration settings
└── main.cpp           # Main entry point
```

## Bitmap Icons

All applications feature custom 16x16 pixel bitmap icons designed in the style of Flipper Zero:
- DOOM: Skull icon
- WiFi Scanner: WiFi signal icon
- Explorer: File and folder icons
- Tamagotchi: Pet icon
- Stopwatch: Clock icon
- Calculator: Calculator icon
- Settings: Gear icon

## Development

### Adding New Applications

1. Create a new application class inheriting from `Application`
2. Implement the required methods (`render`, `handleNavigation`, etc.)
3. Create a 16x16 bitmap icon
4. Register the application in `main.cpp`

### Customizing Display

The display system uses the Adafruit GFX library with a custom `Display` wrapper that provides:
- Text rendering with color control
- Bitmap drawing
- Rectangle and line drawing
- Clear screen functionality

## Testing

See [TESTING.md](TESTING.md) for detailed testing procedures for all applications and features.

## Documentation

- [User Manual](USER_MANUAL.md) - Complete user guide
- [Testing Plan](TESTING.md) - Comprehensive testing procedures

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- Inspired by the Flipper Zero device
- Uses Adafruit GFX and SH1106 libraries
- DOOM rendering techniques based on classic raycasting algorithms

## Remote Control

This firmware supports serial commands that can replace physical button presses, allowing you to control the device remotely through a serial interface. A Python GUI application is included to provide a graphical d-pad interface for sending these commands.

### ESP Controller Application

A Python GUI application (`esp_controller_gui.py`) is provided with:
- Cross-shaped d-pad with UP, DOWN, LEFT, RIGHT buttons
- OK button in the center
- FUNCTION and BACK buttons
- BACK LONG button for long press simulation
- Serial communication to send commands to the ESP device
- Automatic port detection
- Keyboard shortcuts for all commands (Arrow keys, Enter, Escape, F1)
- Visual connection status indicator
- Device display visualization showing real-time screen content (128x64 pixels)

See [ESP_CONTROLLER_README.md](ESP_CONTROLLER_README.md) for detailed usage instructions.

For the Python GUI controller, see [ESP_CONTROLLER_GUI_README.md](ESP_CONTROLLER_GUI_README.md).

### Supported Serial Commands

- `UP` - Simulate pressing the UP button
- `DOWN` - Simulate pressing the DOWN button
- `LEFT` - Simulate pressing the LEFT button
- `RIGHT` - Simulate pressing the RIGHT button
- `OK` - Simulate pressing the OK button
- `BACK` - Simulate pressing the BACK button
- `FUNCTION` - Simulate pressing the FUNCTION button
- `BACK_LONG` - Simulate a long press on the BACK button

Commands are case-sensitive and should be sent via the serial interface (115200 baud rate) followed by a newline character.

For detailed information about the serial command protocol, see [SERIAL_COMMANDS.md](SERIAL_COMMANDS.md).

### Building Executables

See [BUILDING_EXECUTABLES.md](BUILDING_EXECUTABLES.md) for instructions on creating standalone executables for Windows, Linux, and Android.

The Python controller can be built into standalone executables for easy distribution without requiring Python installation:
- Windows (.exe) using PyInstaller or cx_Freeze
- Linux executables using PyInstaller or cx_Freeze
- Android APK using Kivy + Buildozer (requires conversion)