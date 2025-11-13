#ifndef SLOTS_APPLICATION_H
#define SLOTS_APPLICATION_H

#include "Application.h"
#include "../core/Display.h"
#include "../core/Navigation.h"
#include "../graphics/bitmaps.h"

class SlotsApplication : public Application {
private:
    Display* display;
    bool running;
    int reel1, reel2, reel3;
    int credits;
    bool spinning;
    unsigned long lastUpdate;
    const int REEL_UPDATE_INTERVAL = 200; // ms
    const int SPIN_DURATION = 2000; // ms
    unsigned long spinStartTime;

public:
    SlotsApplication();  // Default constructor
    SlotsApplication(Display* display, Navigation* navigation);
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
    
    void spin();
    void stopSpin();
    bool checkWin();
    void drawReel(int x, int y, int value);
};

#endif