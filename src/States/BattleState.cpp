#include "BattleState.h"

BattleState::BattleState(Player* player, ItemHandler* instantiatr) : State(player) {
    this->background.load("images/states/battle.png");
    this->ppg1Container = ItemContainer(150,111); // Container that holds one of the PowerPuff Girls.
    this->ppg2Container = ItemContainer(150, 307); // Container that holds one of the PowerPuff Girls.
    this->ppg3Container = ItemContainer(360, 213); // Container that holds one of the PowerPuff Girls.
    this->instantiator = instantiatr;
    addPowerPuffGirls();
}

void BattleState::addPowerPuffGirls() {
    this->ppg = {62, 63, 64};
}

void BattleState::attack() {
//Implement later.
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