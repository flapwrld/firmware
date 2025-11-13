#include "SlotsApplication.h"
#include "core/ApplicationManager.h"

extern ApplicationManager appManager;

SlotsApplication::SlotsApplication()
    : display(nullptr), running(false), reel1(0), reel2(0), reel3(0),
      credits(100), spinning(false), lastUpdate(0), spinStartTime(0) {
}

SlotsApplication::SlotsApplication(Display* display, Navigation* navigation)
    : display(display), running(false), reel1(0), reel2(0), reel3(0),
      credits(100), spinning(false), lastUpdate(0), spinStartTime(0) {
}

void SlotsApplication::initialize() {
    running = true;
    reel1 = random(0, 3);
    reel2 = random(0, 3);
    reel3 = random(0, 3);
}

void SlotsApplication::update() {
    if (spinning) {
        unsigned long currentTime = millis();
        
        // Update reels while spinning
        if (currentTime - lastUpdate > REEL_UPDATE_INTERVAL) {
            reel1 = random(0, 3);
            reel2 = random(0, 3);
            reel3 = random(0, 3);
            lastUpdate = currentTime;
        }
        
        // Stop spinning after duration
        if (currentTime - spinStartTime > SPIN_DURATION) {
            stopSpin();
        }
    }
    
    // Use global display instance if local one is not set
    extern Display display;
    render(this->display ? this->display : &display);
}

void SlotsApplication::render(Display* display) {
    Display* displayPtr = this->display ? this->display : display;
    displayPtr->clear();
    
    // Draw title
    displayPtr->drawString(32, 0, "CASINO SLOTS");
    
    // Draw credits
    char creditsStr[20];
    sprintf(creditsStr, "Credits: %d", credits);
    displayPtr->drawString(0, 10, creditsStr);
    
    // Draw reels
    drawReel(20, 25, reel1);
    drawReel(52, 25, reel2);
    drawReel(84, 25, reel3);
    
    // Draw spin button
    if (!spinning) {
        displayPtr->drawString(40, 50, "Press OK to Spin");
    } else {
        displayPtr->drawString(45, 50, "Spinning...");
    }
    
    displayPtr->update();
}

void SlotsApplication::cleanup() {
    running = false;
}

void SlotsApplication::onUpButton() {
    // Not used in this application
}

void SlotsApplication::onDownButton() {
    // Not used in this application
}

void SlotsApplication::onLeftButton() {
    // Not used in this application
}

void SlotsApplication::onRightButton() {
    // Not used in this application
}

void SlotsApplication::onOkButton() {
    if (!spinning && credits > 0) {
        spin();
    }
}

void SlotsApplication::onBackButton() {
    // Exit application
    appManager.switchToApplication(1); // Go back to menu
}

void SlotsApplication::onFunctionButton() {
    // Not used in this application
}

void SlotsApplication::onBackLongPress() {
    // Exit application
    appManager.switchToApplication(1); // Go back to menu
}

const char* SlotsApplication::getName() {
    return "Slots";
}

bool SlotsApplication::isRunning() {
    return running;
}

void SlotsApplication::spin() {
    if (credits > 0) {
        credits--;
        spinning = true;
        spinStartTime = millis();
        lastUpdate = millis();
    }
}

void SlotsApplication::stopSpin() {
    spinning = false;
    
    // Set final values
    reel1 = random(0, 3);
    reel2 = random(0, 3);
    reel3 = random(0, 3);
    
    // Check for win
    if (checkWin()) {
        credits += 10; // Win 10 credits
        extern Display display;
        Display* displayPtr = this->display ? this->display : &display;
        displayPtr->clear();
        displayPtr->drawString(20, 30, "WIN! +10 Credits");
        displayPtr->update();
        delay(2000); // Show win message for 2 seconds
    }
}

bool SlotsApplication::checkWin() {
    // Win if all reels match
    return (reel1 == reel2 && reel2 == reel3);
}

void SlotsApplication::drawReel(int x, int y, int value) {
    extern Display display;
    Display* displayPtr = this->display ? this->display : &display;
    
    // Draw a simple reel with different symbols
    switch (value) {
        case 0: // Cherry
            displayPtr->drawString(x, y, "C");
            break;
        case 1: // Lemon
            displayPtr->drawString(x, y, "L");
            break;
        case 2: // Seven
            displayPtr->drawString(x, y, "7");
            break;
    }
    
    // Draw box around reel
    displayPtr->drawRect(x-2, y-2, 12, 12, 1);
}