// VBA controls: https://visualboyadvance.org/default-controls/

#ifndef GAME_H
#define GAME_H

#include "menu.h"

enum GameState { MAIN_MENU, GAMEPLAY, END, WIN_LEVEL1 } gameState;

int gotKey = FALSE;
int keyWithPlayer = 0; // player that has the key
#define KEY_GRAB_DISTANCE 16 // distance to grab key from other player (in pixels)

void updatePlayerState() {
    updatePlayers();
    for (int i = 0; i < NUM_PLAYERS; i++) {
        drawSprite(players[i].spriteIndex, players[i].spriteN, players[i].x, players[i].y);
    } 

    // draw arrow above current active player
    drawSprite(ARROW_, ARROW_SPRITE_N, players[activePlayerIndex].x, players[activePlayerIndex].y - SPRITE_SIZE); 
}


#define TOUCH_BOMB_TOLERANCE 6

void updateGameState() {
    for (int i = 0; i < NUM_PLAYERS; i++) {
        // LOSE
        if (getTileBelowCenter(players[i].x, players[i].y) == INVALID || // fall off ground
            getTileAt(players[i].x+TOUCH_BOMB_TOLERANCE, players[i].y) == BOMB || // check if leftmost of player touch bomb (with some tolerance)
            getTileAt(players[i].x+SPRITE_SIZE-1-TOUCH_BOMB_TOLERANCE, players[i].y) == BOMB) {  // check if rightmost of player touch bomb (with some tolerance)
                gameState = END;
                if (gameState == WIN_LEVEL1) {
                    gameState = WIN_LEVEL1; // restart level 2 (TODO: IF WANT EVIL JUST RESTART FROM LEVEL 1 HOHO. i doing this for now cuz i lazy to restart for debugging)
                } else {
                    gameState = END; // go to main menu
                }
                showEndingScreen(0);
        }
    }

    if (gotKey) { // if already reached key, render the key near the player that has it
        if (keyWithPlayer != activePlayerIndex) {
            int dx = players[activePlayerIndex].x - players[keyWithPlayer].x;
            int dy = players[activePlayerIndex].y - players[keyWithPlayer].y;
            if (dx * dx + dy * dy <= KEY_GRAB_DISTANCE * KEY_GRAB_DISTANCE)
                keyWithPlayer = activePlayerIndex; // transfer key
        }
        drawSprite(KEY_, KEY_SPRITE_N, players[keyWithPlayer].x - SPRITE_SIZE / 2, players[keyWithPlayer].y - SPRITE_SIZE);

        // WIN
        if (getTileAt(players[activePlayerIndex].x, players[activePlayerIndex].y) == GOAL) { // touch goal
            
            if (gameState == WIN_LEVEL1) {
                gameState = END;
            } else {
                gameState = WIN_LEVEL1; // go to next level
            }
            showEndingScreen(1);
        }
    }
    else if (getTileAt(players[activePlayerIndex].x, players[activePlayerIndex].y) == KEY) { // no key and first time touch key, pick up key
            gotKey = TRUE;
            keyWithPlayer = activePlayerIndex;
    }
}

// cooldown to prevent a single button press from being registered multiple times
#define COOLDOWN_TIME 10 // cooldown time in frames (for button press)
int START_cooldown = 0;
int KEY_A_cooldown = 0;
int KEY_B_cooldown = 0;
static void updateCooldown() {
    if (START_cooldown > 0) START_cooldown--;
    if (KEY_A_cooldown > 0) KEY_A_cooldown--;
    if (KEY_B_cooldown > 0) KEY_B_cooldown--;}

static int keyPressedWithCooldown(u16 buttons, int key, int* cooldownVar) {
    if ((buttons & key) == key && *cooldownVar == 0) {
        *cooldownVar = COOLDOWN_TIME;
        return 1;
    }
    return 0;
}

static void startGame(int level) {
    clearScreen();
    drawLevel(level);
    activePlayerIndex = 0;  // reset active player index to 0 (first player)
    gotKey = FALSE;         // reset key state
    gameState = GAMEPLAY;
}

#define INPUT                      (KEY_MASK & (~REG_KEYS))
void checkbutton(void)
{
	// Gift function to show you how a function that can be called upon button interrupt to detect which button was pressed and run a specific function for each button could look like. You would have to define each buttonA/buttonB/... function yourself.
    u16 buttons = INPUT;

    updateCooldown();

    int startPressed = keyPressedWithCooldown(buttons, KEY_START, &START_cooldown);
    int aPressed     = keyPressedWithCooldown(buttons, KEY_A, &KEY_A_cooldown);

    if (startPressed || aPressed) {
        if (gameState == MAIN_MENU) { // start level 1 from main menu
            startGame(0);
        } else if (gameState == WIN_LEVEL1) { // start level 2 after winning level 1
            startGame(1);
        }
        else if (gameState == END) { // return to main menu after game end
            clearScreen();
            showMainMenu();
            gameState = MAIN_MENU;
        }
    }

    if (gameState == GAMEPLAY) {
        // switch player
        if (keyPressedWithCooldown(buttons, KEY_B, &KEY_B_cooldown)) { // "Z" on keyboard
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
            playerStop(); // stop if no horizontal movement keys are held
        }

        updatePlayerState();
        updateGameState();
    }
}

#endif
