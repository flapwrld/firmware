#ifndef CONFIG_H
#define CONFIG_H

// Display configuration
#define OLED_SDA_PIN 21
#define OLED_SCL_PIN 22
#define OLED_WIDTH 128
#define OLED_HEIGHT 64

// Button pin definitions
#define BUTTON_UP_PIN 12
#define BUTTON_DOWN_PIN 13
#define BUTTON_LEFT_PIN 14
#define BUTTON_RIGHT_PIN 15
#define BUTTON_OK_PIN 16
#define BUTTON_BACK_PIN 17
#define BUTTON_FUNCTION_PIN 18

// Button states
#define BUTTON_PRESSED LOW
#define BUTTON_RELEASED HIGH

// Display update rate (ms)
#define DISPLAY_UPDATE_INTERVAL 50

// Button debounce time (ms)
#define BUTTON_DEBOUNCE_TIME 50

// SD Card SPI pins
#define SD_SCK_PIN 19
#define SD_MISO_PIN 23
#define SD_MOSI_PIN 25  // Changed from pin 18 to avoid conflict with BUTTON_FUNCTION_PIN
#define SD_CS_PIN 5

// IR Sensor pins
#define IR_RECEIVE_PIN 4
#define IR_SEND_PIN 2

#endif // CONFIG_H