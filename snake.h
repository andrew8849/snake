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
  int del;
  char direction, partchar, oldalchar, foo;
  bool get;
  snakelocation food;
  snakelocation head;
  //std::vector<snakelocation> snake;
  std::vector<snakelocation> tail;
public:
  snake(); //additional vector declaration?
  snake(std::vector<snakelocation> body);
  ~snake();
  void start();
};

#endif
