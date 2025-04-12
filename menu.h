#ifndef MENU_H
#define MENU_H

#include "level.h"

void clearScreen() {
    for(int i = 0; i < 128; i++)
        drawSprite(0, i, 240, 160);
}


void showMainMenu() {
    // DRAW TITLE
    int title_first_x = 60;
    int title_x_interval = 20;
    int title_y = 20;
    for (int i = 0; i < TITLE_LENGTH; i++) 
        drawSprite(TITLE_G, TITLE_SPRITE_N + i, title_first_x + title_x_interval * i, title_y); // TODO FIX SPRITE INDEX

    // DRAW START BUTTON
    int start_first_x = 60;
    int start_x_interval = 20;
    int start_y = 100;
    for (int i = 0; i < START_LENGTH; i++) 
        drawSprite(START_S, START_SPRITE_N + i, start_first_x + start_x_interval * i, start_y); // TODO FIX SPRITE INDEX
}


void showEndingScreen(int isWin) {
    int ending_first_x = 60;
    int ending_interval = 20;
    int ending_y = 40;
    int ending_sprite_index;
    if (isWin) {
        ending_sprite_index = TITLE_G;
    } else {
        ending_sprite_index = TITLE_A;
    }
    for (int i = 0; i < ENDING_LENGTH; i++) {
        drawSprite(ending_sprite_index, ENDING_SPRITE_N + i, ending_first_x + ending_interval * i, ending_y); // TODO FIX SPRITE INDEX
    }
}

#endif

