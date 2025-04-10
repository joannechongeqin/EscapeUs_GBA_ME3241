#ifndef MYGBALIB_H
#define MYGBALIB_H

#include "player.h"

#define INPUT                      (KEY_MASK & (~REG_KEYS))

void drawSprite8x8(int numb, int N, int x, int y);

void drawSprite(int numb, int N, int x, int y);

void delSprite(int N);

void fillPalette(void);

void fillSprites(void);

#endif