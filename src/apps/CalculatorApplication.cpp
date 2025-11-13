#include "CalculatorApplication.h"
#include "core/ApplicationManager.h"
#include <Arduino.h>

extern ApplicationManager appManager;

CalculatorApplication::CalculatorApplication() {
    running = false;
    currentValue = 0;
    previousValue = 0;
    operation = 0;
    waitingForOperand = true;
    showingResult = false;
}

void CalculatorApplication::initialize() {
    running = true;
    clearCalculator();
}

void CalculatorApplication::update() {
    // Nothing to update continuously
}

void CalculatorApplication::render(Display* display) {
    // Clear display
    display->clear();
    
    // Draw title with icon
    display->drawBitmap(0, 0, calculatorIcon, CALCULATOR_ICON_WIDTH, CALCULATOR_ICON_HEIGHT, 1);
    display->drawString(20, 5, "Calculator");
    
    // Display current value
    char displayBuffer[16];
    if (currentValue == (int)currentValue) {
        sprintf(displayBuffer, "%d", (int)currentValue);
    } else {
        sprintf(displayBuffer, "%.2f", currentValue);
    }
    
    // Display result right-aligned
    display->drawString(128 - strlen(displayBuffer) * 6, 20, displayBuffer);
    
    // Draw calculator buttons
    // Row 1
    display->drawString(20, 35, "7 8 9 /");
    // Row 2
    display->drawString(20, 45, "4 5 6 *");
    // Row 3
    display->drawString(20, 55, "1 2 3 -");
    // Row 4
    display->drawString(20, 65, "0 C = +");
    
    // Update display
    display->update();
}

void CalculatorApplication::cleanup() {
    running = false;
}

// Navigation handlers
void CalculatorApplication::onUpButton() {
    // Do nothing
}

void CalculatorApplication::onDownButton() {
    // Do nothing
}

void CalculatorApplication::onLeftButton() {
    // Do nothing
}

void CalculatorApplication::onRightButton() {
    // Do nothing
}

void CalculatorApplication::onOkButton() {
    // For this simple implementation, we'll just show a message
    // A full implementation would require a more complex input system
}

void CalculatorApplication::onBackButton() {
    // Go back to menu
    appManager.switchToApplication(1);
}

void CalculatorApplication::onFunctionButton() {
    // Do nothing
}

void CalculatorApplication::onBackLongPress() {
    clearCalculator();
}

// Metadata methods
const char* CalculatorApplication::getName() {
    return "Calculator";
}

bool CalculatorApplication::isRunning() {
    return running;
}

// Calculator methods
void CalculatorApplication::inputDigit(int digit) {
    if (waitingForOperand) {
        currentValue = digit;
        waitingForOperand = false;
        showingResult = false;
    } else {
        currentValue = currentValue * 10 + digit;
    }
}

void CalculatorApplication::inputOperation(char op) {
    if (!waitingForOperand) {
        if (operation != 0) {
            calculateResult();
        }
        previousValue = currentValue;
        operation = op;
        waitingForOperand = true;
    }
}

void CalculatorApplication::calculateResult() {
    if (operation != 0) {
        switch (operation) {
            case '+':
                currentValue = previousValue + currentValue;
                break;
            case '-':
                currentValue = previousValue - currentValue;
                break;
            case '*':
                currentValue = previousValue * currentValue;
                break;
            case '/':
                if (currentValue != 0) {
                    currentValue = previousValue / currentValue;
                }
                break;
        }
        operation = 0;
        waitingForOperand = true;
        showingResult = true;
    }
}

void CalculatorApplication::clearCalculator() {
    currentValue = 0;
    previousValue = 0;
    operation = 0;
    waitingForOperand = true;
    showingResult = false;
}

void CalculatorApplication::updateDisplay(char* buffer, int bufferSize) {
    if (currentValue == (int)currentValue) {
        snprintf(buffer, bufferSize, "%d", (int)currentValue);
    } else {
        snprintf(buffer, bufferSize, "%.2f", currentValue);
    }
}