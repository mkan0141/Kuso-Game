#pragma once

#include <stdlib.h>
#include <ctime>
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

void init_enemy(Enemy &enemy, Player player, int (&maze)[MAZE_SIZE][MAZE_SIZE]){
		while(1){
				int x = rand() % MAZE_SIZE, y = rand() % MAZE_SIZE;
				if(maze[y][x] == ROAD && player.x != x && player.y != y){
						enemy = Enemy(x,y);
						break;
				}
		}
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
		Enemy *enemy; enemy = (Enemy*)malloc(sizeof(Enemy) * 10);
		Vector2 *vec; vec = (Vector2*)malloc(sizeof(Vector2) * 10);
		int *enemy_walk; enemy_walk = (int*)malloc(sizeof(int)*10);
		int ch;

		create_maze(maze);
		init_charactor(*player, enemy[0], maze);

		time_t start = time(NULL); 
		draw_all(maze, start);
		timeout(delay);

		int enemy_cnt = 1;
		bool update=false,gameover = false;
		while(1){
				if(update&&enemy_cnt!=10&&(time(NULL)-start)%6 == 0){
						enemy_cnt++;
						init_enemy(enemy[enemy_cnt-1],*player, maze);
						update=false;
				}else{update=true;}


				ch = -1, ch = getch();
				ch = available_key(ch);
				if(ch != -1){
						if(available_move(*player,Vector2(dx[ch],dy[ch]),maze)){
								for(int i=0;i<enemy_cnt; i++) vec[i] = ai(enemy[i], *player,maze,enemy_walk[i]);
								for(int i=0;i<enemy_cnt; i++){
										if(is_game_over(enemy[i],*player)){
												gameover=true;
												break;
										}
										move_enemy(enemy[i], vec[i], maze);
								}
								move_player(*player, Vector2(player->x + dx[ch], player->y + dy[ch]), maze);
								for(int i=0;i<enemy_cnt;i++){
										if(is_game_over(enemy[i], *player)){
												gameover=true;
												break;
										}

								}
						}
				}else{
						for(int i=0;i<enemy_cnt; i++) vec[i] = ai(enemy[i], *player,maze,enemy_walk[i]);
						for(int i=0;i<enemy_cnt;i++){
								move_enemy(enemy[i], vec[i], maze);
								if(is_game_over(enemy[i], *player)){
										gameover = true;
										break;
								}
						}
				}

				draw_all(maze, start);
				ch = -1;
				if(gameover)break;
		}
		draw_all(maze, start);sleep(1);
		destroy_all(maze, player, enemy);
		clear();refresh();
		time_t end = time(NULL);

		timeout(-1);
		draw_result(end - start , name);
}
