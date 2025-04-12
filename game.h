// VBA controls: https://visualboyadvance.org/default-controls/

#ifndef GAME_H
#define GAME_H

#include "menu.h"

enum GameState { MAIN_MENU, GAMEPLAY, END } gameState;

void updatePlayerState() {
    updatePlayers();
    for (int i = 0; i < MAX_PLAYERS; i++) {
        drawSprite(players[i].spriteIndex, players[i].spriteN, players[i].x, players[i].y);
    }
    drawSprite(ARROW_, ARROW_SPRITE_N, players[activePlayerIndex].x, players[activePlayerIndex].y - SPRITE_SIZE); // draw arrow above current active player
}


void updateGameState() {
    for (int i = 0; i < MAX_PLAYERS; i++) {
        // LOSE
        if (getTileBelow(players[i].x, players[i].y) == INVALID || // fall off ground
                getTileAt(players[i].x, players[i].y) == BOMB) { // touch bomb 
            gameState = END;
            showEndingScreen(0);
        }
    }
}


#define INPUT                      (KEY_MASK & (~REG_KEYS))
void checkbutton(void)
{
	// Gift function to show you how a function that can be called upon button interrupt to detect which button was pressed and run a specific function for each button could look like. You would have to define each buttonA/buttonB/... function yourself.
    u16 buttons = INPUT;

    if ((buttons & KEY_SELECT) == KEY_SELECT && (gameState == END)) { // "BACKSPACE" on keyboard
        clearScreen();
        showMainMenu();
        gameState = MAIN_MENU;
    }

    if ((buttons & KEY_START) == KEY_START && gameState == MAIN_MENU) { // "ENTER" on keyboard
        clearScreen();
        drawLevel(0);
        gameState = GAMEPLAY;
    }

    if (gameState == GAMEPLAY) {
        // switch player
        if ((buttons & KEY_A) == KEY_A) { // "Z" on keyboard
            switchPlayer();
        }
        
        // move player
        if ((buttons & KEY_RIGHT) == KEY_RIGHT) {
            playerMoveRight();
        }
        if ((buttons & KEY_LEFT) == KEY_LEFT) {
            playerMoveLeft();
        }
        if ((buttons & KEY_UP) == KEY_UP) {
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
