# Building Executables

This document explains how to build standalone executables for the ESP32 GUI controller for different platforms.

## Overview

The ESP32 GUI controller can be distributed as a standalone executable for Windows, Linux, and macOS. This eliminates the need for users to install Python and dependencies separately.

## Prerequisites

Before building executables, ensure you have:

1. Python 3.6 or higher installed
2. All required dependencies installed:
   ```bash
   pip install -r requirements.txt
   pip install -r requirements-dev.txt
   ```

## Windows Executables (.exe)

### Using PyInstaller (Recommended)

1. Install PyInstaller:
   ```bash
   pip install pyinstaller
   ```

2. Build the executable:
   ```bash
   pyinstaller --onefile --windowed esp_controller_gui.py
   ```

   Options:
   - `--onefile`: Creates a single executable file
   - `--windowed`: Prevents console window from appearing (Windows only)

3. The executable will be created in the `dist` directory.

### Using cx_Freeze

1. Install cx_Freeze:
   ```bash
   pip install cx_Freeze
   ```

2. Build the executable:
   ```bash
   cxfreeze esp_controller_gui.py --target-dir dist
   ```

3. The executable and dependencies will be created in the `dist` directory.

### Using the Batch Script

Run the provided batch script:
```bash
build_executable.bat
```

This will build using both PyInstaller and cx_Freeze.

## Linux Executables

### Using PyInstaller

1. Install PyInstaller:
   ```bash
   pip install pyinstaller
   ```

2. Build the executable:
   ```bash
   pyinstaller --onefile esp_controller_gui.py
   ```

3. The executable will be created in the `dist` directory.

### Using cx_Freeze

1. Install cx_Freeze:
   ```bash
   pip install cx_Freeze
   ```

2. Build the executable:
   ```bash
   cxfreeze esp_controller_gui.py --target-dir dist
   ```

3. The executable and dependencies will be created in the `dist` directory.

### Using Make

If you have `make` installed:
```bash
make
```

This will build using both PyInstaller and cx_Freeze.

### Using the Shell Script

Run the provided shell script:
```bash
chmod +x build_executable.sh
./build_executable.sh
```

This will build using both PyInstaller and cx_Freeze.

## macOS Executables

### Using PyInstaller

1. Install PyInstaller:
   ```bash
   pip install pyinstaller
   ```

2. Build the executable:
   ```bash
   pyinstaller --onefile esp_controller_gui.py
   ```

3. The executable will be created in the `dist` directory.

### Using cx_Freeze

1. Install cx_Freeze:
   ```bash
   pip install cx_Freeze
   ```

2. Build the executable:
   ```bash
   cxfreeze esp_controller_gui.py --target-dir dist
   ```

3. The executable and dependencies will be created in the `dist` directory.

### Using Make

If you have `make` installed:
```bash
make
```

This will build using both PyInstaller and cx_Freeze.

### Using the Shell Script

Run the provided shell script:
```bash
chmod +x build_executable.sh
./build_executable.sh
```

This will build using both PyInstaller and cx_Freeze.

## Android APK

To create an Android APK, you'll need to convert the application to use Kivy:

1. Install Kivy and Buildozer:
   ```bash
   pip install kivy buildozer
   ```

2. Convert the GUI to use Kivy widgets instead of tkinter

3. Create a `main.py` file with Kivy-compatible code

4. Initialize Buildozer:
   ```bash
   buildozer init
   ```

5. Modify the `buildozer.spec` file with your app details

6. Build the APK:
   ```bash
   buildozer android debug
   ```

Note: This requires significant changes to the GUI code as tkinter is not available on Android.

## Customization

### PyInstaller Options

You can customize the PyInstaller build with additional options:

- `--name NAME`: Specify the name of the executable
- `--icon ICON`: Add an icon to the executable
- `--add-data SRC;DEST`: Include additional data files
- `--hidden-import MODULE`: Include hidden imports

Example with custom options:
```bash
pyinstaller --onefile --windowed --name "ESP32 Controller" --icon icon.ico esp_controller_gui.py
```

### cx_Freeze Options

You can customize the cx_Freeze build by modifying `setup.py`:

- `executables`: List of executables to build
- `build_exe`: Build options
- `bdist_msi`: Windows installer options

## Troubleshooting

### Common Issues

1. **Missing modules**:
   - Add missing modules with `--hidden-import` for PyInstaller
   - Add missing modules to `setup.py` for cx_Freeze

2. **Large executable size**:
   - Use `--exclude-module` to exclude unnecessary modules
   - Consider using UPX to compress the executable

3. **Antivirus false positives**:
   - This is common with PyInstaller executables
   - Consider using cx_Freeze as an alternative
   - Add digital signatures to executables

### Testing Executables

Always test your executables on a clean system without Python installed to ensure all dependencies are included.

## Distribution

When distributing your executables:

1. Include any necessary runtime libraries
2. Provide clear installation instructions
3. Test on multiple systems
4. Consider creating installers for easier deployment

For Windows, you can create an MSI installer using cx_Freeze's `bdist_msi` command or third-party tools like Inno Setup.

For Linux, consider creating packages for popular distributions (deb for Ubuntu/Debian, rpm for Fedora/CentOS).

For macOS, you can create a DMG image containing your application.