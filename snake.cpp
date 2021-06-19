#include "snake.h"

using namespace std;

snake::snake(int x, int y){
  struct Point head(x-1,y);
  body.push_back(head);
  body.push_back(Point(x,y));
  body.push_back(Point(x+1,y));
  body.push_back(Point(x+2,y));
  body.push_back(Point(x+3,y));
}
void snake::sethead(Point p){
  body[0] = p;
  head = p;
}

void snake::getItem(bool item_type){
  if(item_type){
    body.push_back(tail);
  }
  else{
    body.pop_back();
  }
}

void snake::move(){
  switch(direction){
    case 'l':
      tail = body[body.size()-1]; // 현재 꼬리부분 위치 저장 [나중에 아이템 먹었을 경우 이 부분을 push_back하면 길이가 늘어남]
      for(int i = body.size()-1; i>0;i--) body[i]=body[i-1];  // 꼬리부터 머리까지 쉬프트 [머리 몸통1 꼬리가 있을 때 꼬리 = 몸통1, 몸통1 = 머리가 된다.]
      body[0] = Point(body[0].x-1, body[0].y); // 머리부분 해당 방향으로 이동
      head = body[0]; // head에 머리 위치 저장
      break;
    case 'u':
      tail = body[body.size()-1];
      for(int i = body.size()-1; i>0;i--) body[i]=body[i-1];
      body[0] = Point(body[0].x, body[0].y-1);
      head = body[0];
      break;
    case 'r':
      tail = body[body.size()-1];
      for(int i = body.size()-1; i>0;i--) body[i]=body[i-1];
      body[0] = Point(body[0].x+1, body[0].y);
      head = body[0];
      break;
    case 'd':
      tail = body[body.size()-1];
      for(int i = body.size()-1; i>0;i--) body[i]=body[i-1];
      body[0] = Point(body[0].x, body[0].y+1);
      head = body[0];
      break;
  }
}

bool snake::crash_check(){
  for(int i = 1; i < body.size(); i++){
    if(head == body[i]){
      return true;
    }
  }
  return false;
}
void snake::set_direction(char direct){
  switch(direct){
    case 'a':
      if(direction != 'r') direction = 'l';
      break;
    case 'w':
      if(direction != 'd') direction = 'u';
      break;
    case 'd':
      if(direction != 'l') direction = 'r';
      break;
    case 's':
      if(direction != 'u') direction = 'd';
      break;
  }
};

vector<Point> snake::get_body(){
  return body;
}
int snake::get_size(){
  return body.size();
}
