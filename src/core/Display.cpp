#include "Display.h"
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH110X.h>
#include "config.h"

// Create an instance of the SH1106 display
// For I2C connection, we need to provide the reset pin
Adafruit_SH1106G display_inst(128, 64, &Wire, -1);  // 128x64 display, I2C, no reset pin

Display::Display() {
    // Constructor
}

void Display::initialize() {
    // Initialize I2C communication and display
    Wire.begin(OLED_SDA_PIN, OLED_SCL_PIN);
    
    // Initialize the SH1106 display
    display_inst.begin(0x3C, true);  // I2C address 0x3C, reset true
    
    // Clear the display
    display_inst.clearDisplay();
    display_inst.display();
}

void Display::clear() {
    // Clear the display buffer
    display_inst.clearDisplay();
}

void Display::update() {
    // Send the buffer to the display
    display_inst.display();
}

void Display::drawPixel(int16_t x, int16_t y, uint16_t color) {
    // Draw a pixel
    display_inst.drawPixel(x, y, color ? SH110X_WHITE : SH110X_BLACK);
}

void Display::drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color) {
    // Draw a line
    display_inst.drawLine(x0, y0, x1, y1, color ? SH110X_WHITE : SH110X_BLACK);
}

void Display::drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
    // Draw a rectangle
    display_inst.drawRect(x, y, w, h, color ? SH110X_WHITE : SH110X_BLACK);
}

void Display::fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
    // Fill a rectangle
    display_inst.fillRect(x, y, w, h, color ? SH110X_WHITE : SH110X_BLACK);
}

void Display::drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) {
    // Draw a circle
    display_inst.drawCircle(x0, y0, r, color ? SH110X_WHITE : SH110X_BLACK);
}

void Display::fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) {
    // Fill a circle
    display_inst.fillCircle(x0, y0, r, color ? SH110X_WHITE : SH110X_BLACK);
}

void Display::drawString(int16_t x, int16_t y, const char* text) {
    // Set text color and size
    display_inst.setTextColor(SH110X_WHITE);
    display_inst.setTextSize(1);
    
    // Set cursor position
    display_inst.setCursor(x, y);
    
    // Print the text
    display_inst.print(text);
}

void Display::drawString(int16_t x, int16_t y, String text) {
    // Set text color and size
    display_inst.setTextColor(SH110X_WHITE);
    display_inst.setTextSize(1);
    
    // Set cursor position
    display_inst.setCursor(x, y);
    
    // Print the text
    display_inst.print(text);
}

// Additional function to draw bitmaps
void Display::drawBitmap(int16_t x, int16_t y, const uint8_t bitmap[], int16_t w, int16_t h, uint16_t color) {
    // Draw a bitmap
    display_inst.drawBitmap(x, y, bitmap, w, h, color ? SH110X_WHITE : SH110X_BLACK);
}

// Set text color and background
void Display::setTextColor(uint16_t color, uint16_t background) {
    display_inst.setTextColor(color ? SH110X_WHITE : SH110X_BLACK, background ? SH110X_WHITE : SH110X_BLACK);
}

// Fill a triangle
void Display::fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color) {
    display_inst.fillTriangle(x0, y0, x1, y1, x2, y2, color ? SH110X_WHITE : SH110X_BLACK);
}

// Get display buffer data
void Display::getDisplayBuffer(uint8_t* buffer, size_t bufferSize) {
    // Copy the display buffer to the provided buffer
    // The SH1106 display uses a 128x64 buffer, which is 1024 bytes
    if (bufferSize >= 1024) {
        // Access the display buffer directly from the Adafruit library
        memcpy(buffer, display_inst.getBuffer(), 1024);
    }
}

// Draw rounded rectangle
void Display::drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color) {
    display_inst.drawRoundRect(x, y, w, h, r, color ? SH110X_WHITE : SH110X_BLACK);
}

// Fill rounded rectangle
void Display::fillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color) {
    display_inst.fillRoundRect(x, y, w, h, r, color ? SH110X_WHITE : SH110X_BLACK);
}

// Set text size
void Display::setTextSize(uint8_t size) {
    display_inst.setTextSize(size);
}

// Draw centered string
void Display::drawCenteredString(int16_t y, const char* text) {
    int16_t x1, y1;
    uint16_t w, h;
    display_inst.getTextBounds(text, 0, 0, &x1, &y1, &w, &h);
    int16_t x = (128 - w) / 2;
    display_inst.setCursor(x, y);
    display_inst.print(text);
}

// Draw centered string (String version)
void Display::drawCenteredString(int16_t y, String text) {
    drawCenteredString(y, text.c_str());
}

// Draw progress bar
void Display::drawProgressBar(int16_t x, int16_t y, int16_t w, int16_t h, uint8_t progress) {
    // Draw border
    drawRoundRect(x, y, w, h, 2, 1);
    
    // Calculate fill width
    int16_t fillWidth = ((w - 4) * progress) / 100;
    
    // Draw fill
    if (fillWidth > 0) {
        fillRoundRect(x + 2, y + 2, fillWidth, h - 4, 1, 1);
    }
}