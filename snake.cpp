#include "snake.h"

using namespace std;

snakeloc::snakeloc(){
  x = 0;
  y = 0;
}
snakeloc::snakeloc(int col, int row){
  y = col;
  x = row;
}

snakeclass::snakeclass(){
  body = 'x';
  snakelength = 3;
  direction = 'l';
  fruit.x = 0;
  fruit.y = 0;
  del = 50000;
  getmaxyx(stdscr,maxheight,maxwidth);
  drawsnake();
  movesnake();
  collision();
  fruitplus();
  //poisonminus();
  //refresh();
}
snakeclass::~snakeclass(){
  nodelay(stdscr,false);
  getch();
  endwin();
}

void snakeclass::drawsnake(){
  for(int i=0; i<3; i++){
    snakebody.push_back(snakeloc(30+i,10));
  }
  for(int i=0; i<snakebody.size(); i++){
    move(snakebody[i].y,snakebody[i].x);
    addch(body);
}
return;
}

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
  }
  if(direction=='l'){
    snaketail.insert(snaketail.begin(), snakehead);
    snakehead = snakeloc(snakehead.y-1,snakehead.x);
  }
  else if(direction=='r'){
    snaketail.insert(snaketail.begin(), snakehead);
    snakehead = snakeloc(snakehead.y,snakehead.x);
  }
  else if(direction=='u'){
    snaketail.insert(snaketail.begin(), snakehead);
    snakehead = snakeloc(snakehead.y-1,snakehead.x);
  }
  else if(direction=='d'){
    snaketail.insert(snaketail.begin(), snakehead);
    snakehead = snakeloc(snakehead.y-1,snakehead.x);
  }
  move(snakehead.y,snakehead.x);
  addch(' ');
  refresh();
  if(!fruitplus()){
    move(snakebody[snakebody.size()-1].y, snakebody[snakebody.size()-1].x);
    printw(" ");
    refresh;
    snakebody.pop_back();
  }
  return;


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

    for (int i=0; i<snakebody.size(); i++) {
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
