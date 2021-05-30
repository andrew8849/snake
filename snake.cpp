#include "snake.h"
using namespace std;

snakelocation::snakelocation(int col, int row){
  x = col;
  y = row;
}
snakelocation::snakelocation(){
  x = 0;
  y = 0;
}
snake::snake(){
  length = 0;
  direction = 'l';
  
}
snake::snake(vector<snakelocation>body){
  initscr();
  nodelay(stdscr,true);
  keypad(stdscr,true);
  noecho();
  curs_set(0);
  del = 50000;
  head = body[0];
  tail = vector<snakelocation>(body.begin()+1, body.end());
  length = body.size(); // vector size?
  snake.push_back(snakelocation(40+i,40));
  direction = 'l';
  }

}
movingsnake::~movingsnake(){
  nodelay(stdscr,false);
  getch();
  endwin();
}
void movingsnake::drawsnake(){
  for(int i=0; i<length; i++){
    move(snake[i].y,snake[i].x);
    addch(partchar);
}

void movingsnake::movesnake(){
  int tmp = getch();
  switch(tmp){
    case KEY_LEFT:
    if(direction != 'r')
    direction = 'l';
    break;
    case KEY_UP:
    if(direction != 'd')
    direction = 'u';
    break;
    case KEY_DOWN:
    if(direction != 'u')
    direction = 'd';
    break;
    case KEY_RIGHT:
    if(direction != 'l')
    direction = 'r';
    break;

    case KEY_BACKSPACE:
    direction = 'q';
    break;

  }
  if(direction=='l')
    snake.insert(snake.begin(), snakelocation(snake[0].x-1, snake[0].y));
    else if(direction=='r')
    snake.insert(snake.begin(), snakelocation(snake[0].x+1, snake[0].y));
    else if(direction=='u')
    snake.insert(snake.begin(), snakelocation(snake[0].x, snake[0].y-1));
    else if(direction=='d')
    snake.insert(snake.begin(), snakelocation(snake[0].x, snake[0].y+1));
    move(snake[0].y,snake[0].x);
    addch(partchar);
    refresh();

  if(!eatfruit){
    move(snake[snake.size()-1].y, snake[snake.size()-1].x);
    printw("□");
    refresh;
    snake.pop_back();
  }


}
void movingsnake::fruitplus(){
  if(snake[0].x == fruit.x && snake[0].y ==fruit.y){
    return eatfruit = True;
  }
  else{
    return eatfruit = False;
  }
  return eatfruit;
}

void movingsnake::collision(){
  //check snakehead
  //opreventing collision
  //snake head == snake body 
    if (snake[0].y < 1 || snake[0].y > MapSize_Y || snake[0].x < 1 || snake[0].x > MapSize_X)
        return true;

    for (int i=3; i<snake.size(); i++) {
        if (snake[0].x==snake[i].x && snake[i].y == snake[0].y) {
            return true;
        }
    }
    return false;
}


void movingsnake::start(){
  while(1){
    if(collision()){
      move(12,36);
      printw("gameend")
      break;
    }
    movesnake();
    if(direction=='q')
    break;
    usleep(del);
  }
}
