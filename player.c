#include "player.h"
#include  "level.h"

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


int _onGroundCheck() {
    int tileBelow = getTileAt(player.x + 8, player.y + 16);
    if (tileBelow == GROUND) {
        player.y = (player.y / 16) * 16; // make sure y is multiple of 16, to snap the player's Y position to the nearest ground level
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
    else if (player.x > SCREEN_WIDTH - SPRITE_SIZE)
        player.x = SCREEN_WIDTH - SPRITE_SIZE;
    if (player.y < 0)
        player.y = 0;
    else if (player.y > SCREEN_HEIGHT - SPRITE_SIZE)
        player.y = SCREEN_HEIGHT - SPRITE_SIZE;

    player.onGround = _onGroundCheck();
}
