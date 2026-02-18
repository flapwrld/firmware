#ifndef DISPLAY_H
#define DISPLAY_H

#include <Arduino.h>
#include "config.h"

class Display {
private:
    // Display buffer
    uint8_t buffer[OLED_HEIGHT * OLED_WIDTH / 8];
    
public:
    Display();
    void initialize();
    void clear();
    void update();
    void drawPixel(int16_t x, int16_t y, uint16_t color);
    void drawLine(int16_t x0, int16_t y0, int16_t x1, int16_t y1, uint16_t color);
    void drawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
    void fillRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color);
    void drawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
    void fillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color);
    void drawString(int16_t x, int16_t y, const char* text);
    void drawString(int16_t x, int16_t y, String text);
    void drawBitmap(int16_t x, int16_t y, const uint8_t bitmap[], int16_t w, int16_t h, uint16_t color);
    void setTextColor(uint16_t color, uint16_t background);
    void fillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1, int16_t x2, int16_t y2, uint16_t color);
    void getDisplayBuffer(uint8_t* buffer, size_t bufferSize);
    
    // Advanced UI functions
    void drawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color);
    void fillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r, uint16_t color);
    void setTextSize(uint8_t size);
    void drawCenteredString(int16_t y, const char* text);
    void drawCenteredString(int16_t y, String text);
    void drawProgressBar(int16_t x, int16_t y, int16_t w, int16_t h, uint8_t progress);
};

#endif // DISPLAY_H