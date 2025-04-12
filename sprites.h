#ifndef SPRITES_H
#define SPRITES_H

#include "gba.h"

#define NCOLS 20
#define MAX_SPRITE_N 50

// RGB palette used for sprites. The sprites defined below use the index of the color in the palette (so black = 0, white = 1, ...)
// Declare as extern to avoid multiple definitions.
extern int palette[];

// Declare the sprites array as extern to avoid multiple definitions.
extern u16 sprites[];

#define SPRITE_SIZE       16  // size of each sprite in pixels (16x16)

#define TITLE_LENGTH      4 // <title> in menu
#define START_LENGTH      5 // "START" button in menu
#define ENDING_LENGTH     7 // "YOU WIN!" or "YOU LOSE" in ending screen

#define PLAYER1_N         0
#define PLAYER2_N         1
#define ARROW_SPRITE_N    2
#define KEY_SPRITE_N      3

#define TITLE_SPRITE_N    4
#define START_SPRITE_N    TITLE_SPRITE_N + TITLE_LENGTH
#define ENDING_SPRITE_N   START_SPRITE_N + START_LENGTH
#define LEVEL_SPRITE_N    ENDING_SPRITE_N + ENDING_LENGTH   // starting of the unique N to draw elements (ground, key, door etc) for level on screen (basically each element/tile will have its own N)


// Define sprite constants here for easier reference
// !!! implementation in sprites.c !!!
#define BLANK   0        // empty sprite (mainly for delSprite())

#define START_S 1      // for start button in menu
#define START_T 2      // for start button in menu
#define START_A 3      // for start button in menu
#define START_R 4      // for start button in menu

#define TITLE_G 5      // for title in menu
#define TITLE_A 6      // for title in menu
#define TITLE_M 7      // for title in menu
#define TITLE_E 8      // for title in menu

#define P_IDLE 9        // player idle facing FRONT
#define P_R_MOVE 10     // player moving RIGHT
#define P_L_MOVE 11     // player moving LEFT

#define GROUND_SPRITE 12 // ground sprite (for level)
#define KEY_SPRITE 13    // key sprite (for level)
#define GOAL_SPRITE 14   // goal sprite (for level)
#define BOMB_SPRITE 15   // bomb sprite (for level)

#define ARROW_SPRITE 16   // arrow sprite (to indicate current active player)

#endif
