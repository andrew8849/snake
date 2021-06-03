#include "snake.h"

using namespace std;

snakeloc::snakeloc(int col, int row){
  x = col;
  y = row;
}
snakeloc::snakeloc(){
  x = 0;
  y = 0;
}
snakeclass::snakeclass(){
  partchar = 'x';
  length = 3;
  direction = 'l';
  del = 50000;
   initscr();
  nodelay(stdscr,true);
  keypad(stdscr,true);
  noecho();
  curs_set(0);
  getmaxyx(stdscr, maxheight, maxwidth); // define dimensions of game window



drawsnake();
movesnake();
//placefood();
fruitplus();
//poisonminus();
collision();
refresh();
}
snakeclass::~snakeclass(){
  nodelay(stdscr,false);
  getch();
  endwin();
}

void snakeclass::drawsnake(){
  for(int i=0; i<5; i++){
    snakebody.push_back(snakeloc(30+i,10));
  }
  for(int i=0; i<snakebody.size(); i++){
    move(snakebody[i].y,snakebody[i].x);
    addch(partchar);
}
return;
}
/*
snakeclass::snakeclass(vector<snakeloc>snakebody){
  
  head = body[0];
  tail = vector<snakelocation>(body.begin()+1, body.end());
  length = body.size(); // vector size?
  snake.push_back(snakelocation(40+i,40));
  direction = 'l';
  }

}

*/
void snakeclass::movesnake(){
  int tmp = getch();
  switch(tmp){
    case KEY_LEFT:
    if(direction != 'r'){direction = 'l';}
    break;
    case KEY_UP:
    if(direction != 'd'){direction = 'u';}
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
    snakebody.insert(snakebody.begin(), snakeloc(snakebody[0].x-1, snakebody[0].y));
    else if(direction=='r')
    snakebody.insert(snakebody.begin(), snakeloc(snakebody[0].x+1, snakebody[0].y));
    else if(direction=='u')
    snakebody.insert(snakebody.begin(), snakeloc(snakebody[0].x, snakebody[0].y-1));
    else if(direction=='d')
    snakebody.insert(snakebody.begin(), snakeloc(snakebody[0].x, snakebody[0].y+1));
    move(snakebody[0].y,snakebody[0].x);
    addch(partchar);
    refresh();

  if(!eatfruit){
    move(snakebody[snakebody.size()-1].y, snakebody[snakebody.size()-1].x);
    printw("□");
    refresh;
    snakebody.pop_back();
  }


}
bool snakeclass::fruitplus(){
  if(snakebody[0].x == fruit.x && snakebody[0].y ==fruit.y){
    return eatfruit = true;
  }
  else{
    return eatfruit = false;
  }
  return 0;
}

bool snakeclass::collision(){
  //check snakehead
  //opreventing collision
  //snake head == snake body 
    if (snakebody[0].y < 1 || snakebody[0].y > 21 || snakebody[0].x < 1 || snakebody[0].x > 21)
        return true; //MapSize_X, MapSize_Y

    for (int i=3; i<snakebody.size(); i++) {
        if (snakebody[0].x==snakebody[i].x && snakebody[i].y == snakebody[0].y) {
            return true;
        }
    }
    return false;
}


void snakeclass::start(){
  while(1){
    if(collision()){
      move(12,36);
      printw("gameend");
      break;
    }
    movesnake();
    if(direction=='q')
    break;
    usleep(del);
  }
}
