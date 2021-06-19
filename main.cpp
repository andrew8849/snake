#include "map.cpp"
#include "snake.cpp"
#include <ncurses.h>
#include <clocale>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

struct map_size{
  int x;
  int y;
};
struct map_size map_size;

void printScreen(char ***map);
void push_snake(snake &snake, map &map);
void push_item(map& map, vector<Point> &heart, vector<Point> &poison);
void crash_check(map &map, snake &snake, vector<Point> &heart, vector<Point> &poison);
int main(){
  WINDOW *main_screen;  // 윈도우 생성
  map_size.x=12;  // 맵 기본사이즈 설정
  map_size.y=12;  // 맵 기본사이즈 설정
  setlocale(LC_ALL,""); // 특수문자 사용을위한 지역설정
  keypad(stdscr, TRUE); // 특수 키 값 입력 허용
  map map(map_size.x,map_size.y); // 맵 객체 생성
  char*** test =map.get_map();  //  맵 수정을 위한 변수생성

  initscr();
  start_color();
  init_pair(1,COLOR_YELLOW,COLOR_BLACK);
  bkgd(COLOR_PAIR(1));
  resize_term(100, 100);  // 윈도우 사이즈 설정

  snake snake(map_size.x/2+1,map_size.y/2+1);
  vector<Point> heart;
  vector<Point> poison;
  char Key; // 키입력을 받기위한 변수
  struct two_Point gate;
  while(Key!=27){ // ESC입력시 while문 탈출
      curs_set(0);
      timeout(1);
      map.init_map(); // 맵 초기화
      push_snake(snake, map);
      push_item(map, heart, poison);
      test = map.get_map();
      // 화면에 맵 그리기.
      printScreen(test);
      refresh();
      noecho();
      usleep(500000);
      Key = getch();
      snake.set_direction(Key);
      while(getch()!=EOF);
      clear();

      snake.move();
      if(snake.crash_check()) break;
      if(map.heart_count == 0){
        heart.push_back(map.item_create(true));  // 하트 생성   [뱀 길이 늘어남]
      }
      crash_check(map, snake, heart, poison);
      //map.item_create(false); // 독 생성  [뱀 길이 줄어듦]
      //map.item_create(true);  // 하트 생성   [뱀 길이 늘어남]
      //gate = map.gate_create();  // 게이트 생성
      //vector<Point> v = snake.get_body();
      //string tmp(to_string(v[0].y));
      //mvprintw(0,0,tmp.c_str());
  }
  string tmp(to_string(Key));
  mvprintw(0,0,tmp.c_str());
  refresh();
  endwin();
  return 0;
}

void printScreen(char ***map){
  for(int i = 0 ; i<map_size.y;i++){
    for(int j=0; j<map_size.x; j++){
      mvprintw(i+5,(j*2)+5,map[i][j]);
    }
  }
}

void push_snake(snake &snake, map &map){
  vector<Point> body = snake.get_body();
  string tmp(to_string(body.size()));
  mvprintw(0,0,tmp.c_str());
  for(int i=0; i<body.size();i++){
    map.push_map(body[i].x, body[i].y, "@");
  }
}

void push_item(map& map, vector<Point> &heart, vector<Point> &poison){
    for(int i = 0; i<map.heart_count;i++){
      map.push_map(heart[i].x,heart[i].y,"♥");
    }
    for(int i = 0; i<map.poison_count;i++){
      map.push_map(poison[i].x,poison[i].y,"☠");
    }
}

void crash_check(map &map, snake &snake, vector<Point> &heart, vector<Point> &poison){
  vector<Point> body = snake.get_body();
  for(int i=0;i<heart.size();i++){
    if(body[0] == heart[i]){
      snake.getItem(true);
      map.heart_count--;
      heart.erase(heart.begin()+i);
    }
  }
}
