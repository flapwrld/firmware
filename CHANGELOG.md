# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added
- Device display visualization in the Python GUI controller showing real-time screen content (128x64 pixels)
- GET_DISPLAY serial command to retrieve display data from the ESP32 device
- Display buffer access method in the Display class
- Periodic display update thread in the GUI controller (10 FPS)

### Changed
- Enhanced ESP_CONTROLLER_GUI_README.md with display feature documentation
- Updated USER_MANUAL.md to include information about the display visualization
- Modified README.md to mention the display feature in the ESP Controller Application section
- Extended test_gui_controller.py to test the display functionality

## [1.0.0] - 2025-11-13

### Added
- Initial release of the HAKLESMY Flipper Zero-like device
- ESP32 firmware with multiple applications (DOOM, WiFi Scanner, File Explorer, Tamagotchi, Stopwatch, Calculator)
- Python GUI controller for remote device control
- Serial command interface for remote control
- Comprehensive documentation and testing suite