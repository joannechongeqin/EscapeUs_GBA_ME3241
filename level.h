#ifndef LEVEL_h
#define LEVEL_h

#include "mygbalib.h"

#define MAX_LEVELS      2
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
#define MONSTER 7


typedef struct {
    int spriteN;    // to move the sprite (redraw with same N)
    int x, y;       // monster's position
    int vx;         // horizontal speed (positive moves right, negative moves left)
    int leftBound;  // leftmost position the monster can move
    int rightBound; // rightmost position the monster can move
} Monster;
Monster monster;
extern Monster monsters[MAX_MONSTERS];  // array to store monsters for a given level
extern int numMonsters; // number of monsters in the current level

void updateMonsters();
void drawMonsters();

void drawPlayers();

void drawLevel(int level);
void hideLevel();

int getTileAt(int x, int y);

int checkRightIs(int x, int y, int tile_type);
int checkLeftIs(int x, int y, int tile_type);
int checkBelowIs(int x, int y, int tile_type);

#endif