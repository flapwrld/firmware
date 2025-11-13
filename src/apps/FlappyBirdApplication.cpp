#include "FlappyBirdApplication.h"
#include "../utils/logger.h"

FlappyBirdApplication::FlappyBirdApplication() {
    currentState = MENU;
    birdY = 32;
    birdVelocity = 0;
    birdX = 30;
    pipeCount = 0;
    score = 0;
    highScore = 0;
    upButton = nullptr;
    downButton = nullptr;
    leftButton = nullptr;
    rightButton = nullptr;
    enterButton = nullptr;
    backButton = nullptr;
}

void FlappyBirdApplication::initialize() {
    resetGame();
}

void FlappyBirdApplication::update() {
    switch (currentState) {
        case MENU:
            // Nothing to update in menu
            break;
        case PLAYING:
            updateGame();
            break;
        case GAME_OVER:
            // Nothing to update in game over screen
            break;
    }
}

void FlappyBirdApplication::render(Display* display) {
    display->clear();
    
    switch (currentState) {
        case MENU:
            drawMenu(display);
            break;
        case PLAYING:
            drawBird(display);
            drawPipes(display);
            // Draw score
            display->drawString(100, 0, String(score).c_str());
            break;
        case GAME_OVER:
            drawGameOver(display);
            break;
    }
    
    display->update();
}

void FlappyBirdApplication::cleanup() {
    // Cleanup resources if needed
}

// Navigation handlers
void FlappyBirdApplication::onUpButton() {
    if (currentState == PLAYING) {
        birdVelocity = JUMP_STRENGTH;
    }
}

void FlappyBirdApplication::onDownButton() {
    // Not used in this game
}

void FlappyBirdApplication::onLeftButton() {
    // Not used in this game
}

void FlappyBirdApplication::onRightButton() {
    // Not used in this game
}

void FlappyBirdApplication::onOkButton() {
    switch (currentState) {
        case MENU:
            currentState = PLAYING;
            resetGame();
            break;
        case PLAYING:
            birdVelocity = JUMP_STRENGTH;
            break;
        case GAME_OVER:
            currentState = MENU;
            break;
    }
}

void FlappyBirdApplication::onBackButton() {
    switch (currentState) {
        case MENU:
            // Will be handled by ApplicationManager to switch to menu
            break;
        case PLAYING:
            currentState = MENU;
            break;
        case GAME_OVER:
            currentState = MENU;
            break;
    }
}

void FlappyBirdApplication::onFunctionButton() {
    // Not used in this game
}

void FlappyBirdApplication::onBackLongPress() {
    // Not used in this game
}

// Metadata methods
const char* FlappyBirdApplication::getName() {
    return "Flappy Bird";
}

bool FlappyBirdApplication::isRunning() {
    return true; // Always running
}

// Private methods
void FlappyBirdApplication::resetGame() {
    birdY = 32;
    birdVelocity = 0;
    birdX = 30;
    pipeCount = 0;
    score = 0;
    
    // Initialize pipes
    for (int i = 0; i < MAX_PIPES; i++) {
        pipes[i].x = -100; // Off screen
        pipes[i].gapY = 0;
        pipes[i].passed = false;
    }
    
    // Spawn first pipe
    spawnPipe();
}

void FlappyBirdApplication::updateGame() {
    // Update bird physics
    birdVelocity += GRAVITY;
    birdY += birdVelocity;
    
    // Update pipes
    updatePipes();
    
    // Check collisions
    checkCollisions();
    
    // Check boundaries
    if (birdY < 0 || birdY > 64) {
        currentState = GAME_OVER;
        if (score > highScore) {
            highScore = score;
        }
    }
}

void FlappyBirdApplication::updatePipes() {
    // Move pipes
    for (int i = 0; i < pipeCount; i++) {
        pipes[i].x -= PIPE_SPEED;
        
        // Check if pipe is off screen
        if (pipes[i].x < -PIPE_WIDTH) {
            // Remove pipe by shifting remaining pipes
            for (int j = i; j < pipeCount - 1; j++) {
                pipes[j] = pipes[j + 1];
            }
            pipeCount--;
            i--; // Adjust index after removal
        }
        // Check if bird passed the pipe
        else if (!pipes[i].passed && pipes[i].x + PIPE_WIDTH < birdX) {
            pipes[i].passed = true;
            score++;
        }
    }
    
    // Spawn new pipes
    if (pipeCount == 0 || (pipeCount < MAX_PIPES && pipes[pipeCount - 1].x < 60)) {
        spawnPipe();
    }
}

void FlappyBirdApplication::checkCollisions() {
    for (int i = 0; i < pipeCount; i++) {
        // Simple collision detection
        if (birdX + 4 > pipes[i].x && birdX < pipes[i].x + PIPE_WIDTH) {
            if (birdY < pipes[i].gapY || birdY + 4 > pipes[i].gapY + PIPE_GAP) {
                currentState = GAME_OVER;
                if (score > highScore) {
                    highScore = score;
                }
            }
        }
    }
}

void FlappyBirdApplication::spawnPipe() {
    if (pipeCount < MAX_PIPES) {
        pipes[pipeCount].x = 128; // Start at right edge
        pipes[pipeCount].gapY = random(10, 40); // Random gap position
        pipes[pipeCount].passed = false;
        pipeCount++;
    }
}

bool FlappyBirdApplication::isColliding() {
    // Simple boundary check
    if (birdY < 0 || birdY > 60) {
        return true;
    }
    
    // Check pipe collisions
    for (int i = 0; i < pipeCount; i++) {
        if (birdX + 4 > pipes[i].x && birdX < pipes[i].x + PIPE_WIDTH) {
            if (birdY < pipes[i].gapY || birdY + 4 > pipes[i].gapY + PIPE_GAP) {
                return true;
            }
        }
    }
    
    return false;
}

void FlappyBirdApplication::drawBird(Display* display) {
    display->drawRect(birdX, birdY, 4, 4, 1);
}

void FlappyBirdApplication::drawPipes(Display* display) {
    for (int i = 0; i < pipeCount; i++) {
        // Draw top pipe
        display->drawRect(pipes[i].x, 0, PIPE_WIDTH, pipes[i].gapY, 1);
        
        // Draw bottom pipe
        int bottomPipeHeight = 64 - (pipes[i].gapY + PIPE_GAP);
        display->drawRect(pipes[i].x, pipes[i].gapY + PIPE_GAP, PIPE_WIDTH, bottomPipeHeight, 1);
    }
}

void FlappyBirdApplication::drawMenu(Display* display) {
    display->drawString(20, 20, "Flappy Bird");
    display->drawString(10, 40, "Press OK to start");
}

void FlappyBirdApplication::drawGameOver(Display* display) {
    display->drawString(20, 20, "Game Over");
    display->drawString(10, 35, String("Score: " + String(score)).c_str());
    display->drawString(10, 45, String("Best: " + String(highScore)).c_str());
    display->drawString(10, 55, "OK for menu");
}