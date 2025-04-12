#include "player.h"
#include  "level.h"

Player players[MAX_PLAYERS];
int activePlayerIndex = 0;


Player* currentPlayer() {
    return &players[activePlayerIndex];
}


static int _onGroundCheck(Player* p) {
    if (getTileBelow(p->x, p->y) == GROUND) {
        p->y = (p->y / SPRITE_SIZE) * SPRITE_SIZE; // make sure y is multiple of 16, to snap the player's Y position to the nearest ground level
        p->vy = 0;
        return 1;
    }
    return 0;
}


void initPlayer(int index, int x, int y) {
    players[index].x = x;
    players[index].y = y;
    players[index].vx = 0;
    players[index].vy = 0;
    players[index].spriteN = index; 
    players[index].spriteIndex = P_IDLE; // TODO: diff sprite for diff player_N(?)
    players[index].onGround = _onGroundCheck(&players[index]); // check if player is on ground at start
}

void switchPlayer() {
    playerStop(); // stop current player before switching
    activePlayerIndex = (activePlayerIndex + 1) % MAX_PLAYERS;
}

void playerMoveRight() {
    Player* p = currentPlayer();
    p->vx = MOVE_INTERVAL;
    p->spriteIndex = P_R_MOVE;
}

void playerMoveLeft() {
    Player* p = currentPlayer();
    p->vx = -MOVE_INTERVAL;
    p->spriteIndex = P_L_MOVE;
}

void playerStop() {
    Player* p = currentPlayer();
    p->vx = 0;
    p->spriteIndex = P_IDLE;
}


void playerJump() {
    Player* p = currentPlayer();
    if (p->onGround) { // only jump if on ground
        p->vy = JUMP_STRENGTH;
        p->onGround = 0;
    }
}


static int _canMoveRight(Player* p) {
    return getTileRight(p->x, p->y) != GROUND;
}

static int _canMoveLeft(Player* p) {
    return getTileLeft(p->x, p->y) != GROUND;
}


static void _limitWithinScreenBoundaries(Player* p) {
    if (p->x < 0) 
        p->x = 0;
    else if (p->x > SCREEN_WIDTH - SPRITE_SIZE)
        p->x = SCREEN_WIDTH - SPRITE_SIZE;
    if (p->y < 0) 
        p->y = 0;
    else if (p->y > SCREEN_HEIGHT - SPRITE_SIZE) 
        p->y = SCREEN_HEIGHT - SPRITE_SIZE;
}


void updatePlayers() {
    for (int i = 0; i < MAX_PLAYERS; i++) {
        Player* p = &players[i];

        // horizontal movement
        if ((p->vx > 0 && _canMoveRight(p)) || (p->vx < 0 && _canMoveLeft(p))) {
            p->x += p->vx;
        }

        // vertical movement
        if (p->vy < 0 && getTileAbove(p->x, p->y) == GROUND) { // jumping and hitting the ceiling
            p->y = ((p->y / SPRITE_SIZE)) * SPRITE_SIZE; // snap to just below the ceiling
				p->vy = 0;
        } else {
				p->y += p->vy;
		  }
        if (p->onGround == 0) { // apply gravity if not on the ground
            p->vy += GRAVITY;
        }

        p->onGround = _onGroundCheck(p);
        _limitWithinScreenBoundaries(p);
    }
}

