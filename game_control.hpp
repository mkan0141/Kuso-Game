#pragma once

#include <ncurses.h>
#include <unistd.h>

#include "game.hpp"

char *input_username_screen(char *name){
  int ch, index = 0;
  clear();

  int width = 5;
  mvprintw(5,2,"ゆーざーめいをにゅうりょくしてね");
  while(ch = getch(), ch != 10){
    clear();
    mvprintw(5,2,"ゆーざーめいをにゅうりょくしてね");
    if(ch == KEY_BACKSPACE){
      name[index] = '\0';
      if(index)index--;
    }else if(ch != KEY_BACKSPACE){
      name[index] = ch;
      index++;
    }
    mvprintw(10,width, "%s",name);
    refresh();
  }
  
  clear();
  return name;
}

void show_game(){
  char name[200];
  input_username_screen(name);
  game_main(name);
}
