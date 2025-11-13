#!/bin/bash

echo "ESP Controller GUI Build Script"
echo "=============================="

# Check if Python is installed
if ! command -v python3 &> /dev/null
then
    echo "Python 3 is not installed"
    echo "Please install Python 3.6 or higher"
    exit 1
fi

# Check if development dependencies are installed
if ! python3 -c "import PyInstaller" &> /dev/null
then
    echo "Installing development dependencies..."
    pip3 install -r requirements-dev.txt
    if [ $? -ne 0 ]; then
        echo "Failed to install development dependencies"
        exit 1
    fi
fi

echo ""
echo "Select build method:"
echo "1. PyInstaller (Recommended)"
echo "2. cx_Freeze"
echo "3. Cancel"
echo ""

read -p "Enter your choice (1-3): " choice

case $choice in
    1)
        echo "Building with PyInstaller..."
        pyinstaller --onefile esp_controller_gui.spec
        if [ $? -ne 0 ]; then
            echo "PyInstaller build failed"
            exit 1
        fi
        echo ""
        echo "Build successful! Executable is in the dist folder."
        ;;
    2)
        echo "Building with cx_Freeze..."
        python3 setup.py build
        if [ $? -ne 0 ]; then
            echo "cx_Freeze build failed"
            exit 1
        fi
        echo ""
        echo "Build successful! Executable is in the build folder."
        ;;
    3)
        echo "Build cancelled."
        ;;
    *)
        echo "Invalid choice. Build cancelled."
        ;;
esac