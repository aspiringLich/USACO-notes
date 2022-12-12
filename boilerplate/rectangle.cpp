#include <iostream>
using namespace std;

struct rect {
    int x1, y1, x2, y2;
    
    rect(int x1, int y1, int x2, int y2) : x1{x1}, y1{y1}, x2{x2}, y2{y2} {};
    rect(istream& in) { in >> x1 >> y1 >> x2 >> y2; }
    
    int area() { return (y2 - y1) * (x2 - x1); }
    bool overlap(rect& other) { return !(x1 >= other.x2 || x2 <= other.x1 || y1 >= other.y2 || y2 <= other.y1); }
    int area(rect& other) { return (min(x2, other.x2) - max(x1, other.x1)) * (min(y2, other.y2) - max(y1, other.y1)); }
};