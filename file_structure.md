# File Structure and Organization

## Root Directory Structure
```
src/
├── main.cpp                 # System initialization and main loop
├── config.h                 # System configuration and pin definitions
├── graphics/
│   ├── display.cpp          # Display driver and basic drawing functions
│   ├── display.h            # Display class declarations
│   ├── bitmaps.cpp          # Bitmap and graphic assets
│   └── bitmaps.h            # Bitmap declarations
├── core/
│   ├── button.cpp           # Button handling and debouncing
│   ├── button.h             # Button class declarations
│   ├── navigation.cpp       # Navigation system and menu handling
│   └── navigation.h         # Navigation class declarations
├── apps/
│   ├── app_interface.h      # Base application interface
│   ├── app_manager.cpp      # Application manager
│   ├── app_manager.h        # Application manager declarations
│   ├── file_explorer/
│   │   ├── file_explorer.cpp # File explorer application implementation
│   │   └── file_explorer.h   # File explorer class declarations
│   └── wifi_scanner/
│       ├── wifi_scanner.cpp  # WiFi scanner application implementation
│       └── wifi_scanner.h    # WiFi scanner class declarations
└── utils/
    ├── logger.cpp           # Logging utilities
    └── logger.h             # Logging utilities declarations
```

## Detailed File Descriptions

### Main System Files
- `main.cpp`: Entry point of the firmware, initializes all subsystems and runs the main loop
- `config.h`: System-wide configuration including pin definitions, display settings, and hardware parameters

### Graphics Module
- `display.cpp/h`: Handles communication with the SH1106 OLED display, provides drawing primitives
- `bitmaps.cpp/h`: Stores all bitmap data and graphic assets used in the UI

### Core System Modules
- `button.cpp/h`: Implements button handling with debouncing, long press, and multi-button detection
- `navigation.cpp/h`: Implements the navigation system, menu handling, and application switching

### Application Framework
- `app_interface.h`: Defines the base interface that all applications must implement
- `app_manager.cpp/h`: Manages application registration, switching, and lifecycle
- `file_explorer/`: Directory containing the file explorer application
- `wifi_scanner/`: Directory containing the WiFi scanner application

### Utility Modules
- `logger.cpp/h`: Provides logging capabilities for debugging and monitoring