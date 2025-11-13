#include "TamagotchiApplication.h"
#include "core/ApplicationManager.h"

extern ApplicationManager appManager;

TamagotchiApplication::TamagotchiApplication() {
    running = false;
    petHappiness = 50;
    petHunger = 50;
    petEnergy = 50;
    petCleanliness = 50;
    lastUpdate = 0;
}

void TamagotchiApplication::initialize() {
    running = true;
    petHappiness = 50;
    petHunger = 50;
    petEnergy = 50;
    petCleanliness = 50;
    lastUpdate = millis();
}

void TamagotchiApplication::update() {
    // Update pet status every 5 seconds
    if (millis() - lastUpdate > 5000) {
        updatePetStatus();
        lastUpdate = millis();
    }
}

void TamagotchiApplication::render(Display* display) {
    // Clear display
    display->clear();
    
    // Draw title with icon
    display->drawBitmap(0, 0, tamagotchiIcon, TAMAGOTCHI_ICON_WIDTH, TAMAGOTCHI_ICON_HEIGHT, 1);
    display->drawString(20, 5, "Tamagotchi");
    
    // Draw pet status
    display->drawString(10, 15, "Happiness:");
    display->fillRect(70, 15, petHappiness / 2, 5, 1);
    display->drawRect(70, 15, 50, 5, 1);
    
    display->drawString(10, 25, "Hunger:");
    display->fillRect(70, 25, (100 - petHunger) / 2, 5, 1);
    display->drawRect(70, 25, 50, 5, 1);
    
    display->drawString(10, 35, "Energy:");
    display->fillRect(70, 35, petEnergy / 2, 5, 1);
    display->drawRect(70, 35, 50, 5, 1);
    
    display->drawString(10, 45, "Clean:");
    display->fillRect(70, 45, petCleanliness / 2, 5, 1);
    display->drawRect(70, 45, 50, 5, 1);
    
    // Draw pet (improved visualization)
    // Head
    display->fillCircle(64, 55, 8, 1);
    display->fillCircle(64, 55, 6, 0); // Inner head
    
    // Eyes
    display->fillCircle(60, 53, 2, 1); // Left eye
    display->fillCircle(68, 53, 2, 1); // Right eye
    display->fillCircle(60, 53, 1, 0); // Left pupil
    display->fillCircle(68, 53, 1, 0); // Right pupil
    
    // Draw mouth based on happiness
    if (petHappiness > 70) {
        // Happy smile
        display->drawLine(60, 58, 64, 60, 1);
        display->drawLine(64, 60, 68, 58, 1);
    } else if (petHappiness < 30) {
        // Sad frown
        display->drawLine(60, 60, 64, 58, 1);
        display->drawLine(64, 58, 68, 60, 1);
    } else {
        // Neutral
        display->drawLine(60, 59, 68, 59, 1);
    }
    
    // Draw ears based on energy
    if (petEnergy > 50) {
        // Erect ears
        display->fillTriangle(58, 47, 56, 42, 60, 47, 1); // Left ear
        display->fillTriangle(70, 47, 72, 42, 68, 47, 1); // Right ear
    } else {
        // Droopy ears
        display->fillTriangle(58, 47, 54, 48, 60, 47, 1); // Left ear
        display->fillTriangle(70, 47, 74, 48, 68, 47, 1); // Right ear
    }
    
    // Draw navigation hint
    display->drawString(10, 55, "OK:Feed  Fn:Play  Left:Clean");
    
    // Update display
    display->update();
}

void TamagotchiApplication::cleanup() {
    running = false;
}

// Navigation handlers
void TamagotchiApplication::onUpButton() {
    // Do nothing
}

void TamagotchiApplication::onDownButton() {
    // Do nothing
}

void TamagotchiApplication::onLeftButton() {
    cleanPet();
}

void TamagotchiApplication::onRightButton() {
    // Do nothing
}

void TamagotchiApplication::onOkButton() {
    feedPet();
}

void TamagotchiApplication::onBackButton() {
    // Go back to menu
    appManager.switchToApplication(1);
}

void TamagotchiApplication::onFunctionButton() {
    playWithPet();
}

void TamagotchiApplication::onBackLongPress() {
    putPetToSleep();
}

// Metadata methods
const char* TamagotchiApplication::getName() {
    return "Tamagotchi";
}

bool TamagotchiApplication::isRunning() {
    return running;
}

// Tamagotchi methods
void TamagotchiApplication::feedPet() {
    if (petHunger > 10) {
        petHunger -= 10;
        petHappiness += 5;
        if (petHappiness > 100) petHappiness = 100;
    }
}

void TamagotchiApplication::playWithPet() {
    if (petEnergy > 10) {
        petHappiness += 10;
        petEnergy -= 10;
        if (petHappiness > 100) petHappiness = 100;
    }
}

void TamagotchiApplication::cleanPet() {
    if (petCleanliness < 100) {
        petCleanliness += 20;
        if (petCleanliness > 100) petCleanliness = 100;
        petHappiness += 5;
        if (petHappiness > 100) petHappiness = 100;
    }
}

void TamagotchiApplication::putPetToSleep() {
    petEnergy += 20;
    if (petEnergy > 100) petEnergy = 100;
}

void TamagotchiApplication::updatePetStatus() {
    // Natural decay of stats over time
    petHappiness -= 1;
    petHunger += 1;
    petEnergy -= 1;
    petCleanliness -= 1;
    
    // Keep values within bounds
    if (petHappiness < 0) petHappiness = 0;
    if (petHunger > 100) petHunger = 100;
    if (petEnergy < 0) petEnergy = 0;
    if (petCleanliness < 0) petCleanliness = 0;
}