#ifndef PLAYER_H
#define PLAYER_H

#include "sprites.h"

typedef struct {
    int x, y;          // position
    int vx, vy;        // velocity
    int spriteIndex;   // sprite to draw
    int spriteN;       // to move the sprite (redraw with same N)
    int onGround;      // 1 if on ground, 0 if in the air
} Player;

Player player; // currently only support one player

void initPlayer(int x, int y);
void playerMoveRight();
void playerMoveLeft();
void playerJump();
void playerStop();
void updatePlayer();

#endif