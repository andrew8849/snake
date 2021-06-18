#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <ncurses.h>
#include <cstdlib>
#include <ctime>
#ifndef SNAKE_H
#define SNAKE_H

struct snakeloc{
int y,x;
snakeloc();
snakeloc(int col, int row);


}; //location of snake

class snakeclass{
private:
int del;//delay -> 0.5 sec or tick 50000
int body;//character representing snake's body
int snakelength;//snake's length
int snakemaxlength;//snake's maximum length
int fruitscore, poisonscore; //for scoreboard
int direction;//snake's direction
int height, width; // map height, width
int maxheight,maxwidth;
snakeloc fruit;
snakeloc poison;
bool eatfruit;
bool eatpoison;
bool sidewall; // immune wall
snakeloc snakehead;
std::vector<snakeloc> snaketail;
std::vector<snakeloc> snakebody;//represents all parts of snake's body
void makesnake();
void drawsnake();
void movesnake();
bool collision();
bool fruitplus();
//bool poisonminus();
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