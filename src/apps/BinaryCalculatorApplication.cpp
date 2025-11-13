#include "BinaryCalculatorApplication.h"
#include "core/ApplicationManager.h"
#include <Arduino.h>
#include <stdio.h>

extern ApplicationManager appManager;

BinaryCalculatorApplication::BinaryCalculatorApplication() {
    running = false;
    currentValue = 0;
    cursorPosition = 0;
    showingResult = false;
    memset(binaryResult, 0, sizeof(binaryResult));
}

void BinaryCalculatorApplication::initialize() {
    running = true;
    currentValue = 0;
    cursorPosition = 0;
    showingResult = false;
    memset(binaryResult, 0, sizeof(binaryResult));
    convertToBinary();
}

void BinaryCalculatorApplication::update() {
    // Nothing to update continuously
}

void BinaryCalculatorApplication::render(Display* display) {
    // Clear display
    display->clear();
    
    // Draw title with icon
    display->drawBitmap(0, 0, binaryCalculatorIcon, BINARY_CALCULATOR_ICON_WIDTH, BINARY_CALCULATOR_ICON_HEIGHT, 1);
    display->drawString(20, 5, "Bin Calculator");
    
    if (!showingResult) {
        // Display current value
        char displayBuffer[16];
        sprintf(displayBuffer, "%d", currentValue);
        
        // Display decimal value
        display->drawString(10, 20, "Decimal:");
        display->drawString(70, 20, displayBuffer);
        
        // Display cursor
        int cursorX = 70 + cursorPosition * 6;
        display->drawString(cursorX, 28, "^");
        
        // Display binary result
        display->drawString(10, 35, "Binary:");
        // Pad binary result to 8 bits for consistent display
        char paddedBinary[9];
        int binaryLen = strlen(binaryResult);
        if (binaryLen < 8) {
            int padding = 8 - binaryLen;
            for (int i = 0; i < padding; i++) {
                paddedBinary[i] = '0';
            }
            strcpy(paddedBinary + padding, binaryResult);
        } else {
            strcpy(paddedBinary, binaryResult);
        }
        display->drawString(70, 35, paddedBinary);
        
        // Display instructions
        display->drawString(10, 50, "Up/Dn: Change digit");
        display->drawString(10, 60, "L/R: Move cursor");
        display->drawString(10, 70, "OK: Convert  Fn: Clear");
    } else {
        // Display binary result (full width)
        display->drawString(10, 20, "Binary:");
        display->drawString(70, 20, binaryResult);
        
        // Display decimal value
        char displayBuffer[16];
        sprintf(displayBuffer, "Decimal: %d", currentValue);
        display->drawString(10, 35, displayBuffer);
        
        // Display padded binary for visualization
        display->drawString(10, 50, "8-bit:");
        char paddedBinary[9];
        int binaryLen = strlen(binaryResult);
        if (binaryLen < 8) {
            int padding = 8 - binaryLen;
            for (int i = 0; i < padding; i++) {
                paddedBinary[i] = '0';
            }
            strcpy(paddedBinary + padding, binaryResult);
        } else {
            strcpy(paddedBinary, binaryResult);
        }
        display->drawString(70, 50, paddedBinary);
        
        // Display instruction
        display->drawString(10, 65, "OK: Back  Fn: New");
    }
    
    // Update display
    display->update();
}

void BinaryCalculatorApplication::cleanup() {
    running = false;
}

// Navigation handlers
void BinaryCalculatorApplication::onUpButton() {
    if (!showingResult) {
        incrementDigit();
        convertToBinary();
    }
}

void BinaryCalculatorApplication::onDownButton() {
    if (!showingResult) {
        decrementDigit();
        convertToBinary();
    }
}

void BinaryCalculatorApplication::onLeftButton() {
    if (!showingResult) {
        moveCursorLeft();
    }
}

void BinaryCalculatorApplication::onRightButton() {
    if (!showingResult) {
        moveCursorRight();
    }
}

void BinaryCalculatorApplication::onOkButton() {
    if (!showingResult) {
        showingResult = true;
    } else {
        // Allow going back to input mode
        showingResult = false;
    }
}

void BinaryCalculatorApplication::onBackButton() {
    // Go back to menu
    appManager.switchToApplication(1);
}

void BinaryCalculatorApplication::onFunctionButton() {
    if (!showingResult) {
        clearCalculator();
    } else {
        // Reset to input mode
        showingResult = false;
        clearCalculator();
    }
}

void BinaryCalculatorApplication::onBackLongPress() {
    clearCalculator();
}

// Metadata methods
const char* BinaryCalculatorApplication::getName() {
    return "Binary Calculator";
}

bool BinaryCalculatorApplication::isRunning() {
    return running;
}

// Binary calculator methods
void BinaryCalculatorApplication::incrementDigit() {
    // Convert current value to string to manipulate digits
    char valueStr[16];
    sprintf(valueStr, "%d", currentValue);
    int len = strlen(valueStr);
    
    if (len > 0 && cursorPosition < len) {
        // Increment the digit at cursor position
        if (valueStr[cursorPosition] < '9') {
            valueStr[cursorPosition]++;
        } else {
            valueStr[cursorPosition] = '0'; // Wrap around
        }
        
        currentValue = atoi(valueStr);
    } else {
        // If cursor is at the end or beyond, add a new digit
        if (len == 0) {
            currentValue = 1;
            cursorPosition = 0;
        } else {
            currentValue *= 10;
            currentValue += 1;
            cursorPosition = len; // Move cursor to the new digit
        }
    }
}

void BinaryCalculatorApplication::decrementDigit() {
    // Convert current value to string to manipulate digits
    char valueStr[16];
    sprintf(valueStr, "%d", currentValue);
    int len = strlen(valueStr);
    
    if (len > 0 && cursorPosition < len) {
        // Decrement the digit at cursor position
        if (valueStr[cursorPosition] > '0') {
            valueStr[cursorPosition]--;
        } else {
            valueStr[cursorPosition] = '9'; // Wrap around
        }
        
        currentValue = atoi(valueStr);
    } else {
        // If we're at the end or beyond, and we have digits, add a new digit
        if (len > 0) {
            currentValue *= 10;
            cursorPosition = len; // Move cursor to the new digit
        }
        // If we have no digits, do nothing
    }
}

void BinaryCalculatorApplication::moveCursorLeft() {
    if (cursorPosition > 0) {
        cursorPosition--;
    }
}

void BinaryCalculatorApplication::moveCursorRight() {
    char valueStr[16];
    sprintf(valueStr, "%d", currentValue);
    int len = strlen(valueStr);
    
    if (cursorPosition < len) {
        cursorPosition++;
    } else if (len > 0) {
        // If cursor is at the end, we can add a new digit
        // This is handled when the user presses up/down
    }
}

void BinaryCalculatorApplication::convertToBinary() {
    // Convert currentValue to binary string
    if (currentValue == 0) {
        strcpy(binaryResult, "0");
        return;
    }
    
    int value = currentValue;
    int index = 0;
    char temp[33];
    
    // Convert to binary (LSB first in temp)
    while (value > 0 && index < 32) {
        temp[index++] = (value % 2) ? '1' : '0';
        value = value / 2;
    }
    
    // Reverse to get MSB first
    for (int i = 0; i < index; i++) {
        binaryResult[i] = temp[index - 1 - i];
    }
    binaryResult[index] = '\0';
}

void BinaryCalculatorApplication::clearCalculator() {
    currentValue = 0;
    cursorPosition = 0;
    showingResult = false;
    memset(binaryResult, 0, sizeof(binaryResult));
    convertToBinary();
}