@echo off
echo ESP Controller GUI Build Script
echo =============================

REM Check if Python is installed
python --version >nul 2>&1
if %errorlevel% neq 0 (
    echo Python is not installed or not in PATH
    echo Please install Python 3.6 or higher
    pause
    exit /b 1
)

REM Check if development dependencies are installed
python -c "import PyInstaller" >nul 2>&1
if %errorlevel% neq 0 (
    echo Installing development dependencies...
    pip install -r requirements-dev.txt
    if %errorlevel% neq 0 (
        echo Failed to install development dependencies
        pause
        exit /b 1
    )
)

echo.
echo Select build method:
echo 1. PyInstaller (Recommended)
echo 2. cx_Freeze
echo 3. Cancel
echo.

choice /c 123 /m "Select option"
if %errorlevel% == 3 goto :cancel
if %errorlevel% == 2 goto :cxfreeze
if %errorlevel% == 1 goto :pyinstaller

:pyinstaller
echo Building with PyInstaller...
pyinstaller --onefile --windowed esp_controller_gui.spec
if %errorlevel% neq 0 (
    echo PyInstaller build failed
    pause
    exit /b 1
)
echo.
echo Build successful! Executable is in the dist folder.
goto :end

:cxfreeze
echo Building with cx_Freeze...
python setup.py build
if %errorlevel% neq 0 (
    echo cx_Freeze build failed
    pause
    exit /b 1
)
echo.
echo Build successful! Executable is in the build folder.
goto :end

:cancel
echo Build cancelled.
goto :end

:end
echo.
echo Press any key to exit...
pause >nul