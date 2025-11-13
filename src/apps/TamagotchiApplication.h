#ifndef TAMAGOTCHI_APPLICATION_H
#define TAMAGOTOTCHI_APPLICATION_H

#include "Application.h"
#include "graphics/bitmaps.h"

class TamagotchiApplication : public Application {
private:
    bool running;
    int petHappiness;
    int petHunger;
    int petEnergy;
    int petCleanliness;
    unsigned long lastUpdate;
    
public:
    TamagotchiApplication();
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
    
    // Tamagotchi methods
    void feedPet();
    void playWithPet();
    void cleanPet();
    void putPetToSleep();
    void updatePetStatus();
};

#endif // TAMAGOTCHI_APPLICATION_H