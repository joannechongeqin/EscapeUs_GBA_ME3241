#include "player.h"
#include  "level.h"

Player players[NUM_PLAYERS];
int activePlayerIndex = 0;


Player* currentPlayer() {
    return &players[activePlayerIndex];
}


static int _isLandableTile(int tile) {
    // can land on ground or other players
    return tile == GROUND  || 
            (activePlayerIndex != PLAYER1 && tile == PLAYER1) || 
            (activePlayerIndex != PLAYER2 && tile == PLAYER2);
}


static int _onGroundCheck(Player* p) {
    if (_isLandableTile(getTileBelow(p->x, p->y))) {
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
    activePlayerIndex = (activePlayerIndex + 1) % NUM_PLAYERS;
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


static int _isWalkableTile(int tile) {
    return tile == EMPTY || tile == GOAL || tile == KEY || tile == BOMB;
}

static int _canMoveRight(Player* p) {
    return _isWalkableTile(getTileRight(p->x, p->y));
}

static int _canMoveLeft(Player* p) {
    return _isWalkableTile(getTileLeft(p->x, p->y));
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
    for (int i = 0; i < NUM_PLAYERS; i++) {
        Player* p = &players[i];

        // horizontal movement
        if (p->vx > 0) { // moving right
            if (_canMoveRight(p)) {
                p->x += p->vx;
            } else {
                // snap to just before hitting wall on the right
                p->x = (p->x / SPRITE_SIZE) * SPRITE_SIZE;
            }
        } else if (p->vx < 0) { // moving left
            if (_canMoveLeft(p)) {
                p->x += p->vx;
            } else {
                // Snap to just before hitting wall on the left
                p->x = ((p->x + SPRITE_SIZE - 1) / SPRITE_SIZE) * SPRITE_SIZE;
            }
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

