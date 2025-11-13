#include "DoomApplication.h"
#include "core/ApplicationManager.h"
#include <Arduino.h>

extern ApplicationManager appManager;

DoomApplication::DoomApplication() {
    running = false;
    gameState = 0; // Start in menu
    playerX = 64;
    playerY = 32;
    playerAngle = 0;
    lastFrameTime = 0;
    showFPS = false;
}

void DoomApplication::initialize() {
    running = true;
    gameState = 0; // Start in menu
    playerX = 64;
    playerY = 32;
    playerAngle = 0;
    lastFrameTime = millis();
}

void DoomApplication::update() {
    // Update game logic based on current state
    if (gameState == 1) { // Playing
        // In a real implementation, this would update game entities, physics, etc.
        // For this simplified version, we'll just update the frame timer
    }
}

void DoomApplication::render(Display* display) {
    switch (gameState) {
        case 0: // Menu
            renderMenu(display);
            break;
        case 1: // Playing
            render3DView(display);
            renderHUD(display);
            break;
        case 2: // Paused
            render3DView(display);
            // Draw pause overlay
            display->fillRect(20, 20, 88, 24, 0);
            display->setTextColor(1, 0);
            display->drawString(45, 28, "PAUSED");
            display->setTextColor(1, 0);
            break;
    }
}

void DoomApplication::cleanup() {
    running = false;
}

// Navigation handlers
void DoomApplication::onUpButton() {
    if (gameState == 0) { // In menu
        // Could navigate menu options
    } else if (gameState == 1) { // Playing
        movePlayer(1); // Move forward
    }
}

void DoomApplication::onDownButton() {
    if (gameState == 0) { // In menu
        // Could navigate menu options
    } else if (gameState == 1) { // Playing
        movePlayer(-1); // Move backward
    }
}

void DoomApplication::onLeftButton() {
    if (gameState == 0) { // In menu
        // Could navigate menu options
    } else if (gameState == 1) { // Playing
        turnPlayer(-1); // Turn left
    }
}

void DoomApplication::onRightButton() {
    if (gameState == 0) { // In menu
        // Could navigate menu options
    } else if (gameState == 1) { // Playing
        turnPlayer(1); // Turn right
    }
}

void DoomApplication::onOkButton() {
    if (gameState == 0) { // In menu
        gameState = 1; // Start game
    } else if (gameState == 1) { // Playing
        // Could be used for shooting or interacting
    } else if (gameState == 2) { // Paused
        gameState = 1; // Resume game
    }
}

void DoomApplication::onBackButton() {
    if (gameState == 0) { // In menu
        // Go back to main menu
        appManager.switchToApplication(1);
    } else if (gameState == 1) { // Playing
        gameState = 2; // Pause game
    } else if (gameState == 2) { // Paused
        gameState = 0; // Return to menu
    }
}

void DoomApplication::onFunctionButton() {
    // Toggle FPS display
    showFPS = !showFPS;
}

void DoomApplication::onBackLongPress() {
    // Force exit to main menu
    appManager.switchToApplication(1);
}

// Metadata methods
const char* DoomApplication::getName() {
    return "DOOM";
}

bool DoomApplication::isRunning() {
    return running;
}

// DOOM specific methods
void DoomApplication::render3DView(Display* display) {
    // Draw a simple pseudo-3D view
    // This is a very simplified version of what a real DOOM engine would do
    
    // Sky (top half) - darker shade
    display->fillRect(0, 0, 128, 32, 0); // Black sky
    
    // Ground (bottom half) - lighter shade
    display->fillRect(0, 32, 128, 32, 1); // White ground
    
    // Draw some simple walls/obstacles with better perspective
    // In a real implementation, this would use raycasting
    
    // Draw a simple corridor with varying wall heights for 3D effect
    for (int x = 0; x < 128; x += 16) {
        // Calculate wall height based on distance (simplified)
        int distance = abs(64 - x); // Distance from center
        int wallHeight = 32 - (distance / 4); // Taller in center, shorter at edges
        if (wallHeight < 8) wallHeight = 8; // Minimum height
        
        // Draw wall slice
        int top = 32 - (wallHeight / 2);
        int bottom = 32 + (wallHeight / 2);
        display->drawLine(x, top, x, bottom, 0);
    }
    
    // Draw some "enemies" as simple shapes
    display->fillCircle(40, 32, 4, 0); // Enemy 1 (circle)
    display->fillRect(80, 28, 8, 8, 0); // Enemy 2 (square)
    
    // Draw weapon at bottom center
    display->fillRect(56, 48, 16, 16, 0); // Simple weapon representation
}

void DoomApplication::renderHUD(Display* display) {
    // Draw HUD background
    display->fillRect(0, 0, 128, 16, 1); // White background for HUD
    display->fillRect(0, 48, 128, 16, 1); // White background for weapon
    
    // Set text color for HUD (black text on white background)
    display->setTextColor(0, 1);
    
    // Draw health bar
    display->drawString(0, 2, "H:");
    display->fillRect(16, 4, 30, 6, 0); // Black border
    display->fillRect(17, 5, 22, 4, 1); // White background
    display->fillRect(17, 5, 16, 4, 0); // Black health (75%)
    
    // Draw ammo
    display->drawString(50, 2, "A:");
    display->fillRect(66, 4, 20, 6, 0); // Black border
    display->fillRect(67, 5, 18, 4, 1); // White background
    display->fillRect(67, 5, 10, 4, 0); // Black ammo (50%)
    
    // Draw weapon at bottom center
    display->fillRect(56, 50, 16, 12, 0); // Black weapon
    
    // Draw FPS if enabled
    if (showFPS) {
        unsigned long currentTime = millis();
        unsigned long frameTime = currentTime - lastFrameTime;
        lastFrameTime = currentTime;
        
        if (frameTime > 0) {
            int fps = 1000 / frameTime;
            char fpsBuffer[8];
            sprintf(fpsBuffer, "%d", fps);
            display->drawString(100, 2, "FPS:");
            display->drawString(120, 2, fpsBuffer);
        }
    }
    
    // Reset text color to default
    display->setTextColor(1, 0);
}

void DoomApplication::renderMenu(Display* display) {
    // Draw title with icon
    display->drawBitmap(0, 0, doomIcon, DOOM_ICON_WIDTH, DOOM_ICON_HEIGHT, 1);
    display->drawString(20, 5, "DOOM");
    
    // Draw menu options
    display->drawString(30, 25, "START GAME");
    display->drawString(30, 35, "OPTIONS");
    display->drawString(30, 45, "EXIT");
    
    // Draw instructions
    display->drawString(10, 55, "OK:Select  Back:Exit");
    
    // Draw a simple animation
    static int animationFrame = 0;
    animationFrame = (animationFrame + 1) % 20;
    display->fillRect(25 + animationFrame, 25, 4, 4, 0);
}

void DoomApplication::movePlayer(int direction) {
    // Simple movement logic
    int moveSpeed = 2;
    int newX = playerX + direction * moveSpeed * cos(playerAngle * 3.14159 / 180);
    int newY = playerY + direction * moveSpeed * sin(playerAngle * 3.14159 / 180);
    
    // Keep player within bounds
    if (newX >= 2 && newX <= 126 && newY >= 2 && newY <= 62) {
        playerX = newX;
        playerY = newY;
    }
}

void DoomApplication::turnPlayer(int direction) {
    // Simple turning logic
    int turnSpeed = 5;
    playerAngle += direction * turnSpeed;
    
    // Keep angle within 0-360 range
    if (playerAngle < 0) playerAngle += 360;
    if (playerAngle >= 360) playerAngle -= 360;
}