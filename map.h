#ifndef __MAP__
#define __MAP__

#include <iostream>
#include <ncurses.h>
#include <vector>
#include<string.h>

using namespace std;

class map{
private:
  // 맵 가로 세로 사이즈
  int MapSize_Y = 30;
  int MapSize_X = 30;
  // 맵 배열
  char **map_arr;

public:
  // 생성자 맵 사이즈 받아서 생성
  map(){
    map_arr = new char*[30];
    for(int i=0;i<30;i++){
      map_arr[i] = new char[30];
      memset(map_arr[i], ' ',sizeof(char)*30);
    }
    init_map();
  }
  map(int X, int Y) :MapSize_X(X),MapSize_Y(Y){
    map_arr = new char*[Y];
    for(int i = 0; i<X;i++){
      map_arr[i] = new char[X];
      memset(map_arr[i], ' ',sizeof(char)*X);
    }
    init_map();
  }
  // 소멸자
  ~map(){
    for(int i = 0 ; i < MapSize_X;i++) delete [] map_arr[i];
    delete[] map_arr;
  }

  char **get_map() const;
  void init_map();

};

#endif
