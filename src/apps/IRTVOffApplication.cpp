#include "IRTVOffApplication.h"
#include "../config.h"
#include "../utils/logger.h"
#include "../graphics/bitmaps.h"
#include <IRremote.h>

IRTVOffApplication::IRTVOffApplication() {
    currentState = MENU;
    currentCode = 0;
    currentBitLength = 0;
    currentProtocol = 0;
    attempts = 0;
    lastAttemptTime = 0;
    learnedCode = 0;
    learnedBitLength = 0;
    learnedProtocol = 0;
    codeLearned = false;
    
    // Initialize IR objects
    irReceiver = new IRrecv(IR_RECEIVE_PIN);
    irSender = new IRsend();
    irResults = new decode_results();
}

void IRTVOffApplication::initialize() {
    // Initialize IR receiver
    irReceiver->enableIRIn();
    
    // IRsend doesn't require explicit initialization in this library version
    // It will use the IR_SEND_PIN defined in config.h when sending signals
    
    resetApplication();
}

void IRTVOffApplication::update() {
    switch (currentState) {
        case MENU:
            // Nothing to update in menu
            break;
        case LEARNING:
            // Check if we received an IR signal
            if (irReceiver->decode(irResults)) {
                // Store the received code
                learnedCode = irResults->value;
                learnedBitLength = irResults->bits;
                learnedProtocol = irResults->decode_type;
                codeLearned = true;
                
                // Resume receiving
                irReceiver->resume();
                
                // Move to success state
                currentState = SUCCESS;
            }
            break;
        case BRUTEFORCING:
            // Try next code if enough time has passed
            if (millis() - lastAttemptTime > ATTEMPT_INTERVAL) {
                tryNextCode();
                lastAttemptTime = millis();
            }
            break;
        case SUCCESS:
        case FAILURE:
            // Nothing to update in these states
            break;
    }
}

void IRTVOffApplication::render(Display* display) {
    display->clear();
    
    switch (currentState) {
        case MENU:
            drawMenu(display);
            break;
        case LEARNING:
            drawLearning(display);
            break;
        case BRUTEFORCING:
            drawBruteForcing(display);
            break;
        case SUCCESS:
            drawSuccess(display);
            break;
        case FAILURE:
            drawFailure(display);
            break;
    }
    
    display->update();
}

void IRTVOffApplication::cleanup() {
    // Stop IR receiver
    irReceiver->disableIRIn();
    
    // Clean up allocated objects
    delete irReceiver;
    delete irSender;
    delete irResults;
    irReceiver = nullptr;
    irSender = nullptr;
    irResults = nullptr;
}

// Navigation handlers
void IRTVOffApplication::onUpButton() {
    // Not used in this application
}

void IRTVOffApplication::onDownButton() {
    // Not used in this application
}

void IRTVOffApplication::onLeftButton() {
    // Not used in this application
}

void IRTVOffApplication::onRightButton() {
    // Not used in this application
}

void IRTVOffApplication::onOkButton() {
    switch (currentState) {
        case MENU:
            // Start brute force by default
            startBruteForce();
            break;
        case LEARNING:
            // Stop learning and go back to menu
            currentState = MENU;
            break;
        case BRUTEFORCING:
            // Stop brute forcing and go back to menu
            currentState = MENU;
            break;
        case SUCCESS:
        case FAILURE:
            // Go back to menu
            currentState = MENU;
            break;
    }
}

void IRTVOffApplication::onBackButton() {
    switch (currentState) {
        case MENU:
            // Will be handled by ApplicationManager to switch to menu
            break;
        case LEARNING:
        case BRUTEFORCING:
        case SUCCESS:
        case FAILURE:
            // Go back to menu
            currentState = MENU;
            break;
    }
}

void IRTVOffApplication::onFunctionButton() {
    switch (currentState) {
        case MENU:
            // Start learning mode
            startLearning();
            break;
        case LEARNING:
        case BRUTEFORCING:
        case SUCCESS:
        case FAILURE:
            // Not used in these states
            break;
    }
}

void IRTVOffApplication::onBackLongPress() {
    // Reset the application
    resetApplication();
}

// Metadata methods
const char* IRTVOffApplication::getName() {
    return "IR TV Off";
}

bool IRTVOffApplication::isRunning() {
    return true; // Always running
}

