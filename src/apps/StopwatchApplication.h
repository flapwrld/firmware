#ifndef STOPWATCH_APPLICATION_H
#define STOPWATCH_APPLICATION_H

#include "Application.h"
#include "graphics/bitmaps.h"

class StopwatchApplication : public Application {
private:
    bool running;
    bool stopwatchRunning;
    unsigned long startTime;
    unsigned long elapsedTime;
    unsigned long lastUpdateTime;
    
public:
    StopwatchApplication();
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
    
    // Stopwatch methods
    void startStopwatch();
    void stopStopwatch();
    void resetStopwatch();
    void updateDisplayTime(char* buffer, int bufferSize);
};

#endif // STOPWATCH_APPLICATION_H