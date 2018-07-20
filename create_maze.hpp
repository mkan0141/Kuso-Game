#pragma once

#include <iostream>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "params.hpp"
using namespace std;

vector<Vector2> tmp;
void DEBUG(int maze[MAZE_SIZE][MAZE_SIZE], vector<Vector2> path){
  for(int i=0;i<MAZE_SIZE;i++){
    for(int j=0;j<MAZE_SIZE;j++){
      if(maze[i][j]==BLOCK) cout << "#";
      else cout << ".";
    }
    cout<<endl;
  }
  cout << endl<<endl;;
}

void init_maze(int (&maze)[MAZE_SIZE][MAZE_SIZE], vector<Vector2> &nodes){
  /* 1マスおきに柱を置く  */
  for(int i=0;i<MAZE_SIZE;i++){
    for(int j=0;j<MAZE_SIZE;j++){
      if(i%2==0&&j%2==0){
	maze[i][j] = BLOCK;
	if(i!=0&&j!=0&&i!=MAZE_SIZE-1&&j!=MAZE_SIZE-1)nodes.push_back(Vector2(j,i));
      }else{
	maze[i][j] = ROAD;
      }
    }
  }
  /* 外枠を壁で囲む */
  for(int i = 0; i < MAZE_SIZE; i++){
    maze[0][i] = maze[MAZE_SIZE - 1][i] = maze[i][0] = maze[i][MAZE_SIZE-1] = BLOCK;
    /*
    path.push_back(Vector2(0,i));
    path.push_back(Vector2(i,0));
    path.push_back(Vector2(MAZE_SIZE - 1,i));
    path.push_back(Vector2(i,MAZE_SIZE - 1));
    */
  }
}

bool equal(Vector2 a, Vector2 b){
  return (a.x == b.x && a.y == b.y);
}

bool is_nodes(vector<Vector2> &nodes, Vector2 &vec){
  for(int i = 0; i < nodes.size(); i++){
    if(equal(nodes[i],vec))return true;
  }
  return false;
}

bool is_path(vector<Vector2> &path, Vector2 vec){
  for(int i = 0; i < path.size(); i++){
    if(equal(path[i], vec))return true;
  }
  return false;
}

void delete_node(vector<Vector2> &path, vector<Vector2> &nodes){
  for(int i = 0; i < path.size(); i++){
    for(int j = 0; j < nodes.size(); j++){
      if(equal(path[i],nodes[j])){
	nodes.erase(nodes.begin() + j);
	j--;
	break;
      }
    }
  }
}

Vector2 hoge = Vector2(0,0);
bool ok=false;

bool search(Vector2 now, vector<Vector2> path, vector<Vector2> nodes){
  //cout << now.x <<", " << now.y << endl;
  if(!is_nodes(nodes, now)){
    tmp = path;
    return true;
  }
  
  int d[4] = {0,1,2,3};
  for(int i = 0; i < 5; i++){
    int r1  = rand()%4, r2 = rand() % 4;
    swap(d[r1],d[r2]);
  }
  
  for(int i = 0; i < 4; i++){
    if(ok)return true;
    Vector2 new_vec = Vector2(now.x + dx[d[i]]*2, now.y + dy[d[i]]*2);
    if(is_path(path, new_vec))continue;
    now.x += dx[d[i]];now.y += dy[d[i]];
    path.push_back(now);
    now.x += dx[d[i]];now.y += dy[d[i]];
    path.push_back(now);
    
    if(search(now, path,nodes)){ok=true;return true;}
    now.x -= dx[d[i]]*2;now.y -= dy[d[i]]*2;
    path.pop_back();
    path.pop_back();
  }
  
  return false;
}

void add_block(int (&maze)[MAZE_SIZE][MAZE_SIZE]){
  for(int i = 0; i < tmp.size(); i++){
    maze[tmp[i].y][tmp[i].x] = BLOCK;
  }
}

// 適当に壁を削る
void random_erase(int (&maze)[MAZE_SIZE][MAZE_SIZE]){
  int cnt = 0;
  while(cnt != 20){
    int x = rand() % MAZE_SIZE;
    int y = rand() % MAZE_SIZE;
    if(x!=0&&y!=0&&x!=MAZE_SIZE-1&&y!=MAZE_SIZE-1&&maze[y][x] == BLOCK){
      maze[y][x] = ROAD;
      cnt++;
    }
  }
  
}

void create_maze(int (&maze)[MAZE_SIZE][MAZE_SIZE]){
  vector<Vector2> nodes, path;
  /* 迷路の初期化 */
  init_maze(maze, nodes);
  srand((unsigned)time(NULL));
  while(!nodes.empty()){
    path.clear();
    tmp.clear();
    ok=false;

    // スタート地点を決める
    int index = rand() % nodes.size();
    Vector2 dir = nodes[index];
    hoge = dir;
    
    // pathにスタート位置を入れる
    path.push_back(dir);
    /* 探索開始 */
    if(!search(dir, path, nodes)){cout<<"end"<<endl;continue;}

    delete_node(tmp,nodes);
    add_block(maze);
  }
  random_erase(maze);
  //DEBUG(maze,path);
}
