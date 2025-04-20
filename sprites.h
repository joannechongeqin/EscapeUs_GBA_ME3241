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
#define LETTER_SIZE       8   // size of each letter in pixels (8x8)
#define LETTER_INTERVAL   16  // interval between letters in pixels

#define TITLE_LENGTH      5     // <title> in menu
#define START_LENGTH1     11    // "PRESS START" button in menu
#define START_LENGTH2     7     // "TO PLAY" in menu
#define ENDING_LENGTH     8     // "YOU WIN!" or "YOU LOSE" in ending screen
#define MAX_MONSTERS      1     // max number of monsters in all the level

#define PLAYER1_N         0
#define PLAYER2_N         1
#define ARROW_SPRITE_N    2
#define KEY_SPRITE_N      3
#define MONSTER_N         4

#define TITLE_SPRITE_N    MONSTER_N + MAX_MONSTERS
#define START_SPRITE_N    TITLE_SPRITE_N + TITLE_LENGTH
#define ENDING_SPRITE_N   START_SPRITE_N + START_LENGTH1 + START_LENGTH2
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
#define MONSTER_ 9      // monster sprite (TODO: can do left right also)

#define LETTER_A 10
#define LETTER_B (LETTER_A + 1)
#define LETTER_C (LETTER_B + 1)
#define LETTER_D (LETTER_C + 1)
#define LETTER_E (LETTER_D + 1)
#define LETTER_F (LETTER_E + 1)
#define LETTER_G (LETTER_F + 1)
#define LETTER_H (LETTER_G + 1)
#define LETTER_I (LETTER_H + 1)
#define LETTER_J (LETTER_I + 1)
#define LETTER_K (LETTER_J + 1)
#define LETTER_L (LETTER_K + 1)
#define LETTER_M (LETTER_L + 1)
#define LETTER_N (LETTER_M + 1)
#define LETTER_O (LETTER_N + 1)
#define LETTER_P (LETTER_O + 1)
#define LETTER_Q (LETTER_P + 1)
#define LETTER_R (LETTER_Q + 1)
#define LETTER_S (LETTER_R + 1)
#define LETTER_T (LETTER_S + 1)
#define LETTER_U (LETTER_T + 1)
#define LETTER_V (LETTER_U + 1)
#define LETTER_W (LETTER_V + 1)
#define LETTER_X (LETTER_W + 1)
#define LETTER_Y (LETTER_X + 1)
#define LETTER_Z (LETTER_Y + 1)
#define LETTER_EXCLAMATION (LETTER_Z + 1)

#endif
