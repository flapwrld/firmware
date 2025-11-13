@echo off
echo Starting ESP Device Controller...
echo ===============================

REM Check if Python is installed
python --version >nul 2>&1
if %errorlevel% neq 0 (
    echo Python is not installed or not in PATH
    echo Please install Python 3.6 or higher
    pause
    exit /b 1
)

REM Check if requirements are installed
python -c "import serial" >nul 2>&1
if %errorlevel% neq 0 (
    echo Installing required dependencies...
    pip install -r requirements.txt
    if %errorlevel% neq 0 (
        echo Failed to install dependencies
        pause
        exit /b 1
    )
)

REM Run the controller
echo Starting the controller...
python esp_controller_gui.py

pause