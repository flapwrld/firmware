# ESP32 Upload Fix

This document explains how to fix the ESP32 upload issue on Linux systems.

## Problem

When trying to upload firmware to an ESP32 device, you may encounter an error like:

```
A fatal error occurred: Could not open /dev/ttyS0, the port is busy or doesn't exist.
(Could not configure port: (5, 'Input/output error'))
```

This error occurs because the system is either:
1. Not recognizing the ESP32 device properly
2. Not having the correct permissions to access the serial port
3. Not having the correct udev rules set up

## Solution

Follow the instructions in [ESP32_LINUX_SETUP.md](ESP32_LINUX_SETUP.md) to properly set up your ESP32 device on Linux.

## Quick Fix

If you've already followed the setup guide and are still having issues:

1. Check that your ESP32 is properly connected to your computer
2. Verify the correct port in `platformio.ini`:
   ```ini
   upload_port = /dev/ttyUSB0
   ```
   (Replace with your actual port)

3. Ensure you're in the dialout group:
   ```bash
   groups
   ```
   If "dialout" is not listed, add yourself to it:
   ```bash
   sudo usermod -a -G dialout $USER
   ```

4. Reboot your system to apply all changes

## Verification

After following the setup guide, you should be able to upload to your ESP32 without errors.