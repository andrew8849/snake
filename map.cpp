#include "map.h"

void map::init_map(){
  map_arr[0][0] = '#';
  map_arr[0][MapSize_X-1] = '#';
  map_arr[MapSize_Y-1][0] = '#';
  map_arr[MapSize_Y-1][MapSize_X-1] = '#';
  for(int i = 1 ;i<MapSize_Y-1;i++){
    map_arr[i][0] = '|';
    map_arr[i][MapSize_X-1] = '|';
  }
  for(int i=1;i<MapSize_X-1;i++){
    map_arr[0][i] = '-';
    map_arr[MapSize_Y-1][i] = '-';
  }
}

char **map::get_map() const{

  return map_arr;
}
