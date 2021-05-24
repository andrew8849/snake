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
snakeclass::snakeclass(vector<snakelocation>body){
  initscr();
  nodelay(stdscr,true);
  keypad(stdscr,true);
  noecho();
  curs_set(0);
  del = 50000;
  head = body[0];
  tail = vector<snakelocation>(body.begin()+1, body.end());
  length = body.size();
  direction = 'l';
  for(int i=0; i<length; i++){
    move(snake[i].y,snake[i].x);
    addch(partchar);
  }

}
snakeclass::~snakeclass(){
  nodelay(stdscr,false);
  getch();
  endwin();
}
void snakeclass::movesnake(){
  int tmp = getch()
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
    snake.insert(snake.begin(), snakepart(snake[0].x-1, snake[0].y));
    else if(direction=='r')
    snake.insert(snake.begin(), snakepart(snake[0].x+1, snake[0].y));
    else if(direction=='u')
    snake.insert(snake.begin(), snakepart(snake[0].x, snake[0].y-1));
    else if(direction=='d')
    snake.insert(snake.begin(), snakepart(snake[0].x, snake[0].y+1));
    move(snake[0].y,snake[0].x);
    addch(partchar);
    refresh();


}

void snakeclass::start(){
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
