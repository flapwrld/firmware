#ifndef CALCULATOR_APPLICATION_H
#define CALCULATOR_APPLICATION_H

#include "Application.h"
#include "graphics/bitmaps.h"

class CalculatorApplication : public Application {
private:
    bool running;
    double currentValue;
    double previousValue;
    char operation;
    bool waitingForOperand;
    bool showingResult;
    
public:
    CalculatorApplication();
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
    
    // Calculator methods
    void inputDigit(int digit);
    void inputOperation(char op);
    void calculateResult();
    void clearCalculator();
    void updateDisplay(char* buffer, int bufferSize);
};

#endif // CALCULATOR_APPLICATION_H