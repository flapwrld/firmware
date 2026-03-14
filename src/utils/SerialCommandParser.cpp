#include "SerialCommandParser.h"
#include <string.h>

SerialCommandParser::SerialCommandParser() {
    commandIndex = 0;
    memset(commandBuffer, 0, MAX_COMMAND_LENGTH);
}

void SerialCommandParser::initialize() {
    commandIndex = 0;
    memset(commandBuffer, 0, MAX_COMMAND_LENGTH);
}

NavigationEvent SerialCommandParser::parseCommand() {
    // Check if there's data available on serial
    while (Serial.available() > 0) {
        char c = Serial.read();
        
        // Ignore carriage return
        if (c == '\r') {
            continue;
        }
        
        // Process newline as command terminator
        if (c == '\n') {
            commandBuffer[commandIndex] = '\0';  // Null terminate
            commandIndex = 0;
            
            // Parse the command
            if (strcmp(commandBuffer, "UP") == 0) {
                return NAV_UP;
            } else if (strcmp(commandBuffer, "DOWN") == 0) {
                return NAV_DOWN;
            } else if (strcmp(commandBuffer, "LEFT") == 0) {
                return NAV_LEFT;
            } else if (strcmp(commandBuffer, "RIGHT") == 0) {
                return NAV_RIGHT;
            } else if (strcmp(commandBuffer, "OK") == 0) {
                return NAV_OK;
            } else if (strcmp(commandBuffer, "BACK") == 0) {
                return NAV_BACK;
            } else if (strcmp(commandBuffer, "FUNCTION") == 0) {
                return NAV_FUNCTION;
            } else if (strcmp(commandBuffer, "BACK_LONG") == 0) {
                return NAV_BACK_LONG;
            } else if (strcmp(commandBuffer, "GET_DISPLAY") == 0) {
                return NAV_GET_DISPLAY;
            } else {
                // Unknown command
                Serial.print("Unknown command: ");
                Serial.println(commandBuffer);
                return NAV_NONE;
            }
        } else {
            // Add character to buffer if there's space
            if (commandIndex < MAX_COMMAND_LENGTH - 1) {
                commandBuffer[commandIndex] = c;
                commandIndex++;
            } else {
                // Buffer overflow, reset
                commandIndex = 0;
                memset(commandBuffer, 0, MAX_COMMAND_LENGTH);
            }
        }
    }
    
    return NAV_NONE;
}

bool SerialCommandParser::isCommandAvailable() {
    return Serial.available() > 0;
}