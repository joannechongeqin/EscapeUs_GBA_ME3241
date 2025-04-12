#include "level.h"
#include "player.h"

int level_0[TILES_Y][TILES_X] = {
    // 0     1       2       3       4       5       6       7       8       9      10      11      12      13      14
    { 0,    0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0    },   // Row 0
    { 0,    0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0    },   // Row 1
    { 0,    KEY,    0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0    },   // Row 2
    { 0,    GROUND, 0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0    },   // Row 3
    { 0,    0,      0,      GROUND, 0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      GOAL },   // Row 4
    { 0,    0,      0,      0,      0,      0,      GROUND,      0,      0,      0,      0,      0,      0,      0,      GROUND }, // Row 5
    { 0,    0,      0,      0,      0,      GROUND, 0,      0,      0,      0,      0,      0,      0,      GROUND, GROUND }, // Row 6
    { 0,    0,      0,      0,      0,      0,      PLAYER1,0,      BOMB,   PLAYER2,0,      0,      GROUND, GROUND, GROUND }, // Row 7
    { 0,    0,      0,      0,      0,      0,      GROUND, GROUND, GROUND, GROUND, 0,      GROUND, GROUND, GROUND, GROUND }, // Row 8
    { 0,    0,      0,      0,      0,      0,      GROUND, GROUND, GROUND, GROUND, 0,      GROUND, GROUND, GROUND, GROUND }  // Row 9
};

// int level_1[TILES_Y][TILES_X] = {
//     // 0     1       2       3       4       5       6       7       8       9      10      11      12      13      14
//     { 0,    0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0    },   // Row 0
//     { 0,    0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0    },   // Row 1
//     { 0,    KEY,    0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0    },   // Row 2
//     { 0,    GROUND, 0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      KEY  },   // Row 3
//     { 0,    0,      0,      GROUND, 0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      GOAL },   // Row 4
//     { 0,    0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      GROUND }, // Row 5
//     { 0,    0,      0,      0,      0,      GROUND, 0,      0,      0,      0,      0,      0,      0,      GROUND, GROUND }, // Row 6
//     { 0,    0,      0,      0,      0,      0,      PLAYER1,0,      BOMB,   PLAYER2,0,      0,      GROUND, GROUND, GROUND }, // Row 7
//     { 0,    0,      0,      0,      0,      0,      GROUND, GROUND, GROUND, GROUND, 0,      GROUND, GROUND, GROUND, GROUND }, // Row 8
//     { 0,    0,      0,      0,      0,      0,      GROUND, GROUND, GROUND, GROUND, 0,      GROUND, GROUND, GROUND, GROUND }  // Row 9
// };

int (*_getLevelData(int level))[TILES_X] { // get pointer to selected level
    switch (level) {
        case 0: return level_0;
        // case 1: return level_1;
        // case 2: return level_2;
        default: return level_0;
    }
}

int CURRENT_LEVEL = 0;
int level_sprite_N = LEVEL_SPRITE_N;

void drawLevel(int level) {
    int (*levelData)[TILES_X] = _getLevelData(level);
    CURRENT_LEVEL = level;

    for (int row = 0; row < TILES_Y; row++) {
        for (int col = 0; col < TILES_X; col++) {
            int tile = levelData[row][col];
            int x = col * 16;
            int y = row * 16;
            switch (tile) {
                case EMPTY:
                    break; // no draw
                case GROUND: 
                    drawSprite(GROUND_SPRITE, level_sprite_N, x, y);
                    level_sprite_N += 1;
                    break;
                case KEY: 
                    drawSprite(KEY_SPRITE,    level_sprite_N, x, y);
                    level_sprite_N += 1;
                    break;
                case GOAL:   
                    drawSprite(GOAL_SPRITE,   level_sprite_N, x, y);
                    level_sprite_N += 1;
                    break;
                case BOMB:   
                    drawSprite(BOMB_SPRITE,   level_sprite_N, x, y); 
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
}


void hideLevel() {
    for (int i = 0; i < MAX_PLAYERS; i++) {
        delSprite(players[i].spriteN); // delete player sprite
    }
    for (int i = LEVEL_SPRITE_N; i < level_sprite_N; i++) {
        delSprite(i);
    }
    level_sprite_N = LEVEL_SPRITE_N; // reset to starting N
}


int getTileAt(int x, int y) {
    int (*levelData)[TILES_X] = _getLevelData(CURRENT_LEVEL);
    int col = x / SPRITE_SIZE;
    int row = y / SPRITE_SIZE;
    if (row < 0 || row >= TILES_Y || col < 0 || col >= TILES_X) return INVALID; // out of bounds
    return levelData[row][col];
}

int getTileRight(int x, int y) {
    return getTileAt(x + SPRITE_SIZE, y);
}
int getTileLeft(int x, int y) {
    return getTileAt(x - 1, y);
}

int getTileAbove(int x, int y) {
    return getTileAt(x + SPRITE_SIZE / 2, y - SPRITE_SIZE);
}

int getTileBelow(int x, int y) {
    return getTileAt(x + SPRITE_SIZE / 2, y + SPRITE_SIZE);
}
