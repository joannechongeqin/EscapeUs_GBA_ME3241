// VBA controls: https://visualboyadvance.org/default-controls/

#ifndef GAME_H
#define GAME_H

#include "menu.h"

enum GameState {
    MAIN_MENU,
    LEVEL1,
    LEVEL2,
    LEVEL1_COMPLETE,
    LEVEL2_COMPLETE,
    GAME_OVER
} gameState;


void updateMovingSpritesState() {
    updatePlayers();
    drawPlayers();

    // draw arrow above current active player
    drawSprite(ARROW_, ARROW_SPRITE_N, players[activePlayerIndex].x, players[activePlayerIndex].y - SPRITE_SIZE); 

    updateMonsters();
    drawMonsters();
}


int gotKey = FALSE;
int keyWithPlayer = 0;          // player that has the key
#define KEY_GRAB_DISTANCE 16    // distance to grab key from other player (in pixels)
#define LOSE_TOLERANCE 4        // tolerance to check if player touch bomb or monster (in pixels)


void updateGameState() {
    for (int i = 0; i < NUM_PLAYERS; i++) {
        int playerLeft = players[i].x; int playerRight = players[i].x + SPRITE_SIZE - 1; 

        int touch_monster = FALSE;
        for (int j = 0; j < numMonsters; j++) {
            int monsterLeft = monsters[j].x; int monsterRight = monsters[j].x + SPRITE_SIZE - 1;
            
            int leftDiff = playerRight - monsterLeft;
            int rightDiff = monsterRight - playerLeft;
            if (players[i].y == monsters[j].y && 
                ((leftDiff >= 0 && leftDiff <= SPRITE_SIZE - LOSE_TOLERANCE) || 
                 (rightDiff >= 0 && rightDiff <=  SPRITE_SIZE - LOSE_TOLERANCE))) {
                touch_monster = TRUE;
                break;
            }
        }
        
        // LOSE
        if (touch_monster || // touch monster
            checkBelowIs(players[i].x, players[i].y, INVALID) || // fall off ground
            getTileAt(playerLeft  + LOSE_TOLERANCE, players[i].y) == BOMB || // check if leftmost of player touch bomb (with some tolerance)
            getTileAt(playerRight - LOSE_TOLERANCE, players[i].y) == BOMB) {  // check if rightmost of player touch bomb (with some tolerance)
                gameState = GAME_OVER;
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
            if (gameState == LEVEL1) {
                gameState = LEVEL1_COMPLETE;
            } else if (gameState == LEVEL2) {
                gameState = LEVEL2_COMPLETE;
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
#define COOLDOWN_TIME 5 // cooldown time in frames (for button press)
int START_cooldown = 0;
int KEY_A_cooldown = 0;
int KEY_B_cooldown = 0;
static void updateCooldown() {
    if (START_cooldown > 0) START_cooldown--;
    if (KEY_A_cooldown > 0) KEY_A_cooldown--;
    if (KEY_B_cooldown > 0) KEY_B_cooldown--;
}
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
    if (level == 0)
        gameState = LEVEL1;
    else if (level == 1)
        gameState = LEVEL2;
}


#define INPUT                      (KEY_MASK & (~REG_KEYS))
void checkbutton(void) {
	// Gift function to show you how a function that can be called upon button interrupt to detect which button was pressed and run a specific function for each button could look like. You would have to define each buttonA/buttonB/... function yourself.
    u16 buttons = INPUT;

    updateCooldown();

    int startPressed = keyPressedWithCooldown(buttons, KEY_START, &START_cooldown); // "ENTER" on keyboard
    int aPressed     = keyPressedWithCooldown(buttons, KEY_A, &KEY_A_cooldown);     // "X" on keyboard

    if (startPressed || aPressed) {
        // start level 1 from main menu
        if (gameState == MAIN_MENU) {
            startGame(0);
        } 
        // complete level 1, start level 2
        if (gameState == LEVEL1_COMPLETE) {
            startGame(1); 
            gameState = LEVEL2;
        }
        // return to main menu after game end
        else if (gameState == GAME_OVER || gameState == LEVEL2_COMPLETE) {
            clearScreen();
            showMainMenu();
            gameState = MAIN_MENU;
        }
    }

    if (gameState == LEVEL1 || gameState == LEVEL2) {
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

        updateMovingSpritesState();
        updateGameState();
    }
}

#endif
