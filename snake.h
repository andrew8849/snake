#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include<iostream>
#include<vector>
#include <ncurses.h>
#include <cstdlib>
#include <ctime>

#ifndef SNAKE_H
#define SNAKE_H


struct snakeloc{
int y,x;
snakeloc(int col, int row);
snakeloc();

}; //location of snake

class snakeclass{
private:
int del;//delay -> 0.5 sec or tick?
int partchar,maxwidth, maxheight;
snakeloc fruit;
snakeloc poison;
  char direction;
  int length;
bool eatfruit;
bool eatpoison;
snakeloc head;
std::vector<snakeloc> snakebody;
 void movesnake();
  void drawsnake();
//  void placefood();
  bool fruitplus();
 // bool poisonminus();
  bool collision();
public:
snakeclass();
~snakeclass();
void start();
};
#endif

  /*snakelocation food;
  snakelocation head;
  std::vector<snakelocation> snake;
  std::vector<snakelocation> tail;


  snake(); //additional vector declaration?
  snake(std::vector<snakelocation> body);*/