#include "BattleState.h"

BattleState::BattleState(Player* player, ItemHandler* instantiatr) : State(player) {
    this->background.load("images/states/battle.png");
    this->ppg1Container = ItemContainer(103,74); // Container that holds one of the PowerPuff Girls.
    this->ppg2Container = ItemContainer(246, 147); // Container that holds one of the PowerPuff Girls.
    this->ppg3Container = ItemContainer(103, 208); // Container that holds one of the PowerPuff Girls.
    this->instantiator = instantiatr;
    addPowerPuffGirls();

    // Sounds
    laserSound.load("audio/laser1.wav");
    victory.load("audio/townsvilleIsSafe.wav");
    ppgIntroAudio.load("audio/ppgIntroAudio.mp3");
    himIntroAudio.load("audio/himIntroAudio.mp3");
    ppgTheme.load("audio/powerpuffGirls_ChemicalXTractionTheme.mp3");
    comeOverHere.load("audio/comeOverHere.wav");
}

void BattleState::addPowerPuffGirls() {
    this->ppg = {62, 63, 64};
}

void BattleState::startSoundSequence() {
    ppgIntroAudio.play();
    currentSoundState = PpgIntroAudio;
}

void BattleState:: updateSoundSequence() {
    switch(currentSoundState) {
        case PpgIntroAudio:
            if(!ppgIntroAudio.isPlaying()) {
                himIntroAudio.play();
                currentSoundState = HimIntroAudio;
            } break;
        case HimIntroAudio:
            if(!himIntroAudio.isPlaying()) {
                comeOverHere.play();
                currentSoundState = ComeOverHere;
            } break;
        case ComeOverHere:
            if(!comeOverHere.isPlaying()) {
                ppgTheme.play();
                currentSoundState = PpgTheme;
            } break;
        case PpgTheme:
            break;
        case None:
            break;
        } }
    

void BattleState::attack() {
    laserSound.play();
    villainHealth--;
    if(villainHealth > 0) {
        villainHealth--;
    } if (villainHealth <= 0) { 
        victory.play();
    }
}

void BattleState::draw() {
    background.draw(0,0);
    this->ppg1Container.draw();
    this->ppg2Container.draw();
    this->ppg3Container.draw();
    this->getPlayer()->draw();
}

void BattleState::mouseMoved(int x, int y) {
    State::mouseMoved(x,y);
    // Check if the mouse enters any of the state's containers
    this->ppg1Container.mouseEntered(x,y);
    this->ppg2Container.mouseEntered(x,y);
    this->ppg3Container.mouseEntered(x,y);
};

void BattleState::mousePressed(int x, int y, int button) {
    State::mousePressed(x,y,button);
    if (button == 0) {
        //  Only allow interaction if the player's container is empty (extracting) or if the player's item is a PowerPuff Girl.
        if (this->getPlayer()->getCursorContainer().isEmpty() || isPowerPuffGirl(this->getPlayer()->getCursorContainer().getCurrentItem()))
        this->ppg1Container.leftMouseClicked(x,y,this->getPlayer()->getCursorContainer()); 
        if (this->getPlayer()->getCursorContainer().isEmpty() || isPowerPuffGirl(this->getPlayer()->getCursorContainer().getCurrentItem()))
        this->ppg2Container.leftMouseClicked(x,y,this->getPlayer()->getCursorContainer());
        if (this->getPlayer()->getCursorContainer().isEmpty() || isPowerPuffGirl(this->getPlayer()->getCursorContainer().getCurrentItem())) 
        this->ppg3Container.leftMouseClicked(x,y,this->getPlayer()->getCursorContainer());
    }
};