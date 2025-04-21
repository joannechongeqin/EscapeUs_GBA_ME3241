#include "level.h"
#include "player.h"

int levels[MAX_LEVELS][TILES_Y][TILES_X] = {
    {   // ----- LEVEL 0 -----
        // 0     1       2       3       4       5       6       7       8       9      10      11      12      13      14
        { 0,    0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0    },   // Row 0
        { 0,    0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0    },   // Row 1
        // { 0,    KEY,    0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0    },   // Row 2 // TODO: UNCOMMENT THIS LINE
        { 0,    0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      KEY   },   // Row 2   // TODO: COMMENT THIS LINE (THIS JUST FOR DEBUGGING)
        { 0,    GROUND, 0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0    },   // Row 3
        { 0,    0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      GOAL },   // Row 4
        { 0,    0,      0,      GROUND, 0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      GROUND }, // Row 5
        { 0,    0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      GROUND, GROUND }, // Row 6
        { 0,    0,      0,      0,      0,      0,      PLAYER1,0,      BOMB,   PLAYER2,0,      0,      GROUND, GROUND, GROUND }, // Row 7
        { 0,    0,      0,      0,      0,      0,      GROUND, GROUND, GROUND, GROUND, 0,      GROUND, GROUND, GROUND, GROUND }, // Row 8
        { 0,    0,      0,      0,      0,      0,      GROUND, GROUND, GROUND, GROUND, 0,      GROUND, GROUND, GROUND, GROUND }  // Row 9
    },
    {   // ----- LEVEL 1 -----
        // 0     1       2       3       4       5       6       7       8       9      10      11      12      13      14
        { 0,        0,          0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0       }, // Row 0
        { 0,        0,          0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      KEY     }, // Row 1
        { 0,        0,          0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      GROUND, GROUND, GROUND  }, // Row 2
        { 0,        0,          0,      0,      0,      0,      0,      0,      0,      0, GROUND,      0,      0,      0,      0       }, // Row 3
        { 0,        0,          0,      0,      0,      0,      0,      0, GROUND,      0,      0,      0,      0,      GOAL,   0       }, // Row 4
        { 0,        0,          0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      GROUND, 0       }, // Row 5
        { 0,        0,          0,      0,      0,      0,      0, MONSTER,     0,      0,      0,      0,      0,      0,      0       }, // Row 6 // NOTE: NEED MANUALLY PUT THIS INFO IN initLevelMonsters
        { PLAYER1,  PLAYER2,    0,      0, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND,      0,      0,      0,      GROUND  }, // Row 7
        { GROUND,   GROUND,     0,      0, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND,      0,      0,      GROUND, GROUND  }, // Row 8
        { GROUND,   GROUND,     0,      0, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND,      0,      0,      GROUND, GROUND  }  // Row 9
    } 
};


// --------------- START OF MONSTER ---------------
Monster monsters[MAX_MONSTERS];  // array to store monsters for a given level
int numMonsters; // number of monsters in the current level // TODO: double check if numMonsters < MAX_MONSTERS??

void initMonster(Monster *m, int spriteN, int x, int y, int leftBound, int rightBound, int vx) {
    m->spriteN = spriteN;
    m->x = x;
    m->y = y;
    m->vx = vx;
    m->leftBound = leftBound;
    m->rightBound = rightBound;
}

// NOTE: technically can do many monsters in one level
static void _initLevelMonsters(int level) {
    numMonsters = 0;
    
    // --- level 0  ---
    // no monster

    // --- level 1  ---
    if (level == 1) {
        numMonsters = 1; 
        initMonster(&monsters[0], MONSTER_N, 8*SPRITE_SIZE, 6*SPRITE_SIZE, 4*SPRITE_SIZE, 10*SPRITE_SIZE, 1);
    }
}

static void _updateMonster(Monster *m) {
    m->x += m->vx; 
    if (m->x <= m->leftBound || m->x >= m->rightBound) { // when monster hits left or right bounds
        m->vx = -m->vx; // reverse direction
    }
}

// update all monsters in the current level
void updateMonsters() {
    for (int i = 0; i < numMonsters; i++) {
        _updateMonster(&monsters[i]);
    }
}

