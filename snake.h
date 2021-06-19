#ifndef SNAKE_H
#define SNAKE_H

using namespace std;

#include <vector>

class snake{
private:
  struct Point head;
  struct Point tail;
  vector<Point> body;
  unsigned int size;

public:
  char direction = 'l';
  snake(int x, int y);
  void sethead(Point p);
  void getItem(bool item_type);
  void move();
  bool crash_check();
  void set_direction(char direct);
  vector<Point> get_body();
};
#endif
