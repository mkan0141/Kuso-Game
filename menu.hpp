#include <ncurses.h>
#include <unistd.h>

#include "game_control.hpp"
#include "ranking.hpp"
#include "help.hpp"

void draw_menu(){
  mvprintw(1, 5, "1. ぷれい！");
  mvprintw(3, 5, "2. らんきんぐ！");
  mvprintw(5, 5, "3. へるぷ！");
  mvprintw(7, 5, "4. ばいばい！");
}

int show_menu(){
  int key = -1, x_max, y_max;
  getmaxyx(stdscr, y_max, x_max);
  while(1){
    draw_menu();
    key = getch();
    /* game start */
    if(key == 49) show_game();
    /* show ranking */
    else if(key == 50) show_ranking();
    /* show help */
    else if(key == 51) show_help();
    /* exit game  */
    else if(key == 52) break;
    // mvprintw(30, 30, "%d", key);
  }
}
