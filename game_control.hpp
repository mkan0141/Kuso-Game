#include <ncurses.h>
#include <unistd.h>

#include "game.hpp"

char *input_username_screen(){
  int ch, index = 0;
  char name[200];
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
  char *name = input_username_screen();
  game_main(name);
}
