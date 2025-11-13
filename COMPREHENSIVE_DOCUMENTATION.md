# HAKLESMY - Flipper Zero-like Device: Comprehensive Documentation

## Table of Contents
1. [Project Overview](#project-overview)
2. [Hardware Requirements](#hardware-requirements)
3. [Software Architecture](#software-architecture)
4. [System Components](#system-components)
5. [Application Framework](#application-framework)
6. [Input Handling System](#input-handling-system)
7. [Display System](#display-system)
8. [Creating New Applications](#creating-new-applications)
9. [Existing Applications](#existing-applications)
10. [Developer Guide](#developer-guide)
11. [User Guide](#user-guide)
12. [Building and Flashing](#building-and-flashing)
13. [Troubleshooting](#troubleshooting)

## Project Overview

HAKLESMY is a Flipper Zero-inspired multi-application device based on ESP32 with SH1106 OLED display. This project implements a firmware with multiple applications including a DOOM-like game, WiFi scanner, file explorer, and more.

The system is designed with a modular architecture that allows easy addition of new applications while maintaining a consistent user interface and navigation system.

## Hardware Requirements

### Core Components
- ESP32 development board (ESP32-WROOM-32)
- SH1106 OLED display (128x64 pixels)
- MicroSD card module
- 7 push buttons
- Jumper wires
- Breadboard (optional)

### Pin Connections

#### Display Connections
```
ESP32         SH1106 Display
-----         --------------
GPIO21  ----> SDA
GPIO22  ----> SCL
3.3V    ----> VCC
GND     ----> GND
```

#### SD Card Module Connections
```
ESP32         SD Card Module
-----         --------------
GPIO19  ----> MISO
GPIO23  ----> MOSI
GPIO18  ----> SCK
GPIO5   ----> CS
3.3V    ----> VCC
GND     ----> GND
```

#### Button Connections
```
ESP32         Buttons
-----         -------
GPIO12  ----> UP Button
GPIO13  ----> DOWN Button
GPIO14  ----> LEFT Button
GPIO15  ----> RIGHT Button
GPIO16  ----> OK Button
GPIO17  ----> BACK Button
GPIO18  ----> FUNCTION Button
```

Note: All buttons should be connected with pull-up resistors or use the internal pull-up resistors of the ESP32.

## Software Architecture

The HAKLESMY firmware follows a modular architecture with clearly defined components:

```
Main System
├── Core Components
│   ├── ApplicationManager
│   ├── Display
│   ├── Navigation
│   └── Button
├── Applications
│   ├── MenuApplication
│   ├── SettingsApplication
│   ├── ButtonTestApplication
│   ├── DoomApplication
│   ├── TamagotchiApplication
│   ├── ExplorerApplication
│   ├── WifiScannerApplication
│   ├── StopwatchApplication
│   ├── CalculatorApplication
│   ├── SlotsApplication
│   ├── FlappyBirdApplication
│   ├── PaintApplication
│   ├── WiFiPacketCaptureApplication
│   ├── WiFiDeauthAttackApplication
│   ├── EnhancedWifiScannerApplication
│   ├── EvilPortalApplication
│   ├── BluetoothScannerApplication
│   └── BluetoothAttackApplication
├── Graphics
│   └── Bitmaps
└── Utilities
    └── Logger
```

### System Flow
1. System initialization in `main.cpp`
2. Application registration with ApplicationManager
3. Main loop handles input processing, application updates, and rendering
4. Navigation events are passed to the current application
5. Applications render to the display through the Display wrapper

## System Components

### ApplicationManager
The `ApplicationManager` is the central component that manages all applications in the system.

**Key Responsibilities:**
- Register and manage applications
- Handle application switching
- Route navigation events to the current application
- Initialize and update applications

**Public Interface:**
```cpp
class ApplicationManager {
public:
    ApplicationManager();
    void initialize(Display* display, Navigation* navigation);
    void update();
    void render(Display* display);
    void registerApplication(Application* app);
    void switchToApplication(int index);
    int getApplicationCount();
    Application* getCurrentApplication();
    Application* getApplication(int index);
};
```

### Display System
The `Display` class provides a wrapper around the Adafruit GFX library for the SH1106 OLED display.

**Key Features:**
- Drawing primitives (pixels, lines, rectangles, circles)
- Text rendering
- Bitmap drawing
- Double buffering for flicker-free updates
- Display buffer access for remote visualization

**Public Interface:**
```cpp
class Display {
public:
    Display();
    void initialize();
    void clear();
    void update();
    void drawPixel(int16_t x, int16_t y, uint16_t color);
    void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
    void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
    void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
    void drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
    void fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
    void drawString(int16_t x, int16_t y, const char* text);
    void drawString(int16_t x, int16_t y, String text);
    void drawBitmap(int16_t x, int16_t y, const uint8_t bitmap[], int16_t w, int16_t h, uint16_t color);
    void setTextColor(uint16_t color, uint16_t background);
    void fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
    void getDisplayBuffer(uint8_t* buffer, size_t bufferSize);
};
```

### Button System
The `Button` class handles hardware button input with debouncing and long press detection.

**Key Features:**
- Debouncing to prevent false triggers
- Press, release, and long press detection
- Configurable debounce time
- Dynamic pin assignment

**Public Interface:**
```cpp
class Button {
public:
    Button(uint8_t buttonPin);
    void initialize();
    void update();
    bool isPressed();
    bool isReleased();
    bool isLongPressed();
    bool wasPressed();
    bool wasReleased();
    bool wasLongPressed();
    void setPin(uint8_t newPin);  // Change the pin assignment for this button
};
```

### Navigation System
The `Navigation` class manages all input buttons and provides a clean interface for navigation events.

**Key Features:**
- Event-based input handling
- Long press detection for special functions
- Simple interface for applications to check button states

**Public Interface:**
```cpp
enum NavigationEvent {
    NAV_NONE,
    NAV_UP,
    NAV_DOWN,
    NAV_LEFT,
    NAV_RIGHT,
    NAV_OK,
    NAV_BACK,
    NAV_FUNCTION,
    NAV_BACK_LONG
};

class Navigation {
public:
    Navigation(Button* buttonArray);
    void initialize();
    void update();
    NavigationEvent getEvent();
    bool isButtonPressed(int buttonIndex);
    bool isButtonReleased(int buttonIndex);
    bool isButtonLongPressed(int buttonIndex);
};
```

## Application Framework

All applications in HAKLESMY inherit from the base `Application` class, which defines a common interface.

### Application Interface
```cpp
class Application {
public:
    virtual ~Application() {}
    
    // Lifecycle methods
    virtual void initialize() = 0;
    virtual void update() = 0;
    virtual void render(Display* display) = 0;
    virtual void cleanup() = 0;
    
    // Navigation handlers
    virtual void onUpButton() = 0;
    virtual void onDownButton() = 0;
    virtual void onLeftButton() = 0;
    virtual void onRightButton() = 0;
    virtual void onOkButton() = 0;
    virtual void onBackButton() = 0;
    virtual void onFunctionButton() = 0;
    virtual void onBackLongPress() = 0;
    
    // Metadata methods
    virtual const char* getName() = 0;
    virtual bool isRunning() = 0;
};
```

### Application Lifecycle
1. **initialize()** - Called when the application is first started or switched to
2. **update()** - Called every frame to update application logic
3. **render()** - Called every frame to draw the application interface
4. **cleanup()** - Called when switching away from the application

### Navigation Events
Applications receive navigation events through virtual methods:
- `onUpButton()` - UP button pressed
- `onDownButton()` - DOWN button pressed
- `onLeftButton()` - LEFT button pressed
- `onRightButton()` - RIGHT button pressed
- `onOkButton()` - OK button pressed
- `onBackButton()` - BACK button pressed
- `onFunctionButton()` - FUNCTION button pressed
- `onBackLongPress()` - BACK button long pressed (1+ seconds)

## Input Handling System

The input system uses a hierarchical approach:
1. Hardware buttons are managed by the `Button` class
2. The `Navigation` class aggregates button states and generates events
3. The `ApplicationManager` routes events to the current application
4. Applications handle events in their navigation handler methods

### Button Mapping
```
Button Index   GPIO Pin   Function
0              GPIO12     UP
1              GPIO13     DOWN
2              GPIO14     LEFT
3              GPIO15     RIGHT
4              GPIO16     OK
5              GPIO17     BACK
6              GPIO18     FUNCTION
```

The system supports button remapping through the Settings application. When buttons are remapped, the Navigation system will interpret physical button presses according to the user-defined mapping. For example, if the user remaps the UP function to the physical DOWN button, pressing the physical DOWN button will generate a NAV_UP event.

### Long Press Detection
- BACK button long press (1+ seconds) is treated as a special `NAV_BACK_LONG` event
- This is typically used for system-level functions like returning to the main menu

## Display System

The display system uses the Adafruit GFX library with a custom `Display` wrapper that provides:

### Drawing Primitives
- Pixels, lines, rectangles, circles, triangles
- Filled and outlined shapes
- Text rendering with configurable color
- Bitmap drawing with custom icons
- Display buffer access for remote visualization

### Coordinate System
- Top-left corner is (0, 0)
- X increases to the right (0-127)
- Y increases downward (0-63)
- Display resolution: 128x64 pixels

### Color System
- Monochrome display uses 0 (black) and 1 (white)
- Text color can be set with `setTextColor(foreground, background)`

### Bitmap Icons
Each application has a custom 16x16 pixel bitmap icon:
- File Explorer: Document icon
- WiFi Scanner: WiFi signal icon
- Tamagotchi: Pet icon
- Stopwatch: Clock icon
- Calculator: Calculator icon
- DOOM: Skull icon
- And more...

## Creating New Applications

To create a new application, follow these steps:

### 1. Create Application Class
Create a new class that inherits from `Application`:

```cpp
// MyNewApplication.h
#ifndef MY_NEW_APPLICATION_H
#define MY_NEW_APPLICATION_H

#include "Application.h"

class MyNewApplication : public Application {
private:
    bool running;
    // Add your application-specific variables here
    
public:
    MyNewApplication();
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
};

#endif // MY_NEW_APPLICATION_H
```

```cpp
// MyNewApplication.cpp
#include "MyNewApplication.h"
#include "core/ApplicationManager.h"

extern ApplicationManager appManager;

MyNewApplication::MyNewApplication() {
    running = false;
    // Initialize your variables here
}

void MyNewApplication::initialize() {
    running = true;
    // Initialize application state
}

void MyNewApplication::update() {
    // Update application logic
    // This is called every frame
}

void MyNewApplication::render(Display* display) {
    // Clear display
    display->clear();
    
    // Draw your application interface
    display->drawString(0, 0, "My New Application");
    
    // Update display
    display->update();
}

void MyNewApplication::cleanup() {
    running = false;
    // Clean up resources if needed
}

// Navigation handlers
void MyNewApplication::onUpButton() {
    // Handle UP button press
}

void MyNewApplication::onDownButton() {
    // Handle DOWN button press
}

void MyNewApplication::onLeftButton() {
    // Handle LEFT button press
}

void MyNewApplication::onRightButton() {
    // Handle RIGHT button press
}

void MyNewApplication::onOkButton() {
    // Handle OK button press
}

void MyNewApplication::onBackButton() {
    // Handle BACK button press
    // Typically used to return to menu
    appManager.switchToApplication(1); // Switch to main menu
}

void MyNewApplication::onFunctionButton() {
    // Handle FUNCTION button press
}

void MyNewApplication::onBackLongPress() {
    // Handle BACK button long press
}

const char* MyNewApplication::getName() {
    return "My New App";
}

bool MyNewApplication::isRunning() {
    return running;
}
```

### 2. Register Application
Add your application to `main.cpp`:

```cpp
// In main.cpp
#include "apps/MyNewApplication.h"

// Declare instance
MyNewApplication myNewApplication;

// In setup() function, register the application
appManager.registerApplication(&myNewApplication);
```

### 3. Create Icon (Optional)
If you want a custom icon, add it to `graphics/bitmaps.h` and `graphics/bitmaps.cpp`:

```cpp
// In bitmaps.h
extern const uint8_t myNewAppIcon[];
#define MY_NEW_APP_ICON_WIDTH 16
#define MY_NEW_APP_ICON_HEIGHT 16

// In bitmaps.cpp
const uint8_t myNewAppIcon[] PROGMEM = {
    // 16x16 bitmap data
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

// In your application's render method, use the icon:
display->drawBitmap(0, 0, myNewAppIcon, MY_NEW_APP_ICON_WIDTH, MY_NEW_APP_ICON_HEIGHT, 1);
```

## Existing Applications

### MenuApplication
The main menu that allows users to select and launch applications.

**Features:**
- Vertical list of all registered applications
- Icon display for each application
- Battery indicator in top right corner
- Navigation with UP/DOWN buttons
- Application launch with OK button
- Return to startup screen with BACK button

### SettingsApplication
A system application that allows users to configure device settings including battery display mode and button rebinding.

**Features:**
- Battery display configuration (icon vs percentage)
- Button rebinding functionality
- Navigation with UP/DOWN buttons
- Value adjustment with LEFT/RIGHT buttons
- Save settings with OK button
- Return to menu with BACK button

**Button Remapping:**
The button remapping feature allows users to reassign physical buttons to different functions. This is useful if you prefer a different button layout or if some buttons are damaged.

To rebind buttons:
1. Navigate to the "Button Rebinding" option in the settings menu
2. Press OK to enter rebinding mode
3. For each function (UP, DOWN, LEFT, RIGHT, OK, BACK, FUNCTION):
   - Press the physical button you want to assign to that function
   - The system will automatically move to the next function
4. After rebinding all buttons, the system will return to the settings menu
5. Press BACK to save the new configuration and return to the main menu

The new button configuration is saved to EEPROM and will persist after power cycling the device.

**Controls:**
- UP: Navigate up in settings list
- DOWN: Navigate down in settings list
- LEFT: Decrease selected value
- RIGHT: Increase selected value
- OK: Save settings
- BACK: Return to main menu

### ButtonTestApplication
A simple application for testing button functionality and mapping.

**Features:**
- Displays which buttons are currently pressed
- Useful for verifying button remapping functionality
- Simple interface for testing

**Controls:**
- All buttons: Display press status on screen
- BACK: Return to main menu

### DoomApplication
A simplified pseudo-3D first-person shooter inspired by the classic DOOM game.

**Features:**
- Raycasting-based rendering
- Enemy entities
- Health and ammo display
- In-game menu system
- Movement controls (UP/DOWN to move, LEFT/RIGHT to turn)

**Controls:**
- UP: Move forward
- DOWN: Move backward
- LEFT: Turn left
- RIGHT: Turn right
- OK: Interact/shoot
- BACK: Pause game
- FUNCTION: Toggle FPS display

### TamagotchiApplication
A virtual pet simulation where you can feed, play with, and clean your digital pet.

**Features:**
- Pet status monitoring (happiness, hunger, energy, cleanliness)
- Feeding, playing, and cleaning actions
- Pet state changes over time
- Visual representation of the pet

**Controls:**
- UP: (Unused)
- DOWN: (Unused)
- LEFT: Clean pet
- RIGHT: (Unused)
- OK: Feed pet
- BACK: Return to main menu
- FUNCTION: Play with pet

### ExplorerApplication
Browse files and directories on the SD card.

**Features:**
- File and directory listing
- File content viewing
- Directory navigation
- Support for text files

**Controls:**
- UP: Navigate up in list
- DOWN: Navigate down in list
- OK: Enter directory or view file
- BACK: Return to parent directory or main menu

### WifiScannerApplication
Scans for available WiFi networks and displays information about them.

**Features:**
- Real-time WiFi scanning
- Network strength indicators
- Network information display (SSID, encryption type)
- Simulated connection to networks

**Controls:**
- UP: Navigate up in list
- DOWN: Navigate down in list
- OK: View network details or simulate connection
- BACK: Return to main menu

### StopwatchApplication
A simple stopwatch with start/stop, lap time recording, and reset functionality.

**Features:**
- Start/Stop functionality
- Lap time recording
- Reset function
- Time display in MM:SS:MS format

**Controls:**
- OK: Start/Stop timer
- UP: Record lap time
- DOWN: Reset timer
- BACK: Return to main menu

### CalculatorApplication
A basic calculator supporting addition, subtraction, multiplication, and division operations.

**Features:**
- Addition, subtraction, multiplication, division
- Decimal point support
- Clear function
- Error handling (division by zero)

**Controls:**
- UP/DOWN: Navigate number pad vertically
- LEFT/RIGHT: Navigate number pad horizontally
- OK: Select/confirm
- BACK: Clear entry/return to menu

### SlotsApplication
A casino-style slot machine game where you can bet credits and spin the reels to win prizes.

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

### FlappyBirdApplication
A simplified version of the popular Flappy Bird game.

**Features:**
- Bird character that can be controlled to fly
- Obstacles to navigate through
- Score tracking
- Game over detection

**Controls:**
- OK: Make bird flap/jump
- BACK: Return to main menu

### PaintApplication
A simple drawing application that allows users to create artwork on the display.

**Features:**
- Drawing with a cursor
- Different drawing modes
- Clear screen functionality
- Save/load functionality (if implemented)

**Controls:**
- UP/DOWN/LEFT/RIGHT: Move cursor
- OK: Draw at cursor position
- FUNCTION: Change drawing mode
- BACK: Return to main menu

### WiFi Security Applications
Several applications for WiFi security research and testing:

1. **WiFiPacketCaptureApplication** - Captures and analyzes WiFi packets
2. **WiFiDeauthAttackApplication** - Performs deauthentication attacks
3. **EnhancedWifiScannerApplication** - Advanced WiFi scanning capabilities
4. **EvilPortalApplication** - Creates fake access points for testing

### Bluetooth Applications
Applications for Bluetooth research and testing:

1. **BluetoothScannerApplication** - Scans for Bluetooth devices
2. **BluetoothAttackApplication** - Performs Bluetooth-based attacks

## Developer Guide

### Project Structure
```
src/
├── main.cpp                 # System initialization and main loop
├── config.h                 # System configuration and pin definitions
├── graphics/
│   ├── bitmaps.cpp          # Bitmap and graphic assets
│   └── bitmaps.h            # Bitmap declarations
├── core/
│   ├── ApplicationManager.cpp # Application manager
│   ├── ApplicationManager.h   # Application manager declarations
│   ├── Button.cpp           # Button handling and debouncing
│   ├── Button.h             # Button class declarations
│   ├── Display.cpp          # Display driver and basic drawing functions
│   ├── Display.h            # Display class declarations
│   ├── Navigation.cpp       # Navigation system and menu handling
│   └── Navigation.h         # Navigation class declarations
├── apps/
│   ├── Application.h        # Base application interface
│   ├── StartupScreen.*      # Startup screen application
│   ├── MenuApplication.*    # Main menu application
│   ├── SettingsApplication.* # System settings application
│   ├── ButtonTestApplication.* # Button test application
│   ├── DoomApplication.*    # DOOM game application
│   ├── TamagotchiApplication.* # Virtual pet application
│   ├── ExplorerApplication.* # File explorer application
│   ├── WifiScannerApplication.* # WiFi scanner application
│   ├── StopwatchApplication.* # Stopwatch application
│   ├── CalculatorApplication.* # Calculator application
│   ├── SlotsApplication.*   # Slot machine game
│   ├── FlappyBirdApplication.* # Flappy Bird game
│   ├── PaintApplication.*   # Drawing application
│   ├── WiFiPacketCaptureApplication.* # WiFi packet capture
│   ├── WiFiDeauthAttackApplication.* # WiFi deauth attacks
│   ├── EnhancedWifiScannerApplication.* # Enhanced WiFi scanner
│   ├── EvilPortalApplication.* # Evil portal application
│   ├── BluetoothScannerApplication.* # Bluetooth scanner
│   └── BluetoothAttackApplication.* # Bluetooth attacks
└── utils/
    ├── logger.cpp           # Logging utilities
    └── logger.h             # Logging utilities declarations
```

### Button Remapping Initialization
The main.cpp file initializes the button system with default pin assignments, then reinitializes the buttons with user-defined mappings from the Settings application after all applications have been registered. This two-step initialization allows the system to support dynamic button remapping while maintaining compatibility with the existing button system.

### Configuration
The `config.h` file contains all system configuration parameters:

```cpp
// Display configuration
#define OLED_SDA_PIN 21
#define OLED_SCL_PIN 22
#define OLED_WIDTH 128
#define OLED_HEIGHT 64

// Button pin definitions
#define BUTTON_UP_PIN 12
#define BUTTON_DOWN_PIN 13
#define BUTTON_LEFT_PIN 14
#define BUTTON_RIGHT_PIN 15
#define BUTTON_OK_PIN 16
#define BUTTON_BACK_PIN 17
#define BUTTON_FUNCTION_PIN 18

// Button states
#define BUTTON_PRESSED LOW
#define BUTTON_RELEASED HIGH

// Display update rate (ms)
#define DISPLAY_UPDATE_INTERVAL 50

// Button debounce time (ms)
#define BUTTON_DEBOUNCE_TIME 50

// SD Card SPI pins
#define SD_SCK_PIN 19
#define SD_MISO_PIN 23
#define SD_MOSI_PIN 25
#define SD_CS_PIN 5
```

### Memory Management
- Applications are instantiated once and reused
- Display uses double buffering to prevent flickering
- Button debouncing prevents false triggers
- Efficient use of ESP32 resources

### Adding Dependencies
To add new libraries, modify `platformio.ini`:

```ini
[env:esp32dev]
platform = espressif32
board = esp32dev
framework = arduino
lib_deps =
    adafruit/Adafruit GFX Library@^1.11.9
    https://github.com/adafruit/Adafruit_SH110x.git
    SPI
    SD
    # Add new dependencies here
```

### Debugging
The system uses Serial output for debugging:
- Initialize with `Serial.begin(115200)` in setup
- Use `Serial.println()` for debug messages
- Check serial monitor in PlatformIO for output

### Performance Considerations
- Keep rendering code efficient
- Avoid blocking operations in update() methods
- Use millis() for timing instead of delay()
- Consider display update rate when designing animations

### Remote Control Display Feature
The remote control display feature allows users to view the device's screen content in real-time through the Python GUI controller. This is implemented through:

1. **GET_DISPLAY Serial Command** - A new serial command that requests the current display buffer from the ESP32 device
2. **Display Buffer Access** - A method in the Display class that provides access to the current display buffer
3. **Periodic Updates** - The GUI controller requests display updates at 10 FPS for smooth visualization
4. **Pixel-by-Pixel Rendering** - The GUI accurately renders the 128x64 pixel display with white pixels representing active pixels

This feature is useful for:
- Monitoring the device's screen without physically looking at it
- Debugging applications remotely
- Demonstrating device functionality to others

## User Guide

### Getting Started
1. Assemble the hardware according to the wiring diagram
2. Install PlatformIO and dependencies
3. Build and flash the firmware
4. Insert a microSD card (formatted as FAT32)
5. Power on the device

### Navigation Controls
- UP: Navigate up in menus, move forward in DOOM, feed pet in Tamagotchi
- DOWN: Navigate down in menus, move backward in DOOM, play with pet in Tamagotchi
- LEFT: Turn left in DOOM, clean pet in Tamagotchi
- RIGHT: Turn right in DOOM
- OK: Select items, confirm actions, start/stop in Stopwatch
- BACK: Return to previous screen, cancel actions, exit applications
- FUNCTION: Special function button (varies by application)

### Application Usage

#### DOOM
A simplified pseudo-3D first-person shooter game.
- UP: Move forward
- DOWN: Move backward
- LEFT: Turn left
- RIGHT: Turn right
- OK: Shoot/interact
- BACK: Pause game
- FUNCTION: Toggle FPS display

#### Slots
A casino-style slot machine game.
- UP: Increase bet amount
- DOWN: Decrease bet amount
- OK: Spin the reels
- BACK: Return to main menu

#### WiFi Scanner
Scans for available WiFi networks.
- UP/DOWN: Navigate network list
- OK: View details or simulate connection
- BACK: Return to main menu

#### Explorer
Browse files on the SD card.
- UP/DOWN: Navigate file list
- OK: Enter directory or view file
- BACK: Return to parent directory or main menu

#### Tamagotchi
Virtual pet simulation.
- UP: (Unused)
- DOWN: (Unused)
- LEFT: Clean pet
- RIGHT: (Unused)
- OK: Feed pet
- BACK: Return to main menu
- FUNCTION: Play with pet

#### Stopwatch
Simple stopwatch application.
- OK: Start/Stop timer
- UP: Record lap time
- DOWN: Reset timer
- BACK: Return to main menu

#### Calculator
Basic calculator with arithmetic operations.
- UP/DOWN: Navigate number pad vertically
- LEFT/RIGHT: Navigate number pad horizontally
- OK: Select number or operation
- BACK: Clear or return to menu

### SD Card Usage
The device supports FAT32 formatted microSD cards up to 32GB.

**Supported Operations:**
- Reading files
- Browsing directories
- Viewing text file contents

**File Recommendations:**
- Keep filenames short (8.3 format recommended)
- Use plain text files for best compatibility
- Organize files in directories for easier navigation

## Building and Flashing

### Prerequisites
1. Install PlatformIO Core or PlatformIO IDE
2. Install Git (for cloning the repository)

### Building the Firmware
1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/haklesmy.git
   cd haklesmy
   ```

2. Install dependencies:
   ```bash
   pio lib install
   ```

3. Build the firmware:
   ```bash
   pio run
   ```

### Flashing to ESP32
1. Connect the ESP32 to your computer via USB
2. Upload the firmware:
   ```bash
   pio run --target upload
   ```

### Monitoring Serial Output
To view debug output:
```bash
pio device monitor
```

## Troubleshooting

### Display Issues
- Check all wiring connections to the display
- Ensure the display is properly powered
- Verify SDA/SCL connections to GPIO21/GPIO22
- Try different I2C addresses (0x3C or 0x3D)

### SD Card Problems
- Ensure the SD card is properly inserted
- Check SD card wiring connections
- Verify the SD card is formatted as FAT32
- Try a different SD card

### Button Responsiveness
- Check button wiring connections
- Ensure buttons are properly connected to ground
- Verify pull-up resistors are used or enabled
- Test each button individually

### WiFi Scanner Not Finding Networks
- Ensure the device is in an area with WiFi networks
- Check that the WiFi antenna (if any) is properly connected
- Restart the application
- Try the Enhanced WiFi Scanner application

### Device Not Powering On
- Check USB power connection
- Verify the ESP32 board is functioning
- Check for short circuits in wiring
- Try a different power source

### Firmware Issues
- Re-flash the firmware using PlatformIO
- Check for compilation errors
- Verify all dependencies are installed
- Clear the build cache: `pio run --target clean`

### Application-Specific Issues
- DOOM: If the game is running slowly, reduce the complexity of the 3D rendering
- Tamagotchi: If pet stats aren't updating, check the update() method timing
- Explorer: If files aren't showing, verify SD card formatting and contents
- WiFi Scanner: If networks aren't detected, ensure WiFi functionality is enabled

## Contributing

We welcome contributions to the HAKLESMY project! Here's how you can help:

### Reporting Issues
- Check if the issue already exists in the issue tracker
- Provide detailed information about the problem
- Include steps to reproduce the issue
- Mention your hardware setup and firmware version

### Adding New Features
- Fork the repository
- Create a new branch for your feature
- Follow the existing code style and architecture
- Add documentation for new features
- Submit a pull request with a clear description

### Code Style Guidelines
- Use consistent indentation (4 spaces)
- Follow existing naming conventions
- Add comments for complex logic
- Keep functions focused and small
- Use meaningful variable names

### Testing
- Test your changes on actual hardware
- Verify that existing functionality still works
- Add new test cases for added features
- Document any changes to the user interface

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- Inspired by the Flipper Zero device
- Uses Adafruit GFX and SH1106 libraries
- DOOM rendering techniques based on classic raycasting algorithms
- Community contributions and feedback