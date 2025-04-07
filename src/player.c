#include "player.h"

#define STEP_INTERVAL = 4; // how many pixel to move per step

void initPlayer(void) {
    player.x = 100;
    player.y = 100;
    player.vx = 0;
    player.vy = 0;
    player.spriteIndex = P_R_IDLE;
    player.onGround = 1;
}