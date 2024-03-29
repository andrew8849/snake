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
unsigned int warptime = 0;
void printScreen(char ***map);
void push_snake(snake &snake, map &map);
void push_item(map& map, vector<Point> &heart, vector<Point> &poison, vector<two_Point> &gate);
bool crash_check(map &map, snake &snake, vector<Point> &heart, vector<Point> &poison, vector<two_Point> &gate);
int startscreen();
int heartscore = 0;
int poisonscore = 0;
int gatescore = 0;
int mission[4][4] = {{7,1,0,1},{7,1,1,1},{7,2,1,0},{7,2,1,0}}; 
int currentlevel=0;
int snakebody = 0;
int nextlevel_a=0;
int nextlevel_b=0;
int nextlevel_c=0;
int nextlevel_d=0;


int main(){
  WINDOW *main_screen;  // 윈도우 생성
  map_size.x=22;  // 맵 기본사이즈 설정
  map_size.y=22;  // 맵 기본사이즈 설정
  setlocale(LC_ALL,""); // 특수문자 사용을위한 지역설정
  keypad(stdscr, TRUE); // 특수 키 값 입력 허용
  map map(map_size.x,map_size.y); // 맵 객체 생성
  char*** test = map.get_map();  //  맵 수정을 위한 변수생성

  initscr();
  start_color();
  init_pair(1,COLOR_YELLOW,COLOR_BLACK);
  bkgd(COLOR_PAIR(1));
  resize_term(100, 100);  // 윈도우 사이즈 설정

  char Key; // 키입력을 받기위한 변수
  int stage = 1;
  vector<Point> heart;
  vector<Point> poison;
  vector<two_Point> gate;

  unsigned int tick_heart = 0;
  unsigned int tick_poison = 0;
  unsigned int tick_gate = 0;
  if(startscreen() == 'y'){
while(Key!=27){
  snake *Snake = new snake(map_size.x/2+1,map_size.y/2+1);
  heart.clear();
  poison.clear();
  gate.clear();
  tick_heart = 0;
  tick_poison = 0;
  tick_gate = 0;
  while(Key!=27){ // ESC입력시 while문 탈출
      curs_set(0);
      timeout(1);
      map.init_map(); // 맵 초기화
      push_snake(*Snake, map);
      if(heart.size() == 0){
        heart.push_back(map.item_create(true));  // 하트 생성  [뱀 길이 늘어남]
        tick_heart = 0;
      }
      if(poison.size() == 0){
        poison.push_back(map.item_create(false));
        tick_poison = 0;
      }
      if(gate.size()==0){
        gate.push_back(map.gate_create());
        tick_gate = 0;
      }
      push_snake(*Snake, map);
      push_item(map, heart, poison, gate);

      mvprintw(1,50,"scoreboard");
      string tmp = "B : ";
      tmp += to_string(snakebody)+"/"+ to_string(mission[currentlevel][0]);
      mvprintw(2,50,tmp.c_str());

      tmp  ="+ : ";
      tmp  += (to_string(heartscore));
      mvprintw(3,50,tmp.c_str());

      tmp  ="- : ";
      tmp  +=(to_string(poisonscore));
      mvprintw(4,50,tmp.c_str());

      tmp  ="G : ";
      tmp  +=(to_string(gatescore));
      mvprintw(5,50,tmp.c_str());

      mvprintw(7,50,"mission");
      tmp  ="B : ";
      tmp += to_string(mission[currentlevel][0]);
      mvprintw(8,50,tmp.c_str());
      if(snakebody>=mission[currentlevel][0]){
        mvprintw(8,55,"(V)");
        nextlevel_a=1;
      }

      tmp  ="+ : ";
      tmp += to_string(mission[currentlevel][1]);
      mvprintw(9,50,tmp.c_str());
      if(heartscore>=mission[currentlevel][1]){
        mvprintw(9,55,"(V)");
        nextlevel_b=1;
      }

      tmp  ="- : ";
      tmp += to_string(mission[currentlevel][2]);
      mvprintw(10,50,tmp.c_str());
      if(poisonscore>=mission[currentlevel][2]){
        mvprintw(10,55,"(V)");
        nextlevel_c=1;
      }

      tmp  ="G : ";
      tmp += to_string(mission[currentlevel][3]);
      mvprintw(11,50,tmp.c_str());
      if(gatescore>=mission[currentlevel][3]){
        mvprintw(11,55,"(V)");
        nextlevel_d=1;
      }
      test = map.get_map();
      // 화면에 맵 그리기.
      printScreen(test);
      refresh();
      noecho();
      usleep(300000);
      Key = getch();
      Snake->set_direction(Key);
      while(getch()!=EOF);
      clear();

      Snake->move();
      if(Snake->get_size()>=7 && stage <=3&&(nextlevel_a==1&&nextlevel_b==1&&nextlevel_c==1&&nextlevel_d==1)){
        map.setstage(++stage);
        currentlevel++;
         heartscore = 0;
 poisonscore = 0;
 gatescore = 0;
 snakebody = 0;
nextlevel_a=0;
 nextlevel_b=0;
 nextlevel_c=0;
 nextlevel_d=0;        break;
      }
      else if(Snake->crash_check()) { map.setstage(1);stage=1;currentlevel=0;heartscore = 0;
 poisonscore = 0;
 gatescore = 0;
 snakebody = 0;
 nextlevel_a=0;
 nextlevel_b=0;
 nextlevel_c=0;
 nextlevel_d=0;  break; }
      else if(crash_check(map, *Snake, heart, poison, gate)){
        currentlevel=0;heartscore = 0;
 poisonscore = 0;
 gatescore = 0;
 snakebody = 0;
nextlevel_a=0;
 nextlevel_b=0;
 nextlevel_c=0;
 nextlevel_d=0;   
        map.setstage(1);
        stage =1;
        break;
      }
      tick_heart++;
      tick_poison++;
      tick_gate++;
      if(tick_heart > 20+random()%30) heart.pop_back();
      if(tick_poison > 20) poison.pop_back();
      if(tick_gate > 20+warptime) {gate.pop_back(); warptime=0;}
  }
  delete Snake;
  refresh();
  endwin();
}}

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
  for(int i=0; i<body.size();i++){
    map.push_map(body[i].x, body[i].y, "@");
  }
}