// draw all monsters
void drawMonsters() {
    for (int i = 0; i < numMonsters; i++) {
        drawSprite(MONSTER_, monsters[i].spriteN, monsters[i].x, monsters[i].y);
    }
}

// --------------- END OF MONSTER ---------------


void drawPlayers() {
    for (int i = 0; i < NUM_PLAYERS; i++) {
        drawSprite(players[i].spriteIndex, players[i].spriteN, players[i].x, players[i].y);
    } 
}


int (*_getLevelData(int level))[TILES_X] { // get pointer to selected level
    if (level >= 0 && level < MAX_LEVELS) return levels[level];
    return levels[0]; // fallback to default
}

int current_level = 0;

void drawLevel(int level) {
    int (*levelData)[TILES_X] = _getLevelData(level);
    current_level = level;
    int level_sprite_N = LEVEL_SPRITE_N;
    _initLevelMonsters(level);

    for (int row = 0; row < TILES_Y; row++) {
        for (int col = 0; col < TILES_X; col++) {
            int tile = levelData[row][col];
            int x = col * 16;
            int y = row * 16;
            switch (tile) {
                case EMPTY:
                    break; // no draw
                case GROUND: 
                    drawSprite(GROUND_, level_sprite_N, x, y);
                    level_sprite_N += 1;
                    break;
                case KEY: 
                    drawSprite(KEY_, KEY_SPRITE_N, x, y);
                    break;
                case GOAL:   
                    drawSprite(GOAL_, level_sprite_N, x, y);
                    level_sprite_N += 1;
                    break;
                case BOMB:   
                    drawSprite(BOMB_, level_sprite_N, x, y); 
                    level_sprite_N += 1;
                    break;
                case PLAYER1: 
                    initPlayer(PLAYER1_N, x, y);
                    break;
                case PLAYER2: 
                    initPlayer(PLAYER2_N, x, y);
                    break;
            }
        }
    }

    drawPlayers();
    drawMonsters();
}


// PLAYER X Y POSITION IS TOP LEFT CORNER (0, 0)
// BOTTOM RIGHT OF PLAYER SPRITE IS (15, 15)
int getTileAt(int x, int y) {
    int (*levelData)[TILES_X] = _getLevelData(current_level);
    // check top left corner
    int col = x / SPRITE_SIZE;
    int row = y / SPRITE_SIZE;
    if (row < 0 || row >= TILES_Y || col < 0 || col >= TILES_X) return INVALID; // out of bounds
    return levelData[row][col];
}

static int _getTileRightTop(int x, int y) { // check (16, 0)
    return getTileAt(x + SPRITE_SIZE, y);
}
static int _getTileRightBottom(int x, int y) { // check (16, 15)
    return getTileAt(x + SPRITE_SIZE, y + SPRITE_SIZE - 1) ;
}
int checkRightIs(int x, int y, int tile_type) {
    return _getTileRightTop(x, y) == tile_type || _getTileRightBottom(x, y) == tile_type;
}

static int _getTileLeftTop(int x, int y) { // check (-1, 0)
    return getTileAt(x - 1, y);
}
static int _getTileLeftBottom(int x, int y) { // check (-1, 15)
    return getTileAt(x - 1, y + SPRITE_SIZE - 1);
}
int checkLeftIs(int x, int y, int tile_type) {
    return _getTileLeftTop(x, y) == tile_type || _getTileLeftBottom(x, y) == tile_type;
}


#define GET_TILE_TOLERANCE 2 // magic number to add some tolerance and prevent some bugs

static int _getTileBelowBottomLeft(int x, int y) { // check (CHECK_TILE_BELOW_TOLERANCE, 16)
    return getTileAt(x + GET_TILE_TOLERANCE, y + SPRITE_SIZE);
}
static int _getTileBelowBottomRight(int x, int y) { // check (15 - CHECK_TILE_BELOW_TOLERANCE, 16)
    return getTileAt(x + SPRITE_SIZE - 1 - GET_TILE_TOLERANCE, y + SPRITE_SIZE);
}
int checkBelowIs(int x, int y, int tile_type) {
    return _getTileBelowBottomLeft(x, y) == tile_type || _getTileBelowBottomRight(x, y) == tile_type;
}
