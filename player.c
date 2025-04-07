#include "player.h"

#define PLAYER_SPRITE_N     0   // unique N to draw sprite on screen
#define PLAYER_SPRITE_WIDTH 16
#define MOVE_INTERVAL       2   // number of pixel to move per step
#define GRAVITY             1   // gravity force pulling the player down
#define JUMP_STRENGTH       -10 // initial jump velocity


void initPlayer(int x, int y) {
    player.x = x;
    player.y = y;
    player.vx = 0;
    player.vy = 0;
    player.spriteIndex = P_R_IDLE;
    player.spriteN = PLAYER_SPRITE_N;
    player.onGround = 1;
}


void playerMoveRight() {
    player.vx = MOVE_INTERVAL;
    player.spriteIndex = P_R_MOVE;
}


void playerMoveLeft() {
    player.vx = - MOVE_INTERVAL;
    player.spriteIndex = P_L_MOVE;
}


void playerStop() {
    player.vx = 0;
    player.spriteIndex = P_R_IDLE;
}


void playerJump() {
    if (player.onGround) { // Only jump if on ground
        player.vy = JUMP_STRENGTH;
        player.onGround = 0;
    }
}


int onGroundCheck() {
    // TODO: Once level is created, i think this should be returned by the level code(?) (which knows where is ground)
    if (player.y == 120) { // assume 120 for ground level for now
        player.vy = 0;
       return 1;
    }
    return 0;
}


void updatePlayer() {
    if (!player.onGround) {
        player.vy += GRAVITY;
    }

    player.x += player.vx;
    player.y += player.vy;

    // boundary checks
    if (player.x < 0)
        player.x = 0;
    else if (player.x > (240 - PLAYER_SPRITE_WIDTH))
        player.x = 240 - PLAYER_SPRITE_WIDTH;

    player.onGround = onGroundCheck();
}