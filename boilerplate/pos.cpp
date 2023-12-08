#include <initializer_list>
#include <iostream>
using namespace std;

struct pos {
    int x, y;

    friend bool operator<(const pos &l, const pos &r) {
        if (l.x < r.x)
            return true;
        return l.y < r.y;
    }
    friend bool operator==(const pos &l, const pos &r) {
        return l.x == r.x && l.y == r.y;
    }
    istream &operator>>(istream &is) { return is >> x >> y; }

    pos() = default;
    pos(int x, int y) : x(x), y(y) {}
    pos(const initializer_list<int> list) {
        auto i = list.begin();
        x = i[0], y = i[1];
    }
};

struct rect {
    int x1, y1, x2, y2;

    friend bool operator==(const rect &l, const rect &r) {
        return l.x1 == r.x1 && l.y1 == r.y1 && l.x2 == r.x2 && l.y2 == r.y2;
    }
    istream &operator>>(istream &is) { return is >> x1 >> y1 >> x2 >> y2; }

    rect() = default;
    rect(int x1, int y1, int x2, int y2) : x1{x1}, y1{y1}, x2{x2}, y2{y2} {};
    rect(const initializer_list<int> list) {
        auto i = list.begin();
        x1 = i[0], y1 = i[1], x2 = i[2], y2 = i[3];
    }

    // get the area of the rectangle
    int area() { return (y2 - y1) * (x2 - x1); }
    // get the area enclosed by the overlap of the rectangles
    int area(rect &other) {
        return (min(x2, other.x2) - max(x1, other.x1)) *
               (min(y2, other.y2) - max(y1, other.y1));
    }

    // get the perimeter of the rectangle
    int perimeter() { return (x2 - x1) * 2 + (y2 - y1) * 2; }

    // get the rectangle overlapping this rectangle
    rect overlap(rect &other) {
        return {
            max(x1, other.x1),
            max(y1, other.y1),
            min(x2, other.x2),
            min(y2, other.y2),
        };
    }
    // check if the rectangles intersect
    bool intersect(rect &other) {
        return !(x1 >= other.x2 || x2 <= other.x1 || y1 >= other.y2 ||
                 y2 <= other.y1);
    }

    // include a point within the bounds of the rectangle
    void bounds(pos &p) {
        x1 = min(x1, p.x);
        y1 = min(y1, p.y);
        x2 = max(x2, p.x);
        y2 = max(y2, p.y);
    }
};

// ---

#include <cassert>

int main() {
    rect r1(0, 0, 5, 5);
    rect r2(2, 2, 7, 7);

    assert(r1.overlap(r2) == rect(2, 2, 5, 5));
    assert(r1.area(r2) == 9);
    assert(r1.perimeter() == 20 && r2.perimeter() == 20);
}