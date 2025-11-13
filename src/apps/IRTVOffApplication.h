#ifndef IRTVOFFAPPLICATION_H
#define IRTVOFFAPPLICATION_H

#include "Application.h"
#include "../core/Display.h"
#include "../core/Button.h"
#include "../graphics/bitmaps.h"

// Forward declarations to avoid including IRremote.h in the header
class IRrecv;
class IRsend;
struct decode_results;

class IRTVOffApplication : public Application {
private:
    // Application state
    enum AppState {
        MENU,
        LEARNING,
        BRUTEFORCING,
        SUCCESS,
        FAILURE
    };
    
    AppState currentState;
    
    // IR control
    IRrecv* irReceiver;
    IRsend* irSender;
    decode_results* irResults;
    
    // Brute force parameters
    unsigned long currentCode;
    int currentBitLength;
    int currentProtocol;
    int attempts;
    unsigned long lastAttemptTime;
    static const int MAX_ATTEMPTS = 1000;
    static const unsigned long ATTEMPT_INTERVAL = 1000; // 1 second between attempts
    
    // Learned code (if any)
    unsigned long learnedCode;
    int learnedBitLength;
    int learnedProtocol;
    bool codeLearned;
    
public:
    IRTVOffApplication();
    virtual ~IRTVOffApplication() = default;
    
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
    void resetApplication();
    void startLearning();
    void startBruteForce();
    void sendPowerCode();
    void tryNextCode();
    bool isValidTVCode(unsigned long code, int bitLength, int protocol);
    void drawMenu(Display* display);
    void drawLearning(Display* display);
    void drawBruteForcing(Display* display);
    void drawSuccess(Display* display);
    void drawFailure(Display* display);
};

#endif // IRTVOFFAPPLICATION_H