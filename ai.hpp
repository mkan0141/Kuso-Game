#include <iostream>
#include <queue>
#include <utility>
#include <climits>
#include <ctime>
#include <cstdlib>
#include "params.hpp"

Vector2 random_ai(Enemy &enemy, int (&maze)[MAZE_SIZE][MAZE_SIZE]){
  int rnd=0;
  while(1){
    rnd = rand() % 4;
    if(e_available_move(enemy, Vector2(dx[rnd],dy[rnd]),maze)){
      break;
    }
  }
  return Vector2(enemy.x + dx[rnd], enemy.y + dy[rnd]);
}

int bfs(int x, int y,  Player player,int _maze[MAZE_SIZE][MAZE_SIZE]){
  
  int maze[MAZE_SIZE][MAZE_SIZE];
  for(int i=0;i<MAZE_SIZE;i++)for(int j=0;j<MAZE_SIZE;j++)maze[i][j] = _maze[i][j];

  std::queue<std::pair<Vector2,int> > que;
  que.push(std::make_pair(Vector2(x,y),0));
  
  while(que.size()){
    std::pair<Vector2,int> tmp = que.front();que.pop();
    int _x = tmp.first.x, _y = tmp.first.y, cost = tmp.second;
    for(int i = 0; i < 4; i++){
      int nx = _x + dx[i], ny = _y + dy[i];
      if(nx == player.x && ny == player.y){
	return cost + 1;
      }
      if(0 <= nx && nx < MAZE_SIZE && 0 <= ny && ny < MAZE_SIZE && maze[ny][nx] == ROAD){
	maze[ny][nx] = BLOCK;
	que.push(std::make_pair(Vector2(nx,ny), cost + 1));
      }
    }
  }
  return INT_MAX;
}

Vector2 bfs_ai(Enemy enemy, Player player,int maze[MAZE_SIZE][MAZE_SIZE]){
  int index = 0, cost = INT_MAX;
  
  maze[enemy.y][enemy.x] = BLOCK;
  for(int i = 0; i < 4; i++){
    int nx = enemy.x + dx[i], ny = enemy.y + dy[i];
    if(0 <= nx && nx < MAZE_SIZE && 0 <= ny && ny < MAZE_SIZE && maze[ny][nx] == ROAD){
      maze[ny][nx] = BLOCK;
      int new_cost = bfs(nx, ny, player, maze);
      maze[ny][nx] = ROAD;
      if(new_cost == INT_MAX) continue;
      if(new_cost <= cost)index = i;
    }
  }
  maze[enemy.y][enemy.x] = ROAD;
  return Vector2(enemy.x + dx[index], enemy.y + dy[index]);
}

Vector2 ai(Enemy enemy, Player player,int (&maze)[MAZE_SIZE][MAZE_SIZE], time_t start){
  time_t now = time(NULL);
  int diff_time = now - start;

  if(diff_time <= 10)return random_ai(enemy, maze);
  else return bfs_ai(enemy, player, maze);
}
