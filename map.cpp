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
  if(stage == 1){
    for(int i = 0 ; i<MapSize_Y; i++){
      for(int j = 0 ; j<MapSize_X; j++){
        strcpy(map_arr[i][j],stage_1[i][j]);
      }
    }
  }
  else if(stage == 2){
    for(int i = 0 ; i<MapSize_Y; i++){
      for(int j = 0 ; j<MapSize_X; j++){
        strcpy(map_arr[i][j],stage_2[i][j]);
      }
    }
  }
}

char ***map::get_map() const{
  /*if(stage == 1){
    return stage_1;
  }*/
  return map_arr;
}
void map::push_map(int x,int y,const char* str){
  strcpy(map_arr[y][x],str);
}

struct Point map::item_create(bool item_type){
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<int> Y(1,MapSize_Y-2); // 아이템 랜덤 위치 Y값
  uniform_int_distribution<int> X(1,MapSize_X-2); // 아이템 랜덤 위치 X값

  int y;
  int x;
  do{
    y=Y(gen);
    x=X(gen);
  }while(strcmp(this->map_arr[y][x],"□") != 0); // 해당 위치가 빈 공간일 때만 아이템 생성
  if(item_type) {heart_count++;} // 하트아이템 갯수 +1 및 하트아이템 맵에 넣기
  else if(!item_type) {poison_count++;}  // 포이즌 아이템 갯수 +1 및 포이즌 아이템 맵에 넣기
  return Point(x,y);
}

void map::delete_item(bool item_type){
  if(item_type) heart_count--;  // 하트 아이템 갯수 -1
  else if(!item_type) poison_count--; // 포이즌 아이템 갯수 -1
}

struct two_Point map::gate_create(){
  srand((unsigned int)time(NULL));
  struct Point gate_1,gate_2;
  do{
    gate_1.x = rand()%22;
    gate_1.y = rand()%22;
  }while(strcmp(map_arr[gate_1.y][gate_1.x],"■")!=0);
  do{
    gate_2.x = rand()%22;
    gate_2.y = rand()%22;
  }while(strcmp(map_arr[gate_2.y][gate_2.x],"■")!=0 && (gate_2.y!=gate_1.y || gate_2.x!=gate_1.x));

  strcpy(map_arr[gate_1.y][gate_1.x],"⬚");
  strcpy(map_arr[gate_2.y][gate_2.x],"⬚");
  return two_Point(gate_1, gate_2);

}

const char* map::get_position(int x,int y) {
  if(x > MapSize_X-1 || y> MapSize_Y-1 || x<0 || y<0) return "■";
  return map_arr[y][x];
}

Point map::get_size(){
  return Point(MapSize_X, MapSize_Y);
}

/*
array map
stage_map = {
                {▦,■,■,■,■,■,■,■,■,■,■,■,■,■,■,■,■,■,■,■,▦,▦,},
                {■,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,■},
                {■,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,■},
                {■,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,■},
                {■,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,■},
                {■,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,■},
                {■,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,■},
                {■,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,■},
                {■,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,■},
                {■,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,■},
                {■,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,■},
                {■,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,■},
                {■,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,■},
                {■,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,■},
                {■,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,■},
                {■,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,■},
                {■,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,■},
                {■,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,■},
                {■,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,■},
                {■,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,■},
                {■,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,□,■},
                {▦,■,■,■,■,■,■,■,■,■,■,■,■,■,■,■,■,■,■,■,▦,▦,}
            }






*/
