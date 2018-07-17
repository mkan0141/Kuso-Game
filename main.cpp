#include <cstdio>
#include <ncurses.h>
#include <unistd.h>

#include "menu.hpp"

int main(){
  setlocale(LC_ALL, "");
  initscr();
  keypad(stdscr, TRUE);
  crmode();
  noecho(); 
  curs_set(0);

  show_menu();

  printf("\n\n");
  return 0;
}
