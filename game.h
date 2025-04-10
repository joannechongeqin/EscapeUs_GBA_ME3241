// VBA controls: https://visualboyadvance.org/default-controls/

#ifndef GAME_H
#define GAME_H

#include "mygbalib.h"
#include "menu.h"

enum GameState { MAIN_MENU, GAMEPLAY, WIN, LOSS } gameState;


#define INPUT                      (KEY_MASK & (~REG_KEYS))
void checkbutton(void)
{
	// Gift function to show you how a function that can be called upon button interrupt to detect which button was pressed and run a specific function for each button could look like. You would have to define each buttonA/buttonB/... function yourself.
    u16 buttons = INPUT;

    if ((buttons & KEY_START) == KEY_START && gameState == MAIN_MENU) // "ENTER" on keyboard
    {
        
        initGame();
        gameState = GAMEPLAY;
    }

    if (gameState == GAMEPLAY) {
        if ((buttons & KEY_RIGHT) == KEY_RIGHT)
        {
            playerMoveRight();
        }
        if ((buttons & KEY_LEFT) == KEY_LEFT)
        {
            playerMoveLeft();
        }
        if ((buttons & KEY_UP) == KEY_UP)
        {
            playerJump();
        }
        if ((buttons & KEY_RIGHT) == 0 && (buttons & KEY_LEFT) == 0)
        {
            playerStop();
        }
    }

    updatePlayer();
    drawSprite(player.spriteIndex, player.spriteN, player.x, player.y);

}

#endif