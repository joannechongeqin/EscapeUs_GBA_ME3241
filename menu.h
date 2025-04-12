#ifndef MENU_H
#define MENU_H

#include "level.h"

int _firstXtoCentralizeText(int text_length, int letter_interval) {
	int text_total_width = text_length * letter_interval;
	return (SCREEN_WIDTH - text_total_width) / 2 + letter_interval / 4; 

}

void showMainMenu() {
    // DRAW TITLE
    int title_letters[TITLE_LENGTH] = {LETTER_T, LETTER_I, LETTER_T, LETTER_L, LETTER_E}; // TODO: THINK OF A TITLE
    int title_first_x = _firstXtoCentralizeText(TITLE_LENGTH, LETTER_INTERVAL);
    int title_y = 40;
    for (int i = 0; i < TITLE_LENGTH; i++) 
        drawSprite(title_letters[i], TITLE_SPRITE_N + i, title_first_x + LETTER_INTERVAL * i, title_y);

    // DRAW START BUTTON
    int start_letters[START_LENGTH] = {LETTER_S, LETTER_T, LETTER_A, LETTER_R, LETTER_T};
	int start_first_x = _firstXtoCentralizeText(START_LENGTH, LETTER_INTERVAL);
    int start_y = 100;
    for (int i = 0; i < START_LENGTH; i++) 
        drawSprite(start_letters[i], START_SPRITE_N + i, start_first_x + LETTER_INTERVAL * i, start_y);
}


void showEndingScreen(int isWin) {
    int win_letters[ENDING_LENGTH]  = {LETTER_Y, LETTER_O, LETTER_U, BLANK, LETTER_W, LETTER_I, LETTER_N, LETTER_EXCLAMATION};
    int lose_letters[ENDING_LENGTH] = {LETTER_Y, LETTER_O, LETTER_U, BLANK, LETTER_L, LETTER_O, LETTER_S, LETTER_E};
    int ending_first_x = _firstXtoCentralizeText(ENDING_LENGTH, LETTER_INTERVAL);
    int ending_y = 20;
    if (isWin) {
        for (int i = 0; i < ENDING_LENGTH; i++) {
            drawSprite(win_letters[i], ENDING_SPRITE_N + i, ending_first_x + LETTER_INTERVAL * i, ending_y);
        }
    } else {
        for (int i = 0; i < ENDING_LENGTH; i++) {
            drawSprite(lose_letters[i], ENDING_SPRITE_N + i, ending_first_x + LETTER_INTERVAL * i, ending_y);
        }   
    }
}

#endif

