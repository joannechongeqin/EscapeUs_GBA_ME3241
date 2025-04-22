#include "player.h"
#include  "level.h"

Player players[NUM_PLAYERS];
int activePlayerIndex = 0;

Player* currentPlayer() {
    return &players[activePlayerIndex];
}

static int _onGroundCheck(Player* p) {
    // check if landing on another player
    for (int i = 0; i < NUM_PLAYERS; i++) {
        Player* other = &players[i];
        if (other == p) continue; // skip self

        int tolerance = SPRITE_SIZE / 2; // allow some leeway for pixel overlap
        int playerBottom = p->y + SPRITE_SIZE;
        int otherTop = other->y;

        if (
            p->x + SPRITE_SIZE > other->x &&
            p->x < other->x + SPRITE_SIZE && // horizontal overlap
            playerBottom >= otherTop - tolerance &&
            playerBottom <= otherTop + tolerance && // vertical "step"
            p->vy >= 0 // must be falling onto them
        ) {
            p->y = other->y - SPRITE_SIZE; // snap on top of other player
            p->vy = 0;
            return TRUE;
        }
    }
    if (checkBelowIs(p->x, p->y, GROUND)) {
        return TRUE;
    }
    return FALSE; // not on ground or another player
}


void initPlayer(int index, int x, int y) {
    players[index].x = x;
    players[index].y = y;
    players[index].vx = 0;
    players[index].vy = 0;
    players[index].spriteN = index; 
    players[index].spriteIndex = P_IDLE; // TODO: diff sprite for diff player_N(?)
    players[index].onGround = _onGroundCheck(&players[index]); // check if player is on ground at start
    players[index].enteredGoal = FALSE; // not entered goal at start
}

void switchPlayer() {
    playerStop(); // stop current player before switching
    int originalIndex = activePlayerIndex;
    do {
        activePlayerIndex = (activePlayerIndex + 1) % NUM_PLAYERS;
    } while (players[activePlayerIndex].enteredGoal && activePlayerIndex != originalIndex);
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


static int _canJump(Player* p) {
    return p->onGround;
}

static int abs(int x) {
    return (x < 0) ? -x : x;
}   

void playerJump() {
    Player* p = currentPlayer();
    if (_canJump(p)) { // only jump if on ground
        // block jump if another player is directly on top
        for (int i = 0; i < NUM_PLAYERS; i++) {
            if (i == activePlayerIndex) continue; // skip self
            Player* other = &players[i];
            int xOverlap = abs(p->x - other->x) < SPRITE_SIZE - 1;
            int yAbove = p->y == other->y + SPRITE_SIZE;
            if (xOverlap && yAbove) {
                return;
            }
        }

        p->vy = JUMP_STRENGTH;
        p->onGround = 0;
    }
}

#define VERTICAL_CHECK_TOLERANCE 4 

static int _canMoveRight(Player* p) {
    int nextRight = p->x + SPRITE_SIZE + 1;
    int playerTop = p->y; int playerBottom = p->y + SPRITE_SIZE;

    for (int i = 0; i < NUM_PLAYERS; i++) {
        if (i != activePlayerIndex) {
            Player* other = &players[i];
            int otherLeft = other->x; int otherRight = other->x + SPRITE_SIZE;
            int otherTop = other->y;  int otherBottom = other->y + SPRITE_SIZE;
            
            // check horizontal overlap after moving right
            if (nextRight > otherLeft && nextRight - SPRITE_SIZE < otherRight) {
                // check vertical overlap with tolerance
                if (playerBottom > otherTop + VERTICAL_CHECK_TOLERANCE &&
                    playerTop < otherBottom - VERTICAL_CHECK_TOLERANCE) {
                    return FALSE;
                }
            }
        }
    }
    return !checkRightIs(p->x, p->y, GROUND);
}

static int _canMoveLeft(Player* p) {
    int nextLeft = p->x - MOVE_INTERVAL;
    int playerTop = p->y; int playerBottom = p->y + SPRITE_SIZE;

    for (int i = 0; i < NUM_PLAYERS; i++) {
        if (i != activePlayerIndex) {
            Player* other = &players[i];
            int otherLeft = other->x; int otherRight = other->x + SPRITE_SIZE;
            int otherTop = other->y;  int otherBottom = other->y + SPRITE_SIZE;

            // check horizontal overlap after moving left
            if (nextLeft < otherRight && nextLeft + SPRITE_SIZE > otherLeft) {
                // check vertical overlap -> if they overlap by more than MOVE_VERTICAL_CHECK_TOLERANCE pixels vertically
                if (playerBottom > otherTop + VERTICAL_CHECK_TOLERANCE &&
                    playerTop < otherBottom - VERTICAL_CHECK_TOLERANCE) {
                    return FALSE;
                }
            }
        }
    }
    return !checkLeftIs(p->x, p->y, GROUND);
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
        if (p->vx > 0 && _canMoveRight(p)) { // moving right
            p->x += p->vx;
        } else if (p->vx < 0 && _canMoveLeft(p)) { // moving left
            p->x += p->vx;
        }

        // vertical movement
        int hittingCeiling = p->vy < 0 &&
                             (getTileAt(p->x, p->y + p->vy) == GROUND ||
                             getTileAt(p->x + SPRITE_SIZE - 1, p->y + p->vy) == GROUND);
        if (hittingCeiling) { // then snap to just below the ceiling      
            p->y = ((p->y / SPRITE_SIZE)) * SPRITE_SIZE; 
			p->vy = 0;
        } else {
				p->y += p->vy;
		}

        if (_onGroundCheck(p)) {
            if (p->vy >= 0) { // Only snap when falling down
                p->y = (p->y / SPRITE_SIZE) * SPRITE_SIZE;
                p->vy = 0;
                p->onGround = 1;
            }
        } else {
            p->onGround = 0;
            p->vy += GRAVITY;
        }
        
        _limitWithinScreenBoundaries(p);
    }
}

