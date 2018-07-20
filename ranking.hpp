#include <ncurses.h>
#include <unistd.h>

void show_ranking(){
  clear();
  FILE *fp;
  if((fp = fopen("./text/ranking.txt", "r")) == NULL){
    mvprintw(3,3,"rankingファイルがありません!!");
    refresh();
    sleep(2);
    clear();
    return ;
  }

  char name[100];
  int height = 2, score = 0, rank = 0;

  mvprintw(0, 2,"じゅんい\tおなまえ\tとくてん");
  
  while(fscanf(fp, "%d %s %d", &rank, name, &score) != EOF) {
    mvprintw(height, 2,"%2d\t\t%s\t\t%2d", rank, name, score);
    height+=1;
  }
  
  mvprintw(height+2, 2, "       qキーでタイトルにもどる");
  int ch = 0;
  while(1){
    ch = getch();
    if(ch == 'q')break;
  }
  
  fclose(fp);
  clear();
}