// Private methods
void IRTVOffApplication::resetApplication() {
    currentState = MENU;
    currentCode = 0;
    currentBitLength = 0;
    currentProtocol = 0;
    attempts = 0;
    lastAttemptTime = 0;
    // Don't reset learned code as it might be useful
}

void IRTVOffApplication::startLearning() {
    currentState = LEARNING;
    // IR receiver is already enabled in initialize()
    // No need to call enableIRIn() again
}

void IRTVOffApplication::startBruteForce() {
    currentState = BRUTEFORCING;
    currentCode = 0;
    currentBitLength = 32; // Start with 32-bit codes
    currentProtocol = 1; // Start with NEC protocol
    attempts = 0;
    lastAttemptTime = millis();
}

void IRTVOffApplication::tryNextCode() {
    if (attempts >= MAX_ATTEMPTS) {
        currentState = FAILURE;
        return;
    }
    
    // Send the current code
    sendPowerCode();
    
    // Move to next code
    currentCode++;
    attempts++;
    
    // For demonstration purposes, we'll just increment the code
    // In a real implementation, you would cycle through known TV power codes
    if (currentCode > 0xFFFFFFFF) {
        currentCode = 0;
    }
}

void IRTVOffApplication::sendPowerCode() {
    // If we have a learned code, use it
    if (codeLearned) {
        // For simplicity, we'll just send the learned code as NEC
        // In a real implementation, you would check the protocol and use the appropriate function
        irSender->sendNEC(learnedCode, learnedBitLength);
    } else {
        // Send a generic power code
        // This is a simplified approach - in reality, you would have a database of codes
        irSender->sendNEC(currentCode, currentBitLength);
    }
}

bool IRTVOffApplication::isValidTVCode(unsigned long code, int bitLength, int protocol) {
    // This is a simplified validation
    // In a real implementation, you would check against a database of known TV codes
    return (bitLength >= 16 && bitLength <= 64);
}

void IRTVOffApplication::drawMenu(Display* display) {
    display->drawString(0, 0, "IR TV Off");
    display->drawString(0, 15, "OK: Brute Force");
    display->drawString(0, 25, "FUNC: Learn Code");
    display->drawString(0, 35, "BACK LONG: Reset");
    
    // Draw IR icon
    display->drawBitmap(112, 0, irIcon, IR_ICON_WIDTH, IR_ICON_HEIGHT, 1);
}

void IRTVOffApplication::drawLearning(Display* display) {
    display->drawString(0, 0, "Learning Mode");
    display->drawString(0, 15, "Point remote at");
    display->drawString(0, 25, "sensor and press");
    display->drawString(0, 35, "TV power button");
    display->drawString(0, 45, "OK: Stop");
    
    // Draw IR icon
    display->drawBitmap(112, 0, irIcon, IR_ICON_WIDTH, IR_ICON_HEIGHT, 1);
}

void IRTVOffApplication::drawBruteForcing(Display* display) {
    display->drawString(0, 0, "Brute Forcing...");
    display->drawString(0, 15, "Trying codes:");
    display->drawString(0, 25, String(currentCode, HEX).c_str());
    display->drawString(0, 35, "Attempts:");
    display->drawString(0, 45, String(attempts).c_str());
    display->drawString(0, 55, "OK: Stop");
    
    // Draw IR icon
    display->drawBitmap(112, 0, irIcon, IR_ICON_WIDTH, IR_ICON_HEIGHT, 1);
}

void IRTVOffApplication::drawSuccess(Display* display) {
    display->drawString(0, 0, "Success!");
    display->drawString(0, 15, "TV should be off");
    display->drawString(0, 25, "Code learned:");
    display->drawString(0, 35, String(learnedCode, HEX).c_str());
    display->drawString(0, 45, "OK: Menu");
    
    // Draw IR icon
    display->drawBitmap(112, 0, irIcon, IR_ICON_WIDTH, IR_ICON_HEIGHT, 1);
}

void IRTVOffApplication::drawFailure(Display* display) {
    display->drawString(0, 0, "Failed!");
    display->drawString(0, 15, "Max attempts");
    display->drawString(0, 25, "reached");
    display->drawString(0, 35, "OK: Menu");
    
    // Draw IR icon
    display->drawBitmap(112, 0, irIcon, IR_ICON_WIDTH, IR_ICON_HEIGHT, 1);
}