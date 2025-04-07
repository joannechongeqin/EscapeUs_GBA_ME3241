#ifndef SPRITES_H
#define SPRITES_H

#include "gba.h"

#define NCOLS 20

// RGB palette used for sprites. The sprites defined below use the index of the color in the palette (so black = 0, white = 1, ...)
// Declare as extern to avoid multiple definitions.
extern int palette[];

// Declare the sprites array as extern to avoid multiple definitions.
extern u16 sprites[];

#define TITLE_LENGTH 2
#define START_LENGTH 1

// Define sprite constants for easier reference
// !!! implementation in sprites.c !!!
#define EMPTY 0        // empty sprite (mainly for delSprite())

#define START_S 1      // for start button in menu
#define START_T 2      // for start button in menu
#define START_A 3      // for start button in menu
#define START_R 4      // for start button in menu

#define TITLE_G 5      // for title in menu
#define TITLE_A 6      // for title in menu
#define TITLE_M 7      // for title in menu
#define TITLE_E 8      // for title in menu

#define P_R_IDLE 9      // player idle facing RIGHT
#define P_L_IDLE 10     // player idle facing LEFT
#define P_R_MOVE 11     // player moving RIGHT
#define P_L_MOVE 12     // player moving LEFT

#endif
