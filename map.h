#ifndef __MAP__
#define __MAP__

#include <iostream>
#include <string.h>
#include <random>
#include <time.h>
#include "datatype.cpp"
using namespace std;

class map{
private:
  // 맵 가로 세로 사이즈
  int MapSize_Y = 21;
  int MapSize_X = 21;
  // 맵 배열
  char ***map_arr;
  // 아이템 갯수


public:
  int heart_count = 0;
  int poison_count = 0;
  // 생성자 맵 사이즈 받아서 생성
  map();
  map(int X, int Y);

  // 소멸자
  ~map(){
    for(int i = 0 ; i < MapSize_Y;i++){
      for(int j = 0 ; j < MapSize_X;j++){
        delete[] map_arr[i][j];
      }
      delete[] map_arr[i];
    }
    delete[] map_arr;
  }

  // 기타 함수
  char ***get_map() const; // 맵전체 문자열 받아오는 함수
  void init_map(); //맵전체를 기본맵으로 초기화 하는 함수
  void push_map(int x,int y, const char* str); // 맵 배열에 str을 넣는 함수
  struct Point item_create(bool item_type); // 아이템 생성해서 맵에 삽입하는 함수
  void delete_item(bool item_type); // 아이템 갯수 -1 해주는 함수
  struct two_Point gate_create(); // 게이트 생성해서 맵에 삽입하는 함수
  char* get_position(int x, int y); // 맵에서 x,y에 어떤 문자열인지 리턴해주는 함수
};



#endif
