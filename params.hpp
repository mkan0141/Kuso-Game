#pragma once

#define MAZE_SIZE 21

#define BLOCK 0
#define ROAD 1
#define PLAYER 3
#define ENEMY 4

const int dx[4] = {0,1,0,-1};
const int dy[4] = {1,0,-1,0};

struct Vector2{
  int x, y;
  Vector2(int xx, int yy){
    x = xx;
    y = yy;
  }
};

struct Player{
  int x, y;
  Player(int xx, int yy){
    x = xx;
    y = yy;
  }
};

struct Enemy{
  int x, y;
  Enemy(int xx, int yy){
    x = xx;
    y = yy;
  }
};

bool available_move(Player player,Vector2 vec, int (&maze)[MAZE_SIZE][MAZE_SIZE]){
  if(0 <= player.x + vec.x && player.x + vec.x < MAZE_SIZE && 0 <= player.y + vec.y && player.y + vec.y < MAZE_SIZE)
    return maze[player.y + vec.y][player.x + vec.x] == ROAD;
  else return false;
}

bool e_available_move(Enemy enemy,Vector2 vec, int (&maze)[MAZE_SIZE][MAZE_SIZE]){
  if(0 <= enemy.x + vec.x && enemy.x + vec.x < MAZE_SIZE && 0 <= enemy.y + vec.y && enemy.y + vec.y < MAZE_SIZE)
    return maze[enemy.y + vec.y][enemy.x + vec.x] == ROAD;
  else return false;
}
