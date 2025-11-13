# ESP32 GUI Controller

This document provides specific information about the graphical user interface controller for the ESP32 device.

## Overview

The GUI controller (`esp_controller_gui.py`) provides a user-friendly interface for sending navigation commands to the ESP32 device through its serial interface. It features a graphical layout that mimics a physical remote control with directional buttons and function keys.

## Interface Layout

The GUI consists of:

1. **Directional Pad (D-Pad)**:
   - Cross-shaped arrangement of UP, DOWN, LEFT, RIGHT buttons
   - Central OK button

2. **Function Buttons**:
   - FUNCTION button
   - BACK button
   - BACK LONG button (simulates a long press)

3. **Serial Connection Controls**:
   - Serial port selection dropdown with automatic detection
   - Connect/Disconnect button
   - Connection status indicator (red/green circle)

4. **Device Display Visualization**:
   - 128x64 pixel display showing real-time screen content from the ESP32 device
   - Updates at 10 FPS for smooth visualization
   - White pixels represent active pixels on the device screen

## Usage

### Starting the Controller

Run the controller using one of these methods:

1. Direct Python execution:
   ```bash
   python esp_controller_gui.py
   ```

2. Platform-specific scripts:
   - Windows: Double-click `run_controller.bat` or run from command prompt
   - Linux/macOS: Execute `./run_controller.sh` (may need to make executable first with `chmod +x run_controller.sh`)

### Connecting to the Device

1. Ensure your ESP32 device is connected to your computer via USB
2. Select the appropriate serial port from the dropdown (automatically populated)
3. Click the "Connect" button
4. The status indicator will turn green when connected successfully

### Sending Commands

Use either of these methods to send commands:

1. **Mouse/Touch**:
   - Click the buttons in the GUI to send corresponding commands

2. **Keyboard Shortcuts**:
   - Arrow keys: UP, DOWN, LEFT, RIGHT
   - Enter: OK
   - Escape: BACK
   - F1: FUNCTION

### Disconnecting

Click the "Disconnect" button to close the serial connection.

## Customization

The GUI can be customized by modifying the following parameters in `esp_controller_gui.py`:

- Button sizes and colors
- Window dimensions
- Serial port settings (baud rate, timeout)
- Keyboard shortcuts

## Error Handling

The controller handles various error conditions:

- **Port not found**: Displays an error message if the selected port is not available
- **Connection failed**: Shows an error if connection to the port fails
- **Device not responding**: Displays a warning if the device doesn't respond to commands
- **Invalid command**: Shows an error if the device returns an error for a command

## Troubleshooting

### Common Issues

1. **Port not detected**:
   - Ensure the device is properly connected
   - Check if the device drivers are installed
   - Try refreshing the port list

2. **Connection fails**:
   - Verify the correct port is selected
   - Check if another application is using the port
   - Ensure the device firmware supports serial commands

3. **Commands not working**:
   - Verify the device is responding to serial commands
   - Check the baud rate setting (default: 115200)

### Logs

The controller outputs logs to the console that can help diagnose issues:
- Connection status changes
- Command sending/receiving
- Error conditions

## Development

### Dependencies

The GUI requires these Python packages:
- tkinter (usually included with Python)
- pyserial

Install with:
```bash
pip install -r requirements.txt
```

### Code Structure

The main components are:
- `ESPControllerGUI`: Main application class
- `SerialConnection`: Handles serial communication
- `ButtonFrame`: Manages the button layout
- `ConnectionFrame`: Manages connection controls

### Testing

Run the GUI tests with:
```bash
python test_gui_controller.py
```

This includes tests with a mock serial device to verify functionality without hardware.

## Building Executables

Create standalone executables for distribution:

### Windows

Using PyInstaller:
```bash
pyinstaller --onefile --windowed esp_controller_gui.py
```

Using cx_Freeze:
```bash
cxfreeze esp_controller_gui.py --target-dir dist
```

### Linux/macOS

Using PyInstaller:
```bash
pyinstaller --onefile esp_controller_gui.py
```

Using cx_Freeze:
```bash
cxfreeze esp_controller_gui.py --target-dir dist
```

The executables will be created in the `dist` directory.