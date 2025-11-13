#ifndef BINARY_CALCULATOR_APPLICATION_H
#define BINARY_CALCULATOR_APPLICATION_H

#include "Application.h"
#include "graphics/bitmaps.h"

class BinaryCalculatorApplication : public Application {
private:
    bool running;
    int currentValue;
    int cursorPosition;
    bool showingResult;
    char binaryResult[33]; // 32 bits + null terminator
    
public:
    BinaryCalculatorApplication();
    void initialize() override;
    void update() override;
    void render(Display* display) override;
    void cleanup() override;
    
    // Navigation handlers
    void onUpButton() override;
    void onDownButton() override;
    void onLeftButton() override;
    void onRightButton() override;
    void onOkButton() override;
    void onBackButton() override;
    void onFunctionButton() override;
    void onBackLongPress() override;
    
    // Metadata methods
    const char* getName() override;
    bool isRunning() override;
    
    // Binary calculator methods
    void incrementDigit();
    void decrementDigit();
    void moveCursorLeft();
    void moveCursorRight();
    void convertToBinary();
    void clearCalculator();
    void updateBinaryResult();
};

#endif // BINARY_CALCULATOR_APPLICATION_H