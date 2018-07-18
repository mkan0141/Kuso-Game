#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>

#define MAX_LENGTH 100

void show_help(){
  clear();
  FILE *fp;
  if((fp = fopen("./text/help.txt", "r")) == NULL){
    mvprintw(3,3,"rankingファイルがありません!!");
    refresh();
    sleep(2);
    clear();
    return ;
  }
  
  int height = 0;
  char str[100];
  clear();
  while(fgets(str, MAX_LENGTH, fp) != NULL) {
    mvprintw(height, 2,"%s", str);
    height+=2;
  }
  refresh();
  
  int ch = 0;
  while(1){
    ch = getch();
    if(ch == 'q')break;
  }
  
  fclose(fp);
  clear();
}
