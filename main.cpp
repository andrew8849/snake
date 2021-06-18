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

int main(){
  WINDOW *main_screen;

  struct map_size map_size;
  map_size.x=21;
  map_size.y=21;
  setlocale(LC_ALL,"");
  keypad(stdscr, TRUE);
  map map(map_size.x,map_size.y);
  char*** test =map.get_map();

  initscr();
  start_color();
  init_pair(1,COLOR_YELLOW,COLOR_BLACK);

  bkgd(COLOR_PAIR(1));
  resize_term(100, 100);
  border('*', '*', '*', '*', '*', '*', '*', '*');
  refresh();



  char Key;
  char i = '0';

  while(Key!=27){
      curs_set(0);
      timeout(0);
      keypad(stdscr, false);
      // 화면에 맵 그리기.
      for(int i = 0 ; i<map_size.y;i++){
        for(int j=0; j<map_size.x; j++){
          mvprintw(i+5,(j*2)+5,test[i][j]);
        }
      }
      refresh();
      Key = getch();
      while(getch()!=EOF);
      mvprintw(0,0,&Key);
      usleep(500000);
      clear();
      map.init_map();
      map.item_create(false);
      map.item_create(true);
      map.gate_create();

  }
  endwin();
  return 0;

}
