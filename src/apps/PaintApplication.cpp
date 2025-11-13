#include "PaintApplication.h"
#include "core/ApplicationManager.h"

extern ApplicationManager appManager;

PaintApplication::PaintApplication() {
    isDrawing = false;
    lastX = 0;
    lastY = 0;
    currentX = 0;
    currentY = 0;
    brushSize = 1;
    eraserMode = false;
    currentTool = BRUSH;
    upButton = nullptr;
    downButton = nullptr;
    leftButton = nullptr;
    rightButton = nullptr;
    enterButton = nullptr;
    backButton = nullptr;
}

void PaintApplication::initialize() {
    // Initialize paint application
    isDrawing = false;
    currentX = 64;
    currentY = 32;
}

void PaintApplication::update() {
    // Update paint application logic
    // In a real implementation, this would handle continuous drawing operations
}

void PaintApplication::render(Display* display) {
    display->clear();
    
    // Draw canvas area (leave space for toolbar)
    display->drawRect(0, 0, 128, 56, 1);
    
    // Draw toolbar at bottom
    drawToolbar(display);
    
    // Draw cursor
    display->drawRect(currentX - brushSize, currentY - brushSize, 
                      brushSize * 2, brushSize * 2, 1);
    
    display->update();
}

void PaintApplication::cleanup() {
    // Cleanup resources if needed
}

// Navigation handlers
void PaintApplication::onUpButton() {
    if (currentY > brushSize) {
        currentY--;
    }
}

void PaintApplication::onDownButton() {
    if (currentY < 56 - brushSize) {
        currentY++;
    }
}

void PaintApplication::onLeftButton() {
    if (currentX > brushSize) {
        currentX--;
    }
}

void PaintApplication::onRightButton() {
    if (currentX < 128 - brushSize) {
        currentX++;
    }
}

void PaintApplication::onOkButton() {
    // Start/stop drawing
    isDrawing = !isDrawing;
}

void PaintApplication::onBackButton() {
    // Back to menu
    extern ApplicationManager appManager;
    appManager.switchToApplication(1);
}

void PaintApplication::onFunctionButton() {
    // Change tool
    changeTool();
}

void PaintApplication::onBackLongPress() {
    // Clear canvas
    clearCanvas();
}

// Metadata methods
const char* PaintApplication::getName() {
    return "Paint";
}

bool PaintApplication::isRunning() {
    return true; // Always running
}

// Private methods
void PaintApplication::drawToolbar(Display* display) {
    // Draw toolbar background
    display->drawRect(0, 56, 128, 8, 1);
    
    // Draw tool indicator
    const char* toolName = "Brush";
    if (currentTool == ERASER) toolName = "Eraser";
    else if (currentTool == LINE) toolName = "Line";
    else if (currentTool == RECTANGLE) toolName = "Rect";
    
    display->drawString(0, 58, toolName);
    
    // Draw brush size
    display->drawString(60, 58, String("Size: " + String(brushSize)).c_str());
}

void PaintApplication::drawCanvas(Display* display) {
    // In a real implementation, this would draw the actual canvas content
    // For now, we'll just draw the cursor
}

void PaintApplication::clearCanvas() {
    // Clear the canvas
}

void PaintApplication::changeTool() {
    // Cycle through tools
    currentTool = static_cast<Tool>((currentTool + 1) % 4);
}

void PaintApplication::changeBrushSize() {
    // Cycle brush size
    brushSize = (brushSize % 5) + 1;
}