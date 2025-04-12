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
    int title_letters[TITLE_LENGTH] = {LETTER_M, LETTER_E}; // TODO: THINK OF A TITLE
    for (int i = 0; i < TITLE_LENGTH; i++) 
        drawSprite(title_letters[i], TITLE_SPRITE_N + i, title_first_x + title_x_interval * i, title_y);

    // DRAW START BUTTON
    int start_first_x = 60; int start_y = 100;
    int start_x_interval = 20;
    int start_letters[START_LENGTH] = {LETTER_S, LETTER_T, LETTER_A, LETTER_R, LETTER_T};
    for (int i = 0; i < START_LENGTH; i++) 
        drawSprite(start_letters[i], START_SPRITE_N + i, start_first_x + start_x_interval * i, start_y);
}


void showEndingScreen(int isWin) {
    int ending_first_x = 60; int ending_y = 40;
    int ending_interval = 20;
    int win_letters[ENDING_LENGTH]  = {LETTER_Y, LETTER_O, LETTER_U, LETTER_W, LETTER_I, LETTER_N, LETTER_EXCLAMATION};
    int lose_letters[ENDING_LENGTH] = {LETTER_Y, LETTER_O, LETTER_U, LETTER_L, LETTER_O, LETTER_S, LETTER_E};
    if (isWin) {
        for (int i = 0; i < ENDING_LENGTH; i++) {
            drawSprite(win_letters[i], ENDING_SPRITE_N + i, ending_first_x + ending_interval * i, ending_y);
        }
    } else {
        for (int i = 0; i < ENDING_LENGTH; i++) {
            drawSprite(lose_letters[i], ENDING_SPRITE_N + i, ending_first_x + ending_interval * i, ending_y);
        }   
    }
}

#endif

