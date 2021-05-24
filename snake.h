#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include<vector>
#include <ncurses.h>
#include <cstdlib>
#ifndef SNAKE_H
#define SNAKE_H

struct snakelocation{
  int y, x;
  snakelocation(int col, int row);
  snakelocation();
};
struct snake{
  int del;//delay -> 0.5 sec or tick?
  int direction, partchar, oldalchar, foo;
  bool get;
  int length;
  snakelocation food;
  snakelocation head;
  //std::vector<snakelocation> snake;
  std::vector<snakelocation> tail;

  snake(); //additional vector declaration?
  snake(std::vector<snakelocation> body);
  
};

class movingsnake{
  private:
  //int
  snake food;
  std::vector<snake> fullsnake;
  void movesnake();
  void drawsnake();
  void placefood();
  bool fruitplus();
  bool poisonminus();
  void collision();
  void start();


  public:
  movingsnake();
  ~movingsnake();
  void start();
};
#endif
