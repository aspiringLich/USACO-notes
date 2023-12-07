#include <cstring>
#include <initializer_list>
using namespace std;

struct pos {
    int x;
    int y;

    int operator<(const pos &other) const {
        return memcmp(this, &other, sizeof(pos));
    }

    pos() = default;
    pos(int x, int y) : x(x), y(y) {}
    pos(const initializer_list<int> list) {
        auto i = list.begin();
        x = i[0];
        y = i[1];
    }
};