#include "map.cpp"
#include "snake.cpp"
#include <ncurses.h>
#include <clocale>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <string>
using namespace std;

struct map_size{
  int x;
  int y;
};
struct map_size map_size;

void printScreen(char ***map);
void push_snake(snake &snake, map &map);
void push_item(map& map, vector<Point> &heart, vector<Point> &poison, vector<two_Point> &gate);
bool crash_check(map &map, snake &snake, vector<Point> &heart, vector<Point> &poison, vector<two_Point> &gate);
void Scoreboard();
int startscreen();
int heartscore = 0;
int poisonscore = 0;
int gatescore = 0;
int mission[4][4] = {{4,3,2,1},{5,3,2,1},{9,7,3,2},{10,5,2,1}}; 
int currentlevel=0;
int snakebody = 0;
int nextlevel = 0;

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
  vector<two_Point> gate;
  char Key; // 키입력을 받기위한 변수
  if(startscreen() == 'y'){
  while(Key!=27){ // ESC입력시 while문 탈출
      curs_set(0);
      timeout(1);
      map.init_map(); // 맵 초기화
      if(map.heart_count == 0){
        heart.push_back(map.item_create(true));  // 하트 생성  [뱀 길이 늘어남]
      }
      if(map.poison_count == 0){
        poison.push_back(map.item_create(false));
      }
      if(gate.size()==0){
        gate.push_back(map.gate_create());
      }
      /*string tmp(to_string(gate[0].p1.x));
      mvprintw(1,0,tmp.c_str());
      tmp = (to_string(gate[0].p1.y));
      mvprintw(1,5,tmp.c_str());
      tmp = (to_string(gate[0].p2.x));
      mvprintw(2,0,tmp.c_str());
      tmp = (to_string(gate[0].p2.y));
      mvprintw(2,5,tmp.c_str());*/
      push_snake(snake, map);
      push_item(map, heart, poison, gate);

      mvprintw(1,40,"scoreboard");
      string tmp = "B : ";
      tmp += to_string(snakebody)+"/"+ to_string(mission[currentlevel][0]);
      mvprintw(2,40,tmp.c_str());

      tmp  ="+ : ";
      tmp  += (to_string(heartscore));
      mvprintw(3,40,tmp.c_str());

      tmp  ="- : ";
      tmp  +=(to_string(poisonscore));
      mvprintw(4,40,tmp.c_str());

      tmp  ="G : ";
      tmp  +=(to_string(gatescore));
      mvprintw(5,40,tmp.c_str());

      mvprintw(7,40,"mission");
      tmp  ="B : ";
      tmp += to_string(mission[currentlevel][0]);
      mvprintw(8,40,tmp.c_str());
      if(snakebody>=mission[currentlevel][0]){
        mvprintw(8,45,"(V)");
        nextlevel++;
      }

      tmp  ="+ : ";
      tmp += to_string(mission[currentlevel][1]);
      mvprintw(9,40,tmp.c_str());
      if(heartscore>=mission[currentlevel][1]){
        mvprintw(9,45,"(V)");
        nextlevel++;
      }

      tmp  ="- : ";
      tmp += to_string(mission[currentlevel][2]);
      mvprintw(10,40,tmp.c_str());
      if(poisonscore>=mission[currentlevel][2]){
        mvprintw(10,45,"(V)");
        nextlevel++;
      }

      tmp  ="G : ";
      tmp += to_string(mission[currentlevel][3]);
      mvprintw(11,40,tmp.c_str());
      if(gatescore>=mission[currentlevel][3]){
        mvprintw(11,45,"(V)");
        nextlevel++;
      }
/*
nextlevel=4 -> nextlevel
*/


      test = map.get_map();
      // 화면에 맵 그리기.
      printScreen(test);
      refresh();
      noecho();
      usleep(300000);
      Key = getch();
      snake.set_direction(Key);
      while(getch()!=EOF);
      clear();

      snake.move();
      if(snake.crash_check()) break;
      else if(crash_check(map, snake, heart, poison, gate)){
        break;
      }
      
  }
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

void push_item(map& map, vector<Point> &heart, vector<Point> &poison, vector<two_Point> &gate){
    for(int i = 0; i<map.heart_count;i++){
      map.push_map(heart[i].x,heart[i].y,"♥");
    }
    for(int i = 0; i<map.poison_count;i++){
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
    Point tmp;
    gatescore++;
    for(int i=0; i<gate.size();i++){
      if(gate[i].p1 == body[0]) {tmp = gate[i].p2; break;}
      else if(gate[i].p2 == body[0]) {tmp = gate[i].p1; break;}
    }
    if(body[0].x - body[1].x > 0 && body[0].y == body[1].y ){
      if(strcmp(map.get_position(tmp.x+1,tmp.y), "■") != 0 && strcmp(map.get_position(tmp.x+1,tmp.y), "▦") != 0){
        body[0] = Point(tmp.x+1,tmp.y);
        snake.sethead(body[0]);
      }
      else if(strcmp(map.get_position(tmp.x,tmp.y+1), "■") != 0 && strcmp(map.get_position(tmp.x,tmp.y+1), "▦") != 0){
        body[0] = Point(tmp.x,tmp.y+1);
        snake.sethead(body[0]);
        snake.set_direction('s');
      }
      else if(strcmp(map.get_position(tmp.x,tmp.y-1), "■") != 0 && strcmp(map.get_position(tmp.x,tmp.y-1), "▦") != 0){
        body[0] = Point(tmp.x,tmp.y-1);
        snake.sethead(body[0]);
        snake.set_direction('w');
      }
      else if(strcmp(map.get_position(tmp.x-1,tmp.y), "■") != 0 && strcmp(map.get_position(tmp.x-1,tmp.y), "▦") != 0){
        body[0] = Point(tmp.x-1,tmp.y);
        snake.sethead(body[0]);
        snake.set_direction('w');
        snake.set_direction('a');
      }
    }
    else if(body[0].x - body[1].x < 0 && body[0].y == body[1].y ){
      if(strcmp(map.get_position(tmp.x-1,tmp.y), "■") != 0 && strcmp(map.get_position(tmp.x-1,tmp.y), "▦") != 0){
        body[0] = Point(tmp.x-1,tmp.y);
        snake.sethead(body[0]);
      }
      else if(strcmp(map.get_position(tmp.x,tmp.y-1), "■") != 0 && strcmp(map.get_position(tmp.x,tmp.y-1), "▦") != 0){
        body[0] = Point(tmp.x,tmp.y-1);
        snake.sethead(body[0]);
        snake.set_direction('w');
      }
      else if(strcmp(map.get_position(tmp.x,tmp.y+1), "■") != 0 && strcmp(map.get_position(tmp.x,tmp.y+1), "▦") != 0){
        body[0] = Point(tmp.x,tmp.y+1);
        snake.sethead(body[0]);
        snake.set_direction('s');
      }
      else if(strcmp(map.get_position(tmp.x+1,tmp.y), "■") != 0 && strcmp(map.get_position(tmp.x+1,tmp.y), "▦") != 0){
        body[0] = Point(tmp.x+1,tmp.y);
        snake.sethead(body[0]);
        snake.set_direction('w');
        snake.set_direction('d');
      }
    }
    else if(body[0].x == body[1].x && body[0].y - body[1].y >0 ){
      if(strcmp(map.get_position(tmp.x,tmp.y+1), "■") != 0 && strcmp(map.get_position(tmp.x,tmp.y+1), "▦") != 0){
        body[0] = Point(tmp.x,tmp.y+1);
        snake.sethead(body[0]);
      }
      else if(strcmp(map.get_position(tmp.x-1,tmp.y), "■") != 0 && strcmp(map.get_position(tmp.x-1,tmp.y), "▦") != 0){
        body[0] = Point(tmp.x-1,tmp.y);
        snake.sethead(body[0]);
        snake.set_direction('a');
      }
      else if(strcmp(map.get_position(tmp.x+1,tmp.y), "■") != 0 && strcmp(map.get_position(tmp.x+1,tmp.y), "▦") != 0){
        body[0] = Point(tmp.x+1,tmp.y);
        snake.sethead(body[0]);
        snake.set_direction('d');
      }
      else if(strcmp(map.get_position(tmp.x,tmp.y-1), "■") != 0 && strcmp(map.get_position(tmp.x,tmp.y-1), "▦") != 0){
        body[0] = Point(tmp.x,tmp.y-1);
        snake.sethead(body[0]);
        snake.set_direction('a');
        snake.set_direction('w');
      }
    }
    else if(body[0].x == body[1].x && body[0].y - body[1].y <0){
      if(strcmp(map.get_position(tmp.x,tmp.y-1), "■") != 0 && strcmp(map.get_position(tmp.x,tmp.y-1), "▦") != 0){
        body[0] = Point(tmp.x,tmp.y-1);
        snake.sethead(body[0]);
      }
      else if(strcmp(map.get_position(tmp.x+1,tmp.y), "■") != 0 && strcmp(map.get_position(tmp.x+1,tmp.y), "▦") != 0){
        body[0] = Point(tmp.x+1,tmp.y);
        snake.sethead(body[0]);
        snake.set_direction('d');
      }
      else if(strcmp(map.get_position(tmp.x-1,tmp.y), "■") != 0 && strcmp(map.get_position(tmp.x-1,tmp.y), "▦") != 0){
        body[0] = Point(tmp.x-1,tmp.y);
        snake.sethead(body[0]);
        snake.set_direction('a');
      }
      else if(strcmp(map.get_position(tmp.x,tmp.y+1), "■") != 0 && strcmp(map.get_position(tmp.x,tmp.y+1), "▦") != 0){
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
void Scoreboard(){
  initscr();
  start_color();
  WINDOW *ScoreBoard;
  WINDOW *MissionBoard;

  
  ScoreBoard = newwin(15,15,2,40);
  MissionBoard = newwin(15,15,20,40);
  wbkgd(ScoreBoard, COLOR_PAIR(3));
  wbkgd(MissionBoard, COLOR_PAIR(3));
  box(ScoreBoard, 0,0);//세로, 가로 경계선 스타일
  box(MissionBoard, 0,0);
/*
  string score_b = "B: ";
  score_b +=snakesize;
  //score_b +=to_string("/"+ mission[0][0]);
  string score_plus = "+: ";
  score_plus +=to_string(fruiteat);
  string score_minus = "-: ";
  score_minus +=to_string(poisoneat);
  string gate_count = "G: ";
  gate_count +=to_string(gatethrough);

  mvwprintw(ScoreBoard, 0, 1, "ScoreBoard");
  mvwprintw(ScoreBoard, 2, 1, score_b.c_str());
  mvwprintw(ScoreBoard, 4, 1, score_plus.c_str());
  mvwprintw(ScoreBoard, 6, 1, score_minus.c_str());
  mvwprintw(ScoreBoard, 8, 1, gate_count.c_str());
*/
  mvwprintw(MissionBoard, 0, 1, "MissionBoard");
  mvwprintw(MissionBoard, 2, 1, "B:");
  mvwprintw(MissionBoard, 4, 1, "+:");
  mvwprintw(MissionBoard, 6, 1, "-:");
  mvwprintw(MissionBoard, 8, 1, "G:");
  refresh();

/*
  if(body.length()>=mission[mission_num][0]){
      mvwprintw(MissionBoard, 2, 4, "v");
      mission_finished++;
  }
  if(fruiteat>=mission[mission_num][1]){
    mvwprintw(MissionBoard, 4, 4, "v");
      mission_finished++;
  }
  if(poisoneat>=mission[mission_num][2]){
    mvwprintw(MissionBoard, 6, 4, "v");
      mission_finished++;
  }
  if(gate_count>=mission[mission_num][3]){
    mvwprintw(MissionBoard, 8, 4, "v");
      mission_finished++;
  }

  if(mission_finished>=4){
    다음 레벨
  }*/
  // B,+,-,G 
}
