#ifndef MENU_H
#define MENU_H

#include "level.h"

void _drawTitle() {
    int title_first_x = 60;
    int title_x_interval = 20;
    int title_y = 20;
    drawSprite(TITLE_G, 1, title_first_x,                        title_y);
    drawSprite(TITLE_A, 2, title_first_x + title_x_interval,     title_y);
    drawSprite(TITLE_M, 3, title_first_x + title_x_interval * 2, title_y);
    drawSprite(TITLE_E, 4, title_first_x + title_x_interval * 3, title_y);
}

void _delTitle() {
    delSprite(1);
    delSprite(2);
    delSprite(3);
    delSprite(4);
}

void _drawStartButton() {
    int start_first_x = 60;
    int start_x_interval = 20;
    int start_y = 100;
    drawSprite(START_S, 5, start_first_x,                        start_y);
    drawSprite(START_T, 6, start_first_x + start_x_interval,     start_y);
    drawSprite(START_A, 7, start_first_x + start_x_interval * 2, start_y);
    drawSprite(START_R, 8, start_first_x + start_x_interval * 3, start_y);
    drawSprite(START_T, 9, start_first_x + start_x_interval * 4, start_y);
}

void _delStartButton() {
    delSprite(5);
    delSprite(6);
    delSprite(7);
    delSprite(8);
    delSprite(9);
}

void showMainMenu() {
    _drawTitle();
    _drawStartButton();
}

void hideMainMenu() {
    _delTitle();
    _delStartButton();
}

void initGame() {
    hideMainMenu();
    drawLevel(0);
    for (int i = 0; i < MAX_PLAYERS; i++) {
        drawSprite(players[i].spriteIndex, players[i].spriteN, players[i].x, players[i].y);
    }
}


void _showYouLose() {
    // TODO FIX THIS
    int youLose_first_x = 60;
    int youLose_interval = 20;
    int youLose_y = 40;
    int youLose_sprite_N = level_sprite_N + 1;
    drawSprite(START_S, youLose_sprite_N,     youLose_first_x,                        youLose_y);
    drawSprite(START_T, youLose_sprite_N + 1, youLose_first_x + youLose_interval,     youLose_y);
    drawSprite(START_A, youLose_sprite_N + 2, youLose_first_x + youLose_interval * 2, youLose_y);
    drawSprite(START_R, youLose_sprite_N + 3, youLose_first_x + youLose_interval * 3, youLose_y);
    drawSprite(START_T, youLose_sprite_N + 4, youLose_first_x + youLose_interval * 4, youLose_y);
    drawSprite(START_R, youLose_sprite_N + 5, youLose_first_x + youLose_interval * 5, youLose_y);
    drawSprite(START_T, youLose_sprite_N + 6, youLose_first_x + youLose_interval * 6, youLose_y);
}


void showLoseScreen() {
    // hideLevel();
    _showYouLose();
}

void _showYouWin() {
    // TODO FIX THIS
    int youWin_first_x = 60;
    int youWin_interval = 20;
    int youWin_y = 40;
    int youWin_sprite_N = level_sprite_N + 1;
    drawSprite(START_S, youWin_sprite_N,     youWin_first_x,                       youWin_y);
    drawSprite(START_T, youWin_sprite_N + 1, youWin_first_x + youWin_interval,     youWin_y);
    drawSprite(START_A, youWin_sprite_N + 2, youWin_first_x + youWin_interval * 2, youWin_y);
    drawSprite(START_R, youWin_sprite_N + 3, youWin_first_x + youWin_interval * 3, youWin_y);
    drawSprite(START_T, youWin_sprite_N + 4, youWin_first_x + youWin_interval * 4, youWin_y);
    drawSprite(START_R, youWin_sprite_N + 5, youWin_first_x + youWin_interval * 5, youWin_y);
}


void showWinScreen() {
    // hideLevel();
    _showYouWin();
}


#endif

