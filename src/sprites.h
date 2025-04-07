#ifndef SPRITES_H
#define SPRITES_H

#include "gba.h"

#define NCOLS 20

// RGB palette used for sprites. The sprites defined below use the index of the color in the palette (so black = 0, white = 1, ...)
// Declare as extern to avoid multiple definitions.
extern int palette[];

// Declare the sprites array as extern to avoid multiple definitions.
extern u16 sprites[];

// Define sprite constants for easier reference
#define P_R_IDLE 0 // player idle position (looking RIGHT)
// #define P_L_IDLE 1 // player idle position (looking LEFT)
#define P_R_MOVE 2 // player moving RIGHT
#define P_L_MOVE 3 // player moving LEFT

#endif
