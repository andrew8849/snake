#include "map.cpp"
#include <ncurses.h>
#include <clocale>
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
  curs_set(0);
  //noecho();

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
      for(int i = 0 ; i<map_size.y;i++){
        for(int j=0; j<map_size.x; j++){
          mvprintw(i+5,(j*2)+5,test[i][j]);
        }
      }
      mvprintw(1,1,&i);
      refresh();
      map.init_map();
      sleep(1);
      map.item_create(false);
      map.gate_create();

      i++;
      clear();
  }

  main_screen = newwin(map_size.y,map_size.x,5,5);
  wbkgd(main_screen, COLOR_PAIR(1));
  wattron(main_screen, COLOR_PAIR(1));
  mvwprintw(main_screen, 1, 1, "A new window");
  wborder(main_screen, '@','@','@','@','@','@','@','@');
  wrefresh(main_screen);

  getch();
  delwin(main_screen);
  endwin();
  return 0;

}
