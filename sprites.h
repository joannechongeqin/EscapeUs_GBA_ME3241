#ifndef SPRITES_H
#define SPRITES_H

#include "gba.h"

#define NCOLS 20

// RGB palette used for sprites. The sprites defined below use the index of the color in the palette (so black = 0, white = 1, ...)
// Declare as extern to avoid multiple definitions.
extern int palette[];

// Declare the sprites array as extern to avoid multiple definitions.
extern u16 sprites[];

#define SPRITE_SIZE       16  // size of each sprite in pixels (16x16)

#define TITLE_LENGTH      2 // <title> in menu
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
#define BLANK   0       // empty sprite (mainly for delSprite())

#define P_IDLE   1      // player idle facing FRONT
#define P_R_MOVE 2      // player moving RIGHT
#define P_L_MOVE 3      // player moving LEFT
#define ARROW_   4      // arrow sprite (to indicate current active player)

#define GROUND_  5      // ground sprite (for level)
#define KEY_     6      // key sprite (for level)
#define GOAL_    7      // goal sprite (for level)
#define BOMB_    8      // bomb sprite (for level)

#define LETTER_S 9
#define LETTER_T 10
#define LETTER_A 11
#define LETTER_R 12
#define LETTER_G 13
#define LETTER_M 14
#define LETTER_E 15
#define LETTER_Y 16
#define LETTER_O 17
#define LETTER_U 18
#define LETTER_W 19
#define LETTER_I 20
#define LETTER_N 21
#define LETTER_L 22
#define LETTER_EXCLAMATION 23
#endif
