#include "map.h"

map::map(){
    map_arr = new char**[MapSize_Y];
    for(int i=0;i<MapSize_X;i++){
       map_arr[i] = new char *[MapSize_X];
       for(int j=0;j<MapSize_X;j++){
         map_arr[i][j] = new char[4];
         strcpy(map_arr[i][j],"□");
       }
    }
    init_map();

}

map::map(int X, int Y) :MapSize_X(X),MapSize_Y(Y){
  map_arr = new char**[MapSize_Y];
  for(int i=0;i<MapSize_X;i++){
     map_arr[i] = new char *[MapSize_X];
     for(int j=0;j<MapSize_X;j++){
       map_arr[i][j] = new char[4];
       strcpy(map_arr[i][j],"□");
     }
  }
  init_map();
}

void map::init_map(){
  strcpy(map_arr[0][0],"▦");
  strcpy(map_arr[0][MapSize_X-1],"▦");
  strcpy(map_arr[MapSize_Y-1][0],"▦");
  strcpy(map_arr[MapSize_Y-1][MapSize_X-1],"▦");
  for(int i = 1 ;i<MapSize_Y-1;i++){
    strcpy(map_arr[i][0],"■");
    strcpy(map_arr[i][MapSize_X-1],"■");
  }
  for(int i=1;i<MapSize_X-1;i++){
    strcpy(map_arr[0][i],"■");
    strcpy(map_arr[MapSize_Y-1][i],"■");
  }
  for(int i=1;i<MapSize_X-1;i++){
    for(int j=1;j<MapSize_Y-1;j++){
      strcpy(map_arr[j][i],"□");
    }
  }
}

char ***map::get_map() const{
  return map_arr;
}
void map::push_map(int x,int y,char* str){
  strcpy(map_arr[y-1][x-1],str);
}

struct Point map::item_create(bool item_type){
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<int> Y(1,MapSize_Y-2); // 아이템 랜덤 위치 Y값
  uniform_int_distribution<int> X(1,MapSize_X-2); // 아이템 랜덤 위치 X값
  int y=Y(gen);
  int x=X(gen);
  if(item_type) {strcpy(map_arr[y][x],"♥"); heart_count++;} // 하트아이템 갯수 +1 및 하트아이템 맵에 넣기
  else if(!item_type) {strcpy(map_arr[y][x],"☠"); poison_count++;}  // 포이즌 아이템 갯수 +1 및 포이즌 아이템 맵에 넣기
  struct Point p(x,y);
  return p;
}

void map::delete_item(bool item_type){
  if(item_type) heart_count--;  // 하트 아이템 갯수 -1
  else if(!item_type) poison_count--; // 포이즌 아이템 갯수 -1
}

struct two_Point map::gate_create(){
  srand((unsigned int)time(NULL));
  struct Point gate_1,gate_2;
  switch(rand()%4){
    case 0:
      gate_1.x = rand()%(MapSize_X-2)+1;
      gate_1.y = 0;
      break;
    case 1:
      gate_1.x = MapSize_X-1;
      gate_1.y = rand()%(MapSize_Y-2)+1;
      break;
    case 2:
      gate_1.x = rand()%(MapSize_X-2)+1;
      gate_1.y = MapSize_Y-1;
      break;
    case 3:
      gate_1.x = 0;
      gate_1.y = rand()%(MapSize_Y-2)+1;
      break;
  }
  switch(rand()%4){
    case 0:
      do{
        gate_2.x = rand()%(MapSize_X-2)+1;
        gate_2.y = 0;
      }while(gate_1.x==gate_2.x && gate_1.y==gate_2.y);
      break;
    case 1:
      do{
        gate_2.x = MapSize_X-1;
        gate_2.y = rand()%(MapSize_Y-2)+1;
      }while(gate_1.x==gate_2.x && gate_1.y==gate_2.y);
      break;
    case 2:
      do{
        gate_2.x = rand()%(MapSize_X-2)+1;
        gate_2.y = MapSize_Y-1;
      }while(gate_1.x==gate_2.x && gate_1.y==gate_2.y);
      break;
    case 3:
      do{
        gate_2.x = 0;
        gate_2.y = rand()%(MapSize_Y-2)+1;
      }while(gate_1.x==gate_2.x && gate_1.y==gate_2.y);
      break;
  }
  strcpy(map_arr[gate_1.y][gate_1.x],"⬚");
  strcpy(map_arr[gate_2.y][gate_2.x],"⬚");
  two_Point p(gate_1, gate_2);
  return p;
}

char* map::get_position(int x,int y){
  return map_arr[y][x];
}
