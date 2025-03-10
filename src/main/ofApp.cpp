#include "ofApp.h"
//--------------------------------------------------------------
void ofApp::setup() {
    this->instantiator = new ItemHandler();
    this->player = new Player();
    this->chestState = new ChestState(player);
    this->craftingState = new CraftingState(player,instantiator);
    this->furnaceState = new FurnaceState(player,instantiator);
    this->generatorState= new GeneratorState(player,instantiator);

    this->relaxingMusic.load("audio/miceOnVenus.mp3");
    this->relaxingMusic.play();

    giveItems();
    this->currentState = chestState;
}

/**
 * Handles mouse press events and manages state transitions.
 * 
 * This method is called whenever a mouse button is pressed. It delegates the event to the current state's
 * mousePressed method and checks if the left mouse button (button 0) was pressed. If so, it iterates through
 * the StateButtons and checks if any button was pressed. If a button is pressed, it changes the current state
 * to the target state of the button and plays the button's sound effect.
 * 
 * Basics of the state machine:
 * - The state machine consists of different states (e.g., "chest", "crafting", "furnace").
 * - Transitions between states occur based on user interactions with StateButton objects.
 * - Each state can have its own behavior and actions.
 * - The current state determines the system's behavior at any given time.
 * 
 * @param x The x-coordinate of the mouse cursor.
 * @param y The y-coordinate of the mouse cursor.
 * @param button The mouse button that was pressed (0 for left button, 2 for right button).
 */
void ofApp::mousePressed(int x, int y, int button) {
    currentState->mousePressed(x,y,button);
    if (button == 0) {
        // Iterate through StateButtons
        for (auto stateButton : player->getStateButtons()) {
            if (stateButton.onPress(x,y)) {
                if (stateButton.getTargetState() == "chest") {
                    this->currentState = chestState;
                }
                else if (stateButton.getTargetState() == "crafting") {
                    this->currentState = craftingState;
                }
                else if (stateButton.getTargetState() == "furnace") {
                    this->currentState = furnaceState;
                }
                else if (stateButton.getTargetState() == "generator") {
                    this->currentState = generatorState;
                }
                stateButton.playSoundEffect();
            }
        }
    }
}
void ofApp::update() { 
    if (!relaxingMusic.isPlaying()) relaxingMusic.play();
        currentState->update();
    }
void ofApp::draw() { currentState->draw();}
void ofApp::mouseMoved(int x, int y) { currentState->mouseMoved(x,y); }

//aqui es que tengo que hacer algunos cambios para el cheat code
//en vez de currentState->keyPressed(key);
void ofApp::keyPressed(int key) { 
    //aqui va el cheat code
    if(key == 'b' || key == 'B') {giveBeaconItems();} currentState->keyPressed(key); 
    //cheat code 2 Ender Tools
    if(key == 'e' || key == 'E') {giveEnderToolItems();} currentState->keyPressed(key); }

// Helper function that gives the player, or the chest, items.
void ofApp::giveItems() {
    this->player->addItem(instantiator->getItemFromNumber(55), 1, 26);
    this->chestState->addItem(instantiator->getItemFromNumber(2), 4);
    this->chestState->addItem(instantiator->getItemFromNumber(5), 1);
    this->chestState->addItem(instantiator->getItemFromNumber(10), 1);
    this->chestState->addItem(instantiator->getItemFromNumber(15), 1);
    this->chestState->addItem(instantiator->getItemFromNumber(20), 1);
    this->chestState->addItem(instantiator->getItemFromNumber(25), 1);
    this->chestState->addItem(instantiator->getItemFromNumber(57), 1);
    this->chestState->addItem(instantiator->getItemFromNumber(58), 1);
    this->chestState->addItem(instantiator->getItemFromNumber(59), 1);
    this->chestState->addItem(instantiator->getItemFromNumber(60), 1);
    this->chestState->addItem(instantiator->getItemFromNumber(61), 1);
}

//una funcion para que me den los items
//para crear el beacon
void ofApp::giveBeaconItems(){
    this->player->addItem(instantiator->getItemFromNumber(41),3); //Obsidian
    this->player->addItem(instantiator->getItemFromNumber(37),1); //Nether Star
    this->player->addItem(instantiator->getItemFromNumber(40),5); //Glass
    
}

//una funcion para que me den los items 
//para crear los ender tools

void ofApp::giveEnderToolItems(){
    this->player->addItem(instantiator->getItemFromNumber(50),64); // 64 Ender Eyes
    this->player->addItem(instantiator->getItemFromNumber(42),5); // 5 Beacons
    this->player->addItem(instantiator->getItemFromNumber(23),1); // 1 Diamond axe
    this->player->addItem(instantiator->getItemFromNumber(28),1); // 1 Diamond hoe
    this->player->addItem(instantiator->getItemFromNumber(18),1); // 1 Diamond sword
    this->player->addItem(instantiator->getItemFromNumber(13),1); // 1 Diamond shovel
    this->player->addItem(instantiator->getItemFromNumber(8),1); // 1 Diamond pickaxe
}


//------------------UNUSED--------------------------------------
void ofApp::keyReleased(int key) {}
void ofApp::mouseDragged(int x, int y, int button) {}
void ofApp::mouseReleased(int x, int y, int button) {}
void ofApp::mouseEntered(int x, int y) {}
void ofApp::mouseExited(int x, int y) {}
void ofApp::windowResized(int w, int h) {}
void ofApp::gotMessage(ofMessage msg) {}
void ofApp::dragEvent(ofDragInfo dragInfo) {}