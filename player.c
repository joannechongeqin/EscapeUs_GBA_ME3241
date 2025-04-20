#include "player.h"
#include  "level.h"

Player players[NUM_PLAYERS];
int activePlayerIndex = 0;


Player* currentPlayer() {
    return &players[activePlayerIndex];
}


static int _isLandableTile(int tile) {
    // can land on ground or other players
    return tile == GROUND;
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
    if (_isLandableTile(getTileBelowBottomLeft(p->x, p->y)) || _isLandableTile(getTileBelowBottomRight(p->x, p->y))) {
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


static int _canJump(Player* p) {
    return p->onGround;
}

void playerJump() {
    Player* p = currentPlayer();
    if (_canJump(p)) { // only jump if on ground
        p->vy = JUMP_STRENGTH;
        p->onGround = 0;
    }
}

static int _canMoveRight(Player* p) {
    for (int i = 0; i < NUM_PLAYERS; i++) {
        if (i != activePlayerIndex) {
            Player* otherPlayer = &players[i];
            // check if the other player is in the way
            if (p->x + SPRITE_SIZE == otherPlayer->x && p->y == otherPlayer->y) {
                return FALSE; // cannot move right, other player is in the way
            }
        }
    }
    return getTileRightTop(p->x, p->y) != GROUND && getTileRightBottom(p->x, p->y) != GROUND;
}

static int _canMoveLeft(Player* p) {
    for (int i = 0; i < NUM_PLAYERS; i++) {
        if (i != activePlayerIndex) {
            Player* otherPlayer = &players[i];
            // check if the other player is in the way
            if (p->x - SPRITE_SIZE == otherPlayer->x && p->y == otherPlayer->y) {
                return FALSE; // cannot move left, other player is in the way
            }
        }
    }
    return getTileLeftTop(p->x, p->y) != GROUND && getTileLeftBottom(p->x, p->y) != GROUND;
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

