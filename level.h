#ifndef LEVEL_h
#define LEVEL_h

#include "mygbalib.h"

#define SPRITE_SIZE     16
#define TILES_X         (SCREEN_WIDTH / SPRITE_SIZE)  // 15
#define TILES_Y         (SCREEN_HEIGHT / SPRITE_SIZE) // 10

#define INVALID -1
#define EMPTY   0
#define PLAYER1 1
#define PLAYER2 2
#define GROUND  3
#define KEY     4
#define GOAL    5
#define BOMB    6

int level_0[TILES_Y][TILES_X];
int level_sprite_N;

void drawLevel(int level);

void hideLevel();

int getTileAt(int x, int y);
int getTileRight(int x, int y);
int getTileLeft(int x, int y);
int getTileAbove(int x, int y);
int getTileBelow(int x, int y);

#endif