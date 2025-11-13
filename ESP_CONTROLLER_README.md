# ESP32 Controller

This directory contains a Python-based controller for remotely operating the ESP32 device through its serial interface.

## Overview

The controller provides both a command-line interface (`test_serial_commands.py`) and a graphical user interface (`esp_controller_gui.py`) for sending navigation commands to the ESP32 device.

## Features

- Graphical user interface with buttons for all supported commands
- Keyboard shortcuts for quick command entry
- Automatic serial port detection
- Cross-platform support (Windows, Linux, macOS)
- Standalone executable creation for easy distribution
- Comprehensive test suite

## Requirements

- Python 3.6 or higher
- pyserial library
- tkinter (usually included with Python)

## Installation

1. Install Python 3.6 or higher from [python.org](https://www.python.org/)
2. Install the required dependencies:
   ```bash
   pip install -r requirements.txt
   ```

## Usage

### Graphical Interface

Run the graphical controller:
```bash
python esp_controller_gui.py
```

Or use the platform-specific scripts:
- Windows: `run_controller.bat`
- Linux/macOS: `run_controller.sh`

The GUI provides:
- Cross-shaped directional pad (UP, DOWN, LEFT, RIGHT)
- Central OK button
- FUNCTION and BACK buttons
- BACK LONG button for long press simulation
- Serial port selection with automatic detection
- Connection status indicator

Keyboard shortcuts:
- Arrow keys: UP, DOWN, LEFT, RIGHT
- Enter: OK
- Escape: BACK
- F1: FUNCTION

### Command Line Interface

Run the command-line controller:
```bash
python test_serial_commands.py
```

Follow the prompts to select a serial port and enter commands.

## Building Executables

Standalone executables can be built for easy distribution:

### Windows (.exe)

Using PyInstaller:
```bash
pyinstaller --onefile --windowed esp_controller_gui.py
```

Using cx_Freeze:
```bash
cxfreeze esp_controller_gui.py --target-dir dist
```

### Linux

Using PyInstaller:
```bash
pyinstaller --onefile esp_controller_gui.py
```

Using cx_Freeze:
```bash
cxfreeze esp_controller_gui.py --target-dir dist
```

### Android

Convert to Android APK using Kivy and Buildozer (requires additional setup).

## Testing

Run the test suite:
```bash
python -m pytest
```

Specific test files:
- `test_serial_command_parser.py`: Unit tests for the serial command parser
- `test_navigation.py`: Unit tests for the navigation system
- `test_application_manager.py`: Unit tests for the application manager
- `test_gui_controller.py`: Tests for the GUI controller with mock serial device

## Files

- `esp_controller_gui.py`: Main graphical interface
- `test_serial_commands.py`: Command-line interface
- `requirements.txt`: Python dependencies
- `requirements-dev.txt`: Development dependencies
- `requirements-test.txt`: Test dependencies
- `run_controller.bat`: Windows script to run the controller
- `run_controller.sh`: Linux/macOS script to run the controller
- `build_executable.bat`: Windows script to build executables
- `build_executable.sh`: Linux/macOS script to build executables
- `setup.py`: Setup file for cx_Freeze
- `esp_controller_gui.spec`: PyInstaller spec file
- `Makefile`: Makefile for Linux/macOS builds
- `icon_placeholder.txt`: Icon creation instructions
- `test_serial_command_parser.py`: Unit tests for serial command parser
- `test_navigation.py`: Unit tests for navigation system
- `test_application_manager.py`: Unit tests for application manager
- `test_gui_controller.py`: Tests for GUI controller
- `conftest.py`: pytest configuration