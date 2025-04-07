#ifndef MENU_H
#define MENU_H

#include "player.h"
#include "mygbalib.h"

void drawTitle() {
    int title_first_x = 60;
    int title_x_interval = 20;
    int title_y = 20;
    drawSprite(TITLE_G, 1, title_first_x,                        title_y);
    drawSprite(TITLE_A, 2, title_first_x + title_x_interval,     title_y);
    drawSprite(TITLE_M, 3, title_first_x + title_x_interval * 2, title_y);
    drawSprite(TITLE_E, 4, title_first_x + title_x_interval * 3, title_y);
}

void delTitle() {
    delSprite(1);
    delSprite(2);
    delSprite(3);
    delSprite(4);
}

void drawStartButton() {
    int start_first_x = 60;
    int start_x_interval = 20;
    int start_y = 100;
    drawSprite(START_S, 5, start_first_x,                        start_y);
    drawSprite(START_T, 6, start_first_x + start_x_interval,     start_y);
    drawSprite(START_A, 7, start_first_x + start_x_interval * 2, start_y);
    drawSprite(START_R, 8, start_first_x + start_x_interval * 3, start_y);
    drawSprite(START_T, 9, start_first_x + start_x_interval * 4, start_y);
}

void delStartButton() {
    delSprite(5);
    delSprite(6);
    delSprite(7);
    delSprite(8);
    delSprite(9);
}

void showMainMenu() {
    drawTitle();
    drawStartButton();
}

void hideMainMenu() {
    delTitle();
    delStartButton();
}

void initGame() {
    hideMainMenu();
    initPlayer(120, 120);
}

#endif