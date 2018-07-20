#pragma once

#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include <unistd.h>
#include <locale.h>

#include "ai.hpp"
#include "result.hpp"
#include "create_maze.hpp"
const int delay = 1000;

int available_key(int key){
  if(key == KEY_DOWN) return 0;
  else if(key == KEY_RIGHT)return 1;
  else if(key == KEY_UP) return 2;
  else if(key == KEY_LEFT) return 3;
  else return -1;
}

void move_player(Player &player, Vector2 d, int (&maze)[MAZE_SIZE][MAZE_SIZE]){
  maze[player.y][player.x] = ROAD;
  player = Player(d.x, d.y);
  maze[d.y][d.x] = PLAYER;
}

void move_enemy(Enemy &enemy, Vector2 d, int (&maze)[MAZE_SIZE][MAZE_SIZE]){
  maze[enemy.y][enemy.x] = ROAD;
  enemy = Enemy(d.x, d.y);
  maze[d.y][d.x] = ENEMY;
}

bool is_game_over(Enemy enemy, Player player){
  return (player.x == enemy.x && player.y == enemy.y);
}

void init_charactor(Player &player, Enemy &enemy, int (&maze)[MAZE_SIZE][MAZE_SIZE]){
  player = Player(1, 1);
  enemy = Enemy(9, 9);
  maze[player.y][player.x] = PLAYER;
  maze[enemy.y][enemy.x] = ENEMY;
  srand((unsigned)time(NULL));
}

void draw_all(int (&maze)[MAZE_SIZE][MAZE_SIZE], time_t start){
  clear();
  mvprintw(0, MAZE_SIZE * 3 / 4,"%d びょうけいか",time(NULL) - start);
  for(int i=0;i<MAZE_SIZE;i++){
    int width = 2;
    for(int j=0;j<MAZE_SIZE;j++){
      if(maze[i][j]==BLOCK){
	mvprintw(i+2,width,"■");
      }else if(maze[i][j] == PLAYER){
      	mvprintw(i+2,width,"○");
      }else if(maze[i][j] == ENEMY){
	mvprintw(i+2,width,"●");
      }
      width += 2;
    }
  }
  refresh();
}

void destroy_all(int (&maze)[MAZE_SIZE][MAZE_SIZE], Player *player, Enemy *enemy){
  free(player);
  free(enemy);
}

void game_main(char *name){
  clear();
  int maze[MAZE_SIZE][MAZE_SIZE];
  Player *player; player = (Player*)malloc(sizeof(Player));
  Enemy *enemy; enemy = (Enemy*)malloc(sizeof(Enemy));
  int ch;
  
  create_maze(maze);
  init_charactor(*player, *enemy, maze);
 
  time_t start = time(NULL); 
  draw_all(maze, start);
  timeout(delay);
  while(1){
    ch = -1;
    ch = getch();
    ch = available_key(ch);
    if(ch != -1){
      if(available_move(*player,Vector2(dx[ch],dy[ch]),maze)){
        Vector2 vec = ai(*enemy, *player,maze,start);
        move_player(*player, Vector2(player->x + dx[ch], player->y + dy[ch]), maze);
	    move_enemy(*enemy, vec, maze);
	if(is_game_over(*enemy, *player)){
	  draw_all(maze,start);
          break;
     	}
      }
    }else{
			Vector2 vec = ai(*enemy, *player,maze,start);
			move_enemy(*enemy, vec, maze);

			if(is_game_over(*enemy, *player)){draw_all(maze,start);break;       }
	}
    draw_all(maze, start);
    ch = -1;
  } 
  destroy_all(maze, player, enemy);
  clear();refresh();
  time_t end = time(NULL);

  timeout(-1);
  draw_result(end - start , name);
}
