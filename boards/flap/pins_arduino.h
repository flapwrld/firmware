#ifndef SCK
#define SCK PIN_CC1101_SCK
#endif
#ifndef MISO
#define MISO PIN_CC1101_MISO
#endif
#ifndef MOSI
#define MOSI PIN_CC1101_MOSI
#endif
#ifndef SDA
#define SDA PIN_DISPLAY_SDA
#endif
#ifndef SCL
#define SCL PIN_DISPLAY_SCL
#endif
#ifndef BAD_RX
#define BAD_RX PIN_GPIO_B
#endif
#ifndef BAD_TX
#define BAD_TX PIN_GPIO_C
#endif
#ifndef BTN_ALIAS
#define BTN_ALIAS "OK"
#endif
#ifndef SMOOTH_FONT
#define SMOOTH_FONT 1
#endif
#ifndef SAFE_STACK_BUFFER_SIZE
#define SAFE_STACK_BUFFER_SIZE 1024
#endif
#pragma once

// FLAP pinout
#define PIN_DISPLAY_SCL 22
#define PIN_DISPLAY_SDA 21
#define PIN_BTN_UP 27
#define PIN_BTN_DOWN 26
#define PIN_BTN_OK 33
#define PIN_BTN_BACK 32
#define PIN_CC1101_GDO0 34
#define PIN_CC1101_MISO 19
#define PIN_CC1101_MOSI 23
#define PIN_CC1101_SCK 18
#define PIN_CC1101_CS 5
#define PIN_IR_TX 4
#define PIN_IR_RX 14
#define PIN_GPIO_A 35
#define PIN_GPIO_B 25
#define PIN_GPIO_C 17
#define PIN_GPIO_D 16
#define PIN_GPIO_E 13
#define PIN_GPIO_F 12
#define PIN_GPIO_G 4
#define PIN_SD_MOSI 15
#define PIN_SD_CLK 2
#define PIN_SD_MISO 0
#define PIN_SD_CS 3

// Board-specific defines for compatibility
#define SS PIN_SD_CS
#define ROTATION 1
#define LED PIN_IR_TX
#define GROVE_SCL PIN_DISPLAY_SCL
#define GROVE_SDA PIN_DISPLAY_SDA

// Display/font metrics (примерные значения, скорректируйте при необходимости)
#define LW 8  // ширина символа
#define LH 16 // высота строки

// Версия прошивки
#ifndef BRUCE_VERSION
#define BRUCE_VERSION "flap-1.0"
#endif

// Дополнительные макросы для совместимости
#ifndef GIT_COMMIT_HASH
#define GIT_COMMIT_HASH "unknown"
#endif
#ifndef DEVICE_NAME
#define DEVICE_NAME "FLAP"
#endif
#ifndef EEPROMSIZE
#define EEPROMSIZE 4096
#endif
#ifndef SPI_SCK_PIN
#define SPI_SCK_PIN PIN_SD_CLK
#endif
#ifndef SPI_MOSI_PIN
#define SPI_MOSI_PIN PIN_SD_MOSI
#endif
#ifndef SPI_MISO_PIN
#define SPI_MISO_PIN PIN_SD_MISO
#endif
#ifndef SPI_SS_PIN
#define SPI_SS_PIN PIN_SD_CS
#endif
