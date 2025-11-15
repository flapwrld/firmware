# ESP32 Setup Guide for Linux

This guide will help you set up your ESP32 DevKit board on a Linux system for use with PlatformIO.

## 1. Install Necessary Packages

First, install the required packages for USB serial communication:

```bash
sudo apt update
sudo apt install python3-serial minicom
```

For some Linux distributions, you might also need:

```bash
sudo apt install python3-pip
pip3 install pyserial
```

## 2. Set Up Udev Rules

The ESP32 needs proper udev rules to be accessible by PlatformIO. Create a new udev rules file:

```bash
sudo nano /etc/udev/rules.d/99-platformio-udev.rules
```

Add the following content to the file:

```
# ESP32
SUBSYSTEMS=="usb", ATTRS{idVendor}=="10c4", ATTRS{idProduct}=="ea60", MODE:="0666", ENV{ID_MM_DEVICE_IGNORE}="1"
SUBSYSTEMS=="usb", ATTRS{idVendor}=="1a86", ATTRS{idProduct}=="55d4", MODE:="0666", ENV{ID_MM_DEVICE_IGNORE}="1"
SUBSYSTEMS=="usb", ATTRS{idVendor}=="10c4", ATTRS{idProduct}=="ea70", MODE:="0666", ENV{ID_MM_DEVICE_IGNORE}="1"
SUBSYSTEMS=="usb", ATTRS{idVendor}=="1a86", ATTRS{idProduct}=="7523", MODE:="0666", ENV{ID_MM_DEVICE_IGNORE}="1"
```

Save and exit the file (Ctrl+O, Enter, Ctrl+X for nano).

## 3. Add User to Dialout Group

Add your user to the dialout group to allow access to serial ports:

```bash
sudo usermod -a -G dialout $USER
```

## 4. Reload Udev Rules

Reload the udev rules without rebooting:

```bash
sudo udevadm control --reload-rules
sudo udevadm trigger
```

## 5. Reboot Your System

Reboot your system to ensure all changes take effect:

```bash
sudo reboot
```

## 6. Verify Device Recognition

After rebooting, connect your ESP32 and verify it's recognized:

```bash
ls /dev/ttyUSB*
```

You should see something like `/dev/ttyUSB0` or similar.

You can also check with:

```bash
lsusb
```

Look for an entry related to your ESP32 board.

## 7. Update platformio.ini

Once you've confirmed the device is recognized, update your `platformio.ini` file to specify the correct upload port:

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
    https://github.com/LSatan/SmartRC-CC1101-Driver-Lib.git
    z3t0/IRremote@^4.4.1
monitor_speed = 115200
upload_port = /dev/ttyUSB0
```

Replace `/dev/ttyUSB0` with the actual port your ESP32 is connected to.

## 8. Test the Connection

Try uploading your firmware again:

```bash
platformio run --target upload
```

If everything is set up correctly, the upload should succeed.