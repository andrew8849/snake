struct Point{
  int x = 0;
  int y = 0;
  Point(int _x, int _y) : x(_x), y(_y){};
  Point(){};
  bool operator==(Point p){
    if(p.x==x && p.y==y) return true;
    return false;
  }

  Point operator-(Point p){
    return Point(x-p.x, y-p.y);
  }
};

struct two_Point{
  struct Point p1;
  struct Point p2;
  two_Point(struct Point _p1, struct Point _p2){
    p1.x = _p1.x;
    p1.y = _p1.y;
    p2.x = _p2.x;
    p2.y = _p2.y;
  };
  two_Point(){};
};
