#ifndef DOOM_APPLICATION_H
#define DOOM_APPLICATION_H

#include "Application.h"
#include "graphics/bitmaps.h"

class DoomApplication : public Application {
private:
    bool running;
    int gameState; // 0 = menu, 1 = playing, 2 = paused
    int playerX;
    int playerY;
    int playerAngle;
    unsigned long lastFrameTime;
    bool showFPS;
    
public:
    DoomApplication();
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
    
    // DOOM specific methods
    void render3DView(Display* display);
    void renderHUD(Display* display);
    void renderMenu(Display* display);
    void movePlayer(int direction);
    void turnPlayer(int direction);
};

#endif // DOOM_APPLICATION_H