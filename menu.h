#ifndef MENU_H
#define MENU_H

#include "level.h"

int _firstXtoCentralizeText(int text_length, int letter_interval) {
	int text_total_width = text_length * letter_interval;
	return (SCREEN_WIDTH - text_total_width) / 2 + letter_interval / 4; 
}

void showMainMenu() {
    // DRAW TITLE
    int title_letters[TITLE_LENGTH] = {TITLE_E, TITLE_S, TITLE_C, TITLE_A, TITLE_P, TITLE_E, BLANK, TITLE_U, TITLE_S, BLANK};
    int title_first_x = _firstXtoCentralizeText(TITLE_LENGTH, LETTER_INTERVAL);
    int title_y = 60;
    for (int i = 0; i < TITLE_LENGTH; i++) 
        drawSprite(title_letters[i], TITLE_SPRITE_N + i, title_first_x + LETTER_INTERVAL * i, title_y);

    // DRAW START BUTTON
    int press_start_letters[START_LENGTH1] = {LETTER_P, LETTER_R, LETTER_E, LETTER_S, LETTER_S, BLANK, LETTER_S, LETTER_T, LETTER_A, LETTER_R, LETTER_T};
	int press_start_first_x = _firstXtoCentralizeText(START_LENGTH1, LETTER_INTERVAL);
    int press_start_y = 100;
    for (int i = 0; i < START_LENGTH1; i++) 
        drawSprite(press_start_letters[i], START_SPRITE_N + i, press_start_first_x + LETTER_INTERVAL * i, press_start_y);

    int to_play_letters[START_LENGTH2] = {LETTER_T, LETTER_O, BLANK, LETTER_P, LETTER_L, LETTER_A, LETTER_Y};
    int to_play_first_x = _firstXtoCentralizeText(START_LENGTH2, LETTER_INTERVAL);
    int to_play_y = 120;
    for (int i = 0; i < START_LENGTH2; i++) 
        drawSprite(to_play_letters[i], START_SPRITE_N + START_LENGTH1 + i, to_play_first_x + LETTER_INTERVAL * i, to_play_y);

    // DRAW SOME EXTRA SPRITES TO LOOK GOOD
    drawSprite(P1_R_MOVE, PLAYER1_N, 60, 36);
    drawSprite(ARROW_, ARROW_SPRITE_N, 60, 20);
    drawSprite(P2_R_DEAD, PLAYER2_N, 80, 36);
	 drawSprite(KEY_, KEY_SPRITE_N, 118, 8);
	 drawSprite(GROUND_, LEVEL_SPRITE_N, 118, 28);
    drawSprite(GOAL_, LEVEL_SPRITE_N + 1, 160, 36);
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

