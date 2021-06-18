#include "map.cpp"
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

int main(){
  WINDOW *main_screen;  // 윈도우 생성
  map_size.x=21;  // 맵 기본사이즈 설정
  map_size.y=21;  // 맵 기본사이즈 설정
  setlocale(LC_ALL,""); // 특수문자 사용을위한 지역설정
  keypad(stdscr, TRUE); // 특수 키 값 입력 허용
  map map(map_size.x,map_size.y); // 맵 객체 생성
  char*** test =map.get_map();  //  맵 수정을 위한 변수생성

  initscr();
  start_color();
  init_pair(1,COLOR_YELLOW,COLOR_BLACK);
  bkgd(COLOR_PAIR(1));
  resize_term(100, 100);  // 윈도우 사이즈 설정

  char Key; // 키입력을 받기위한 변수
  struct two_Point gate;
  while(Key!=27){ // ESC입력시 while문 탈출
      curs_set(0);
      timeout(1);

      // 화면에 맵 그리기.
      printScreen(test);
      refresh();
      //noecho();
      Key = getch();
      while(getch()!=EOF);
      usleep(500000);
      clear();
      map.init_map(); // 맵 초기화
      map.item_create(false); // 독 생성  [뱀 길이 줄어듦]
      map.item_create(true);  // 하트 생성   [뱀 길이 늘어남]
      gate = map.gate_create();  // 게이트 생성
      string tmp(to_string(gate.p1.x));
      mvprintw(0,0,tmp.c_str());
      tmp = to_string(gate.p1.y);
      mvprintw(0,5,tmp.c_str());
      tmp = to_string(gate.p2.x);
      mvprintw(1,0,tmp.c_str());
      tmp = to_string(gate.p2.y);
      mvprintw(1,5,tmp.c_str());

  }
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
