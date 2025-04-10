#include "player.h"
#include  "level.h"

void initPlayer(int x, int y) {
    player.x = x;
    player.y = y;
    player.vx = 0;
    player.vy = 0;
    player.spriteIndex = P_IDLE;
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
    player.spriteIndex = P_IDLE;
}


void playerJump() {
    if (player.onGround) { // Only jump if on ground
        player.vy = JUMP_STRENGTH;
        player.onGround = 0;
    }
}


int _onGroundCheck() {
    if (getTileBelow(player.x, player.y) == GROUND) {
        player.y = (player.y / SPRITE_SIZE) * SPRITE_SIZE; // make sure y is multiple of 16, to snap the player's Y position to the nearest ground level
        player.vy = 0;
        return TRUE;
    }
    return FALSE;
}


int _canMoveRight() {
    return getTileRight(player.x, player.y) != GROUND;
}

int _canMoveLeft() {
    return getTileLeft(player.x, player.y) != GROUND;
}


void _limitWithinScreenBoundaries() {
    // boundary checks
    if (player.x < 0)
        player.x = 0;
    else if (player.x > SCREEN_WIDTH - SPRITE_SIZE)
        player.x = SCREEN_WIDTH - SPRITE_SIZE;
    if (player.y < 0)
        player.y = 0;
    else if (player.y > SCREEN_HEIGHT - SPRITE_SIZE)
        player.y = SCREEN_HEIGHT - SPRITE_SIZE;
}


void updatePlayer() {

    // horizontal movement
    if ((player.vx > 0 && _canMoveRight()) || // moving right
        (player.vx < 0 && _canMoveLeft())) {  // moving left
        player.x += player.vx;
    } 

    // vertical movement
    player.y += player.vy;
    if (player.onGround == FALSE) { // apply gravity if not on the ground
        player.vy += GRAVITY;
    }
    player.onGround = _onGroundCheck();

    _limitWithinScreenBoundaries();
}
