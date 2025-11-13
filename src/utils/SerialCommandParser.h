#ifndef SERIAL_COMMAND_PARSER_H
#define SERIAL_COMMAND_PARSER_H

#include <Arduino.h>
#include "core/Navigation.h"

class SerialCommandParser {
private:
    static const int MAX_COMMAND_LENGTH = 20;
    char commandBuffer[MAX_COMMAND_LENGTH];
    int commandIndex;
    
public:
    SerialCommandParser();
    void initialize();
    NavigationEvent parseCommand();
    bool isCommandAvailable();
};

#endif // SERIAL_COMMAND_PARSER_H