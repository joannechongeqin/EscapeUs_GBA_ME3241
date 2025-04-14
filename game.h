// VBA controls: https://visualboyadvance.org/default-controls/

#ifndef GAME_H
#define GAME_H

#include "menu.h"

enum GameState { MAIN_MENU, GAMEPLAY, END } gameState;

int gotKey = FALSE;
int keyWithPlayer = 0; // player that has the key
#define KEY_GRAB_DISTANCE 16 // distance to grab key (in pixels)

void updatePlayerState() {
    updatePlayers();
    for (int i = 0; i < NUM_PLAYERS; i++) {
        drawSprite(players[i].spriteIndex, players[i].spriteN, players[i].x, players[i].y);
    } 

    // draw arrow above current active player
    drawSprite(ARROW_, ARROW_SPRITE_N, players[activePlayerIndex].x, players[activePlayerIndex].y - SPRITE_SIZE); 
}


void updateGameState() {
    for (int i = 0; i < NUM_PLAYERS; i++) {
        // LOSE
        if (getTileBelow(players[i].x, players[i].y) == INVALID || // fall off ground
                getTileAt(players[i].x, players[i].y) == BOMB) { // touch bomb 
            gameState = END;
            showEndingScreen(0);
        }
    }

    if (gotKey) { // if already reached key, render the key it near the player that has it
        if (keyWithPlayer != activePlayerIndex) {
            int dx = players[activePlayerIndex].x - players[keyWithPlayer].x;
            int dy = players[activePlayerIndex].y - players[keyWithPlayer].y;
            if (dx * dx + dy * dy <= KEY_GRAB_DISTANCE * KEY_GRAB_DISTANCE)
                keyWithPlayer = activePlayerIndex; // Transfer key
        }
        drawSprite(KEY_, KEY_SPRITE_N, players[keyWithPlayer].x - SPRITE_SIZE / 2, players[keyWithPlayer].y - SPRITE_SIZE);

        // WIN
        if (getTileAt(players[activePlayerIndex].x, players[activePlayerIndex].y) == GOAL) { // touch goal
            gameState = END;
            showEndingScreen(1);
        }
    }
    else if (getTileAt(players[activePlayerIndex].x, players[activePlayerIndex].y) == KEY) { // no key and first time touch key, pick up key
            gotKey = TRUE;
            keyWithPlayer = activePlayerIndex; // player that has the key
    }
}


#define COOLDOWN_TIME 10 // cooldown time in frames (for button press)
int START_cooldown = 0;
int KEY_B_cooldown = 0;
void updateCooldown() {
    if (START_cooldown > 0) START_cooldown--;
    if (KEY_B_cooldown > 0) KEY_B_cooldown--;
}


#define INPUT                      (KEY_MASK & (~REG_KEYS))
void checkbutton(void)
{
	// Gift function to show you how a function that can be called upon button interrupt to detect which button was pressed and run a specific function for each button could look like. You would have to define each buttonA/buttonB/... function yourself.
    u16 buttons = INPUT;

    updateCooldown();

    if ((buttons & KEY_START) == KEY_START && START_cooldown == 0) {
        START_cooldown = COOLDOWN_TIME;
        if (gameState == END) {
            clearScreen();
            showMainMenu();
            gameState = MAIN_MENU;
        }
        else if (gameState == MAIN_MENU) {
            clearScreen();
            drawLevel(0);
            activePlayerIndex = 0; // reset active player index to 0 (first player)
            gotKey = FALSE; // reset key state
            gameState = GAMEPLAY;
        }
    }

    if (gameState == GAMEPLAY) {
        // switch player
        if ((buttons & KEY_B) == KEY_B && KEY_B_cooldown == 0) { // "Z" on keyboard
            KEY_B_cooldown = COOLDOWN_TIME;
            switchPlayer();
        }
        
        // move player
        if ((buttons & KEY_RIGHT) == KEY_RIGHT) {
            playerMoveRight();
        }
        if ((buttons & KEY_LEFT) == KEY_LEFT) {
            playerMoveLeft();
        }
        if ((buttons & KEY_UP) == KEY_UP || (buttons & KEY_A) == KEY_A) {
            playerJump();
        }
        if ((buttons & KEY_RIGHT) == 0 && (buttons & KEY_LEFT) == 0) {
            playerStop();
        }

        updatePlayerState();
        updateGameState();
    }
}

#endif
