#include "level.h"
#include "player.h"

int level_0[TILES_Y][TILES_X] = {
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
};

int level_1[TILES_Y][TILES_X] = {
    // 0     1       2       3       4       5       6       7       8       9      10      11      12      13      14
    { 0,        0,          0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0       }, // Row 0
    { 0,        0,          0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      KEY     }, // Row 1
    { 0,        0,          0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      GROUND, GROUND, GROUND  }, // Row 2
    { 0,        0,          0,      0,      0,      0,      0,      0,      0,      0, GROUND,      0,      0,      0,      0       }, // Row 3
    { 0,        0,          0,      0,      0,      0,      0,      0, GROUND,      0,      0,      0,      0,      GOAL,   0       }, // Row 4
    { 0,        0,          0,      0,      0,      0,      0, GROUND,      0,      0,      0,      0,      0,      GROUND, 0       }, // Row 5
    { 0,        0,          0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0       }, // Row 6
    { PLAYER1,  PLAYER2,    0,      0, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND,      0,      0,      0,      GROUND  }, // Row 7
    { GROUND,   GROUND,     0,      0, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND,      0,      0,      GROUND, GROUND  }, // Row 8
    { GROUND,   GROUND,     0,      0, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND, GROUND,      0,      0,      GROUND, GROUND  }  // Row 9
};

int (*_getLevelData(int level))[TILES_X] { // get pointer to selected level
    switch (level) {
        case 0: return level_0;
        case 1: return level_1;
        // case 2: return level_2;
        default: return level_0;
    }
}

int current_level = 0;

void drawLevel(int level) {
    int (*levelData)[TILES_X] = _getLevelData(level);
    current_level = level;
    int level_sprite_N = LEVEL_SPRITE_N;

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

    for (int i = 0; i < NUM_PLAYERS; i++) {
        drawSprite(players[i].spriteIndex, players[i].spriteN, players[i].x, players[i].y);
    }
    
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



int getTileRightTop(int x, int y) { // check (16, 0)
    return getTileAt(x + SPRITE_SIZE, y);
}
int getTileRightBottom(int x, int y) { // check (16, 15)
    return getTileAt(x + SPRITE_SIZE, y + SPRITE_SIZE - 1) ;
}

int getTileLeftTop(int x, int y) { // check (-1, 0)
    return getTileAt(x - 1, y);
}
int getTileLeftBottom(int x, int y) { // check (-1, 15)
    return getTileAt(x - 1, y + SPRITE_SIZE - 1);
}

#define GET_TILE_TOLERANCE 2 // magic number to add some tolerance and prevent some bugs

int getTileBelowCenter(int x, int y) { // check (7, 16)
    return getTileAt(x + SPRITE_SIZE - 1, y + SPRITE_SIZE);
}

int getTileBelowBottomLeft(int x, int y) { // check (CHECK_TILE_BELOW_TOLERANCE, 16)
    return getTileAt(x + GET_TILE_TOLERANCE, y + SPRITE_SIZE);
}

int getTileBelowBottomRight(int x, int y) { // check (15 - CHECK_TILE_BELOW_TOLERANCE, 16)
    return getTileAt(x + SPRITE_SIZE - 1 - GET_TILE_TOLERANCE, y + SPRITE_SIZE);
}
