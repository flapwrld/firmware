#ifndef PAINTAPPLICATION_H
#define PAINTAPPLICATION_H

#include "Application.h"
#include "../core/Display.h"
#include "../core/Button.h"
#include "../core/ApplicationManager.h"
#include "../graphics/bitmaps.h"

class PaintApplication : public Application {
private:
    // Drawing state
    bool isDrawing;
    int lastX, lastY;
    int currentX, currentY;
    
    // Brush properties
    int brushSize;
    bool eraserMode;
    
    // Canvas state
    static const int CANVAS_WIDTH = 128;
    static const int CANVAS_HEIGHT = 64;
    
    // Button references
    Button* upButton;
    Button* downButton;
    Button* leftButton;
    Button* rightButton;
    Button* enterButton;
    Button* backButton;
    
    // Drawing tools
    enum Tool {
        BRUSH,
        ERASER,
        LINE,
        RECTANGLE
    };
    
    Tool currentTool;
    
public:
    PaintApplication();
    virtual ~PaintApplication() = default;
    
    // Application interface implementation
    void initialize() override;
    void update() override;
    void render(Display* display) override;
    void cleanup() override;
    
    // Navigation handlers
    void onUpButton() override;
    void onDownButton() override;
    void onLeftButton() override;
    void onRightButton() override;
    void onOkButton() override;
    void onBackButton() override;
    void onFunctionButton() override;
    void onBackLongPress() override;
    
    // Metadata methods
    const char* getName() override;
    bool isRunning() override;
    
private:
    void drawToolbar(Display* display);
    void drawCanvas(Display* display);
    void clearCanvas();
    void changeTool();
    void changeBrushSize();
};

#endif // PAINTAPPLICATION_H