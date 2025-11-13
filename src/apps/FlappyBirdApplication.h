#ifndef FLAPPYBIRDAPPLICATION_H
#define FLAPPYBIRDAPPLICATION_H

#include "Application.h"
#include "../core/Display.h"
#include "../core/Button.h"
#include "../core/ApplicationManager.h"
#include "../graphics/bitmaps.h"

class FlappyBirdApplication : public Application {
private:
    // Game state
    enum GameState {
        MENU,
        PLAYING,
        GAME_OVER
    };
    
    GameState currentState;
    
    // Bird properties
    float birdY;
    float birdVelocity;
    int birdX;
    
    // Pipe properties
    struct Pipe {
        int x;
        int gapY;
        bool passed;
    };
    
    static const int MAX_PIPES = 3;
    Pipe pipes[MAX_PIPES];
    int pipeCount;
    
    // Game settings
    static const int GRAVITY = 1;
    static const int JUMP_STRENGTH = -8;
    static const int PIPE_SPEED = 2;
    static const int PIPE_GAP = 40;
    static const int PIPE_WIDTH = 20;
    
    int score;
    int highScore;
    
    // Button references
    Button* upButton;
    Button* downButton;
    Button* leftButton;
    Button* rightButton;
    Button* enterButton;
    Button* backButton;

public:
    FlappyBirdApplication();
    virtual ~FlappyBirdApplication() = default;
    
    // Application interface implementation
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
    
private:
    void resetGame();
    void updateGame();
    void updatePipes();
    void checkCollisions();
    void spawnPipe();
    bool isColliding();
    void drawBird(Display* display);
    void drawPipes(Display* display);
    void drawMenu(Display* display);
    void drawGameOver(Display* display);
};

#endif // FLAPPYBIRDAPPLICATION_H