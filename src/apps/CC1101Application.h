#ifndef CC1101_APPLICATION_H
#define CC1101_APPLICATION_H

#include "Application.h"
#include <ELECHOUSE_CC1101_SRC_DRV.h>

class CC1101Application : public Application {
private:
    bool running;
    int mode; // 0 = RX, 1 = TX
    int frequency;
    String receivedData;
    String transmittedData;
    unsigned long lastActionTime;
    
public:
    CC1101Application();
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
    
    // CC1101 specific methods
    void switchMode();
    void changeFrequency(int delta);
    void sendData();
    void receiveData();
};

#endif // CC1101_APPLICATION_H