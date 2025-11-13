# Flipper Zero-like Device Connection Diagram

## Overview
This document provides the complete connection diagram for the Flipper Zero-like device based on ESP32 with SH1106 OLED display.

## Component List
1. ESP32 Development Board
2. SH1106 OLED Display (128x64)
3. 7 Push Buttons (Up, Down, Left, Right, OK, Back, Function)
4. MicroSD Card Module
5. CC1101 Transceiver Module
6. Resistors (10kΩ for pull-up resistors)

## Pin Connections

### Display Connections (SH1106 OLED)
| Display Pin | ESP32 Pin | Function     |
|-------------|-----------|--------------|
| GND         | GND       | Ground       |
| VCC         | 3.3V      | Power        |
| SDA         | GPIO 21   | Data Line    |
| SCL         | GPIO 22   | Clock Line   |

### Button Connections
All buttons use internal pull-up resistors, so they connect to GND when pressed.

| Button | ESP32 Pin | Function     |
|--------|-----------|--------------|
| UP     | GPIO 12   | Up Navigation|
| DOWN   | GPIO 13   | Down Navigation|
| LEFT   | GPIO 14   | Left Navigation|
| RIGHT  | GPIO 15   | Right Navigation|
| OK     | GPIO 16   | Select/OK    |
| BACK   | GPIO 17   | Back/Cancel  |
| FUNCTION| GPIO 18  | Function Key |

### SD Card Module Connections
| SD Card Pin | ESP32 Pin | Function     |
|-------------|-----------|--------------|
| GND         | GND       | Ground       |
| VCC         | 3.3V      | Power        |
| MISO        | GPIO 23   | Master In Slave Out |
| MOSI        | GPIO 18   | Master Out Slave In |
| SCK         | GPIO 19   | Clock        |
| CS          | GPIO 5    | Chip Select  |

### CC1101 Module Connections
| CC1101 Pin | ESP32 Pin | Function     |
|------------|-----------|--------------|
| GND        | GND       | Ground       |
| VCC        | 3.3V      | Power        |
| SCK        | GPIO 18   | Clock        |
| MISO       | GPIO 19   | Master In Slave Out |
| MOSI       | GPIO 23   | Master Out Slave In |
| CS         | GPIO 27   | Chip Select  |
| GDO0       | GPIO 26   | Data Out     |

## Circuit Diagram (Text-based)

```
                    ESP32 DEV BOARD
    ┌─────────────────────────────────────────────┐
    │                                             │
    │  3.3V ──────────────────────────────────┐   │
    │                                         │   │
    │  GND  ───┬──┬──┬──┬──┬──┬──┬──────────┬─┼───┤
    │          │  │  │  │  │  │  │          │ │   │
    │ GPIO 21 ─┼──┼──┼──┼──┼──┼──┼──────────┼─┼───┤
    │ GPIO 22 ─┼──┼──┼──┼──┼──┼──┼──────────┼─┼───┤
    │ GPIO 12 ─┼──┼──┼──┼──┼──┼──┼──────────┼─┼───┤
    │ GPIO 13 ─┼──┼──┼──┼──┼──┼──┼──────────┼─┼───┤
    │ GPIO 14 ─┼──┼──┼──┼──┼──┼──┼──────────┼─┼───┤
    │ GPIO 15 ─┼──┼──┼──┼──┼──┼──┼──────────┼─┼───┤
    │ GPIO 16 ─┼──┼──┼──┼──┼──┼──┼──────────┼─┼───┤
    │ GPIO 17 ─┼──┼──┼──┼──┼──┼──┼──────────┼─┼───┤
    │ GPIO 18 ─┼──┼──┼──┼──┼──┼──┼──┬───────┼─┼───┤
    │ GPIO 19 ─┼──┼──┼──┼──┼──┼──┼──┼───────┼─┼───┤
    │ GPIO 23 ─┼──┼──┼──┼──┼──┼──┼──┼───────┼─┼───┤
    │ GPIO 5  ─┼──┼──┼──┼──┼──┼──┼──┼───────┼─┼───┤
    │          │  │  │  │  │  │  │  │       │ │   │
    └──────────┼──┼──┼──┼──┼──┼──┼──┼───────┼─┼───┘
               │  │  │  │  │  │  │  │       │ │
    ┌──────────┼──┼──┼──┼──┼──┼──┼──┼───────┼─┼───┐
    │  OLED    │  │  │  │  │  │  │  │       │ │   │
    │  Display │  │  │  │  │  │  │  │       │ │   │
    │  GND ────┴──┼──┼──┼──┼──┼──┼──┼───────┼─┼───┤
    │  VCC ───────┴──┼──┼──┼──┼──┼──┼───────┼─┼───┤
    │  SDA ──────────┴──┼──┼──┼──┼──┼───────┼─┼───┤
    │  SCL ─────────────┴──┼──┼──┼──┼───────┼─┼───┤
    └──────────────────────┴──┼──┼──┼───────┼─┼───┘
                              │  │  │       │ │
    ┌─────────────────────────┼──┼──┼───────┼─┼───┐
    │  Buttons                │  │  │       │ │   │
    │  UP    ─────────────────┴──┼──┼───────┼─┼───┤
    │  DOWN  ────────────────────┴──┼───────┼─┼───┤
    │  LEFT  ───────────────────────┴───────┼─┼───┤
    │  RIGHT ────────────────────────────────┴─┼───┤
    │  OK    ──────────────────────────────────┼───┤
    │  BACK  ──────────────────────────────────┼───┤
    │  FUNC  ──────────────────────────────────┼───┤
    └──────────────────────────────────────────┴───┘
                              │  │  │       │ │
    ┌─────────────────────────┼──┼──┼───────┼─┼───┐
    │  SD Card                │  │  │       │ │   │
    │  GND ───────────────────┴──┼──┼───────┼─┼───┤
    │  VCC ──────────────────────┴──┼───────┼─┼───┤
    │  MISO ────────────────────────┴───────┼─┼───┤
    │  MOSI ────────────────────────────────┴─┼───┤
    │  SCK  ──────────────────────────────────┼───┤
    │  CS   ──────────────────────────────────┼───┤
    └──────────────────────────────────────────┴───┘
                              │  │  │       │ │
    ┌─────────────────────────┼──┼──┼───────┼─┼───┐
    │  CC1101                 │  │  │       │ │   │
    │  GND ───────────────────┴──┼──┼───────┼─┼───┤
    │  VCC ──────────────────────┴──┼───────┼─┼───┤
    │  SCK ────────────────────────┼───────┼─┼───┤
    │  MISO ───────────────────────┼───────┼─┼───┤
    │  MOSI ───────────────────────┼───────┼─┼───┤
    │  CS   ───────────────────────┼───────┼─┼───┤
    │  GDO0 ───────────────────────┼───────┼─┼───┤
    └──────────────────────────────┴───────┴─┴───┘
```

## Notes
1. All buttons should be connected with one side to the ESP32 GPIO pin and the other side to GND
2. The internal pull-up resistors of the ESP32 are used, so no external resistors are needed for buttons
3. The SD card module should be a 3.3V compatible module
4. The SH1106 OLED display should be a 3.3V compatible module
5. The CC1101 module should be a 3.3V compatible module
6. Make sure to use a stable 3.3V power supply for all components

## Assembly Instructions
1. Connect the OLED display to ESP32 using the SDA/SCL pins
2. Connect each button between its respective GPIO pin and GND
3. Connect the SD card module to the ESP32 using SPI pins
4. Connect the CC1101 module to the ESP32 using SPI pins
5. Upload the firmware to the ESP32
6. Power on the device and test all functions