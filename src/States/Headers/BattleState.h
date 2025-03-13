#pragma once
#include "State.h"

/**
 * @class BattleState
 * @brief Represents the state of the game when the player is interacting with the battle ground.
 */
class BattleState : public State {
    private:
        ItemContainer ppg1Container; ///< The container that holds the first PowerPuff Girl.
        ItemContainer ppg2Container; ///< The container that holds the second PowerPuff Girl.
        ItemContainer ppg3Container; ///< The container that holds the third PowerPuff Girl.
        ItemHandler* instantiator; ///< Pointer to the item handler for item creation.
        vector<int> ppg; ///< Holds the numbers of all PowerPuff Girls.

        enum SoundState {     ///< Assigned names to integer values. This makes switch case in BattleState.cpp easier to read.
            PpgIntroAudio,
            HimIntroAudio,
            ComeOverHere,
            PpgTheme,
            None
        };

        ofSoundPlayer laserSound;  ///< Sound that plays when you attack the villain.
        ofSoundPlayer victory; ///< Sound that plays when the PowerPuff Girls defeat the villain.
        ofSoundPlayer ppgIntroAudio; ///< Introduction to the PowerPuff Girls.
        ofSoundPlayer himIntroAudio; ///< Introduction to Him.
        ofSoundPlayer comeOverHere; ///< Him sound effect.
        ofSoundPlayer ppgTheme;  ///< PowerPuff Girls Theme Song.
        SoundState currentSoundState = None; ///< Default integer.

    public:
        /**
         * @brief Constructs a FurnaceState object with a player and an item handler pointer.
         * @param player Player pointer.
         * @param instantiator Item handler pointer.
         */
        BattleState(Player* player, ItemHandler* instantiatr);

        /**
         * @brief Verifies if item placed is a PowerPuff Girl.
         * @param itm Item placed in container.
         */
        bool isPowerPuffGirl(Item itm) {
            for (int itemNum : this->ppg) { if (itm.getItemNumber() == itemNum) return true; }
            return false;
        }

        /**
         * @brief Defines what items are the PowerPuff Girls.
         */
        void addPowerPuffGirls();

        /**
         * @brief Starts the sequence of sounds. Press 'S' or 's' to activate.
         */
        void startSoundSequence();

        /**
         * @brief Updates the sounds that should play next. Press 'N' or 'n' to activate.
         */
        void updateSoundSequence();

        /**
         * @brief Handles damage done to villain.
         */
        void attack();

        int villainHealth = 3;  // Villain's health.
        int getVillainHealth() {return villainHealth;} //Getter for villain's health.

        /**
         * @brief Updates the state. Mandatory unused implementation.
         */
        void update(){}; 

        /**
         * @brief Draws the battle state on the screen.
         */
        void draw(); 

        /**
         * @brief Handles key press events.
         * @param key The key that was pressed.
         */
        void keyPressed(int key) { 
        if (key == 'A' || key == 'a') attack(); 
        if (key == 'S' || key == 's') startSoundSequence();
        if(key== 'N' || key == 'n') updateSoundSequence(); }

        /**
         * @brief Handles mouse movement events.
         * @param x The x-coordinate of the mouse.
         * @param y The y-coordinate of the mouse.
         */
        void mouseMoved(int x, int y);

        /**
         * @brief Handles mouse press events.
         * @param x The x-coordinate of the mouse.
         * @param y The y-coordinate of the mouse.
         * @param button The mouse button that was pressed.
         */
        void mousePressed(int x, int y, int button);
};