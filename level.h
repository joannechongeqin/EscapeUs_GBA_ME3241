#ifndef LEVEL_h
#define LEVEL_h

#include "mygbalib.h"

#define SPRITE_SIZE     16
#define TILES_X         (SCREEN_WIDTH / SPRITE_SIZE)  // 15
#define TILES_Y         (SCREEN_HEIGHT / SPRITE_SIZE) // 10

#define EMPTY   0
#define GROUND  1
#define PLAYER  2
#define KEY     3
#define GOAL    4
#define BOMB    5

int level_0[TILES_Y][TILES_X];

void drawLevel(int level);

void hideLevel();

int getTileAt(int x, int y);

#endif