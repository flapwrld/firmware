# Serial Command Protocol

This document describes the serial command protocol used to control the ESP32 device remotely.

## Overview

The ESP32 device accepts text-based commands through its serial interface. Each command should be sent as a single line of text followed by a newline character (`\n`).

## Supported Commands

| Command | Description | Navigation Event |
|---------|-------------|------------------|
| `UP` | Navigate up | NAVIGATION_UP |
| `DOWN` | Navigate down | NAVIGATION_DOWN |
| `LEFT` | Navigate left | NAVIGATION_LEFT |
| `RIGHT` | Navigate right | NAVIGATION_RIGHT |
| `OK` | Select/Confirm | NAVIGATION_OK |
| `BACK` | Go back/Cancel | NAVIGATION_BACK |
| `FUNCTION` | Function key | NAVIGATION_FUNCTION |
| `BACK_LONG` | Long press back | NAVIGATION_BACK_LONG |
| `GET_DISPLAY` | Request display data | NAVIGATION_GET_DISPLAY |

## Command Format

Commands are case-sensitive and should be sent exactly as shown in the table above. Each command must be terminated with a newline character.

Example:
```
UP\n
DOWN\n
OK\n
```

## Response Format

The device will respond to each command with an acknowledgment message:
- `OK` - Command was processed successfully
- `ERROR` - Command was not recognized

For the `GET_DISPLAY` command, the device will respond with 1024 bytes of binary display data.

## Implementation Details

The serial command parser is implemented in `src/core/SerialCommandParser.h` and `src/core/SerialCommandParser.cpp`. It converts text commands to `NavigationEvent` values that are then processed by the navigation system.

The `Navigation` class in `src/core/Navigation.h` and `src/core/Navigation.cpp` has been modified to accept external events with priority over button events.

The `ApplicationManager` in `src/core/ApplicationManager.h` and `src/core/ApplicationManager.cpp` processes serial commands in its main loop.

## Python Controller

A Python GUI controller is provided in `esp_controller_gui.py` that sends these commands to the device through a serial connection. The controller provides a graphical interface with buttons for each command and supports keyboard shortcuts.

## Testing

Unit tests for the serial command parser are available in `test_serial_command_parser.py`. Integration tests for the navigation system and application manager are available in `test_navigation.py` and `test_application_manager.py` respectively.