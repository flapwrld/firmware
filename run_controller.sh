#!/bin/bash

echo "Starting ESP Device Controller..."
echo "==============================="

# Check if Python is installed
if ! command -v python3 &> /dev/null
then
    echo "Python 3 is not installed"
    echo "Please install Python 3.6 or higher"
    exit 1
fi

# Check if requirements are installed
if ! python3 -c "import serial" &> /dev/null
then
    echo "Installing required dependencies..."
    pip3 install -r requirements.txt
    if [ $? -ne 0 ]; then
        echo "Failed to install dependencies"
        exit 1
    fi
fi

# Run the controller
echo "Starting the controller..."
python3 esp_controller_gui.py