void push_item(map& map, vector<Point> &heart, vector<Point> &poison, vector<two_Point> &gate){
    for(int i = 0; i<heart.size();i++){
      map.push_map(heart[i].x,heart[i].y,"♥");
    }
    for(int i = 0; i<poison.size();i++){
      map.push_map(poison[i].x,poison[i].y,"☠");
    }
    for(int i = 0; i<gate.size();i++){
      map.push_map(gate[i].p1.x,gate[i].p1.y,"⬚");
      map.push_map(gate[i].p2.x,gate[i].p2.y,"⬚");
    }
}

bool crash_check(map &map, snake &snake, vector<Point> &heart, vector<Point> &poison, vector<two_Point> &gate){
  vector<Point> body = snake.get_body();
  snakebody = body.size();

  for(int i=0;i<heart.size();i++){
    if(body[0] == heart[i]){
      snake.getItem(true);
      map.delete_item(true);
      heart.erase(heart.begin()+i);
            heartscore++;

      return false;
    }
  }
  for(int i = 0; i<poison.size();i++){
    if(body[0] == poison[i]){
      snake.getItem(false);
      map.delete_item(false);
      poison.erase(poison.begin()+i);
            poisonscore++;

      return false;
    }
  }
  if(strcmp(map.get_position(body[0].x, body[0].y),"⬚")==0){
        gatescore++;

    warptime += body.size();
    Point tmp;
    for(int i=0; i<gate.size();i++){
      if(gate[i].p1 == body[0]) {tmp = gate[i].p2; break;}
      else if(gate[i].p2 == body[0]) {tmp = gate[i].p1; break;}
    }
    if(body[0].x - body[1].x > 0 && body[0].y == body[1].y ){
      if(strcmp(map.get_position(tmp.x+1,tmp.y), "■") != 0
      && strcmp(map.get_position(tmp.x+1,tmp.y), "▦") != 0
      && strcmp(map.get_position(tmp.x+1,tmp.y), "⬚") != 0){
        body[0] = Point(tmp.x+1,tmp.y);
        snake.sethead(body[0]);
      }
      else if(strcmp(map.get_position(tmp.x,tmp.y+1), "■") != 0
      && strcmp(map.get_position(tmp.x,tmp.y+1), "▦") != 0
      && strcmp(map.get_position(tmp.x,tmp.y+1), "⬚") != 0){
        body[0] = Point(tmp.x,tmp.y+1);
        snake.sethead(body[0]);
        snake.set_direction('s');
      }
      else if(strcmp(map.get_position(tmp.x,tmp.y-1), "■") != 0
      && strcmp(map.get_position(tmp.x,tmp.y-1), "▦") != 0
      && strcmp(map.get_position(tmp.x,tmp.y-1), "⬚") != 0){
        body[0] = Point(tmp.x,tmp.y-1);
        snake.sethead(body[0]);
        snake.set_direction('w');
      }
      else if(strcmp(map.get_position(tmp.x-1,tmp.y), "■") != 0
      && strcmp(map.get_position(tmp.x-1,tmp.y), "▦") != 0
      && strcmp(map.get_position(tmp.x-1,tmp.y), "⬚") != 0){
        body[0] = Point(tmp.x-1,tmp.y);
        snake.sethead(body[0]);
        snake.set_direction('w');
        snake.set_direction('a');
      }
    }
    else if(body[0].x - body[1].x < 0 && body[0].y == body[1].y ){
      if(strcmp(map.get_position(tmp.x-1,tmp.y), "■") != 0
      && strcmp(map.get_position(tmp.x-1,tmp.y), "▦") != 0
      && strcmp(map.get_position(tmp.x-1,tmp.y), "⬚") != 0){
        body[0] = Point(tmp.x-1,tmp.y);
        snake.sethead(body[0]);
      }
      else if(strcmp(map.get_position(tmp.x,tmp.y-1), "■") != 0
      && strcmp(map.get_position(tmp.x,tmp.y-1), "▦") != 0
      && strcmp(map.get_position(tmp.x,tmp.y-1), "⬚") != 0){
        body[0] = Point(tmp.x,tmp.y-1);
        snake.sethead(body[0]);
        snake.set_direction('w');
      }
      else if(strcmp(map.get_position(tmp.x,tmp.y+1), "■") != 0
      && strcmp(map.get_position(tmp.x,tmp.y+1), "▦") != 0
      && strcmp(map.get_position(tmp.x,tmp.y+1), "⬚") != 0){
        body[0] = Point(tmp.x,tmp.y+1);
        snake.sethead(body[0]);
        snake.set_direction('s');
      }
      else if(strcmp(map.get_position(tmp.x+1,tmp.y), "■") != 0
      && strcmp(map.get_position(tmp.x+1,tmp.y), "▦") != 0
      && strcmp(map.get_position(tmp.x+1,tmp.y), "⬚") != 0){
        body[0] = Point(tmp.x+1,tmp.y);
        snake.sethead(body[0]);
        snake.set_direction('w');
        snake.set_direction('d');
      }
    }
    else if(body[0].x == body[1].x && body[0].y - body[1].y >0 ){
      if(strcmp(map.get_position(tmp.x,tmp.y+1), "■") != 0
      && strcmp(map.get_position(tmp.x,tmp.y+1), "▦") != 0
      && strcmp(map.get_position(tmp.x,tmp.y+1), "⬚") != 0){
        body[0] = Point(tmp.x,tmp.y+1);
        snake.sethead(body[0]);
      }
      else if(strcmp(map.get_position(tmp.x-1,tmp.y), "■") != 0
      && strcmp(map.get_position(tmp.x-1,tmp.y), "▦") != 0
      && strcmp(map.get_position(tmp.x-1,tmp.y), "⬚") != 0){
        body[0] = Point(tmp.x-1,tmp.y);
        snake.sethead(body[0]);
        snake.set_direction('a');
      }
      else if(strcmp(map.get_position(tmp.x+1,tmp.y), "■") != 0
      && strcmp(map.get_position(tmp.x+1,tmp.y), "▦") != 0
      && strcmp(map.get_position(tmp.x+1,tmp.y), "⬚") != 0){
        body[0] = Point(tmp.x+1,tmp.y);
        snake.sethead(body[0]);
        snake.set_direction('d');
      }
      else if(strcmp(map.get_position(tmp.x,tmp.y-1), "■") != 0
      && strcmp(map.get_position(tmp.x,tmp.y-1), "▦") != 0
      && strcmp(map.get_position(tmp.x,tmp.y-1), "⬚") != 0){
        body[0] = Point(tmp.x,tmp.y-1);
        snake.sethead(body[0]);
        snake.set_direction('a');
        snake.set_direction('w');
      }
    }
    else if(body[0].x == body[1].x && body[0].y - body[1].y <0){
      if(strcmp(map.get_position(tmp.x,tmp.y-1), "■") != 0
      && strcmp(map.get_position(tmp.x,tmp.y-1), "▦") != 0
      && strcmp(map.get_position(tmp.x,tmp.y-1), "⬚") != 0){
        body[0] = Point(tmp.x,tmp.y-1);
        snake.sethead(body[0]);
      }
      else if(strcmp(map.get_position(tmp.x+1,tmp.y), "■") != 0
      && strcmp(map.get_position(tmp.x+1,tmp.y), "▦") != 0
      && strcmp(map.get_position(tmp.x+1,tmp.y), "⬚") != 0){
        body[0] = Point(tmp.x+1,tmp.y);
        snake.sethead(body[0]);
        snake.set_direction('d');
      }
      else if(strcmp(map.get_position(tmp.x-1,tmp.y), "■") != 0
      && strcmp(map.get_position(tmp.x-1,tmp.y), "▦") != 0
      && strcmp(map.get_position(tmp.x-1,tmp.y), "⬚") != 0){
        body[0] = Point(tmp.x-1,tmp.y);
        snake.sethead(body[0]);
        snake.set_direction('a');
      }
      else if(strcmp(map.get_position(tmp.x,tmp.y+1), "■") != 0
      && strcmp(map.get_position(tmp.x,tmp.y+1), "▦") != 0
      && strcmp(map.get_position(tmp.x,tmp.y+1), "⬚") != 0){
        body[0] = Point(tmp.x,tmp.y+1);
        snake.sethead(body[0]);
        snake.set_direction('a');
        snake.set_direction('s');
      }
    }
  }

  if(body.size()<3) return true;
  else if(strcmp(map.get_position(body[0].x, body[0].y),"■")==0){
      return true;
  }
  return false;
}
int startscreen(){
  clear();
  initscr();
  move(10,13);
  printw("start game? (y/n)");
  int gameinput = getch();
  refresh();
  endwin();
  clear();

  return gameinput;
}
//if(startscreen() == 'y')