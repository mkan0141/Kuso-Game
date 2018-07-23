#pragma once

#include <ncurses.h>
#include <unistd.h>

#include "game.hpp"

void input_username_screen(char *name) {
    int ch, index = 0;
    clear();

    int width = 5;
    mvprintw(3, 2, "ゆーざーめいをにゅうりょくしてね");
    while (ch = getch(), ch != 10) {
        clear();
        mvprintw(3, 2, "ゆーざーめいをにゅうりょくしてね");
        if (ch == KEY_BACKSPACE) {
            name[index] = '\0';
            if (index) index--;
        } else if (ch != KEY_BACKSPACE) {
            name[index] = ch;
            index++;
        }
        mvprintw(5, width, "%s", name);
        refresh();
    }

    clear();
}

void show_game() {
    char name[200];
    input_username_screen(name);
    game_main(name);
}
