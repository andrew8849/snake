#ifndef __MAP__
#define __MAP__

#include <iostream>
#include <string.h>
#include <random>
#include <time.h>

using namespace std;

class map{
private:
  // 맵 가로 세로 사이즈
  int MapSize_Y = 21;
  int MapSize_X = 21;
  // 맵 배열
  char ***map_arr;

public:
  // 생성자 맵 사이즈 받아서 생성
  map();
  map(int X, int Y);

  // 소멸자
  ~map(){
    for(int i = 0 ; i < MapSize_X;i++) delete [] map_arr[i];
    delete[] map_arr;
  }

  // 기타 함수
  char ***get_map() const;
  void init_map();
  void push_map(int x,int y, char* str);
  void item_create(bool item_type);
  void gate_create();
};

struct Point{
  int x;
  int y;
};

#endif
