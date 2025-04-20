#ifndef PLAYER_H
#define PLAYER_H

#include "sprites.h"

#define MOVE_INTERVAL       2   // number of pixel to move per step
#define GRAVITY             1   // gravity force pulling the player down
#define JUMP_STRENGTH       -8  // initial jump velocity
#define NUM_PLAYERS         2   // NOTE: must have 2 players for now (some functions are hardcoded for 2 players)

typedef struct {
    int x, y;          // position
    int vx, vy;        // velocity
    int spriteIndex;   // sprite to draw
    int spriteN;       // to move the sprite (redraw with same N)
    int onGround;      // 1 if on ground, 0 if in the air
} Player;

extern Player players[NUM_PLAYERS];
extern int activePlayerIndex;

void initPlayer(int index, int x, int y);
Player* currentPlayer();
void switchPlayer();

void playerMoveRight();
void playerMoveLeft();
void playerJump();
void playerStop();
void updatePlayers();

#endif
