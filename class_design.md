# Class and Interface Designs

## Core System Classes

### Display Class
```cpp
class Display {
private:
    // SH1106 display driver instance
    // Display buffer and configuration
    
public:
    Display();
    void initialize();
    void clear();
    void update();
    
    // Drawing primitives
    void drawPixel(int x, int y, bool color);
    void drawLine(int x1, int y1, int x2, int y2, bool color);
    void drawRect(int x, int y, int width, int height, bool color);
    void fillRect(int x, int y, int width, int height, bool color);
    void drawCircle(int x, int y, int radius, bool color);
    void drawText(int x, int y, const char* text, int fontSize);
    void drawBitmap(int x, int y, const uint8_t* bitmap, int width, int height);
    
    // Display management
    int getWidth();
    int getHeight();
};
```

### Button Class
```cpp
class Button {
private:
    int pin;
    bool lastState;
    bool currentState;
    unsigned long lastDebounceTime;
    unsigned long debounceDelay;
    
public:
    Button(int buttonPin);
    void update();
    bool isPressed();
    bool wasPressed();
    bool wasReleased();
    bool isLongPressed(unsigned long duration);
};
```

### Navigation Class
```cpp
class Navigation {
private:
    Button upButton;
    Button downButton;
    Button leftButton;
    Button rightButton;
    Button okButton;
    Button backButton;
    
public:
    Navigation();
    void update();
    bool isUpPressed();
    bool isDownPressed();
    bool isLeftPressed();
    bool isRightPressed();
    bool isOkPressed();
    bool isBackPressed();
    bool isUpReleased();
    bool isDownReleased();
    // ... other button state methods
};
```

## Application Framework

### Application Interface
```cpp
class Application {
public:
    virtual ~Application() = default;
    
    // Lifecycle methods
    virtual void initialize() = 0;
    virtual void update() = 0;
    virtual void render(Display& display) = 0;
    virtual void cleanup() = 0;
    
    // Navigation methods
    virtual void onUpButton();
    virtual void onDownButton();
    virtual void onLeftButton();
    virtual void onRightButton();
    virtual void onOkButton();
    virtual void onBackButton();
    
    // Getters
    virtual const char* getName() = 0;
    virtual bool isRunning() = 0;
};
```

### Application Manager
```cpp
class ApplicationManager {
private:
    std::vector<Application*> applications;
    int currentAppIndex;
    Application* currentApp;
    
public:
    ApplicationManager();
    void registerApplication(Application* app);
    void switchToApplication(int index);
    void switchToApplication(const char* name);
    void update();
    void render(Display& display);
    void handleNavigation(Navigation& navigation);
    
    // Application lifecycle
    void startApplication();
    void stopApplication();
    
    // Getters
    Application* getCurrentApplication();
    int getApplicationCount();
    Application* getApplication(int index);
};
```

## Application Classes

### File Explorer Application
```cpp
class FileExplorerApp : public Application {
private:
    bool running;
    std::vector<String> fileList;
    int selectedIndex;
    String currentPath;
    
public:
    FileExplorerApp();
    
    // Application interface implementation
    void initialize() override;
    void update() override;
    void render(Display& display) override;
    void cleanup() override;
    
    // Navigation handling
    void onUpButton() override;
    void onDownButton() override;
    void onOkButton() override;
    void onBackButton() override;
    
    // Getters
    const char* getName() override;
    bool isRunning() override;
    
private:
    void loadFileList();
    void navigateUp();
    void navigateIntoDirectory();
};
```

### WiFi Scanner Application
```cpp
class WiFiScannerApp : public Application {
private:
    bool running;
    std::vector<String> wifiNetworks;
    int selectedIndex;
    bool scanning;
    
public:
    WiFiScannerApp();
    
    // Application interface implementation
    void initialize() override;
    void update() override;
    void render(Display& display) override;
    void cleanup() override;
    
    // Navigation handling
    void onUpButton() override;
    void onDownButton() override;
    void onOkButton() override;
    void onBackButton() override;
    
    // Getters
    const char* getName() override;
    bool isRunning() override;
    
private:
    void startScan();
    void updateNetworkList();
};