#include <unistd.h>
#include <studio.h>
#include <stdlib.h>
#include<iostream>
#include<vector>
#include <ncurses.h>
#include <cstdlib>
#ifndef SNAKE_H
#define SNAKE_H

struct snakelocation{
  int y, x;
  snakepart(int col, int row);
  snakepart();
};
struct snakeclass{
  int del;
  char direction, partchar. oldalchar, foo;
  bool get;
  snakelocation food;
  snakelocation head;
  std::vector<snakelocation> tail;
  snakeclass();
  snakeclass(std::vector<snakelocationt> body);
public:
  snakeclass();
  ~snakeclass();
  void start;
};

#endif
