#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using ull = unsigned long long;

#define repeat(_i, _x) for(int _i = 0; _i < (_x); ++_i)
#define for_range(_i, _start, _end, _itr) for (int _i = (_start); i < (_end); _i += _itr)

void setIO(const string str = "") {
    ios::sync_with_stdio(false);
#ifdef LOCAL // compile with -DLOCAL
    cout << "compiled locally" << endl;
    if (str.empty()) freopen("test.in", "r", stdin);
    else {
        freopen((str + ".in").c_str(), "r", stdin);
    }
#else
    if (!str.empty()) { 
        freopen((str + ".in").c_str(),"r",stdin);
        freopen((str + ".out").c_str(),"w",stdout);
    }
#endif
}

#define _range(_x) _x.begin(), _x.end() 

struct pos {
    int x;
    int y;
    
    pos () {
        x = 0;
        y = 0;
    }
    
    pos(int x, int y) {
        this->x = x;
        this->y = y;
    }
    
    bool operator < (pos const &other) const {
        return memcmp(this, &other, sizeof(pos)) < 0;
    }
    
    bool operator == (pos const &other) const {
        return memcmp(this, &other, sizeof(pos)) == 0;
    }
};

int sgn(int val) {
    return (0 < val) - (val < 0);
}

int main() {
    setIO("9");
    
    set<pos> visited_1;
    set<pos> visited_2;
    // head at the front, tail at the back
    const int knots_n = 10;
    pos knots[knots_n];
    
    visited_1.insert(pos());
    visited_2.insert(pos());
    
    string line;
    while (getline(cin, line)) {
        stringstream ss(line);
        string dir;
        int n, dx, dy;
        ss >> dir >> n;
        char d = dir[0];
        
        pos& head = knots[0];
        // keep movin the head
        for (int itr = 0; itr < n; itr++) { 
            switch (d) {
                case 'U': head.y++; break;
                case 'D': head.y--; break;
                case 'L': head.x--; break;
                case 'R': head.x++; break;
            } 
            // move those knots around
            for (int i = 1; i < knots_n; i++) {
                pos& front = knots[i - 1];
                pos& back = knots[i];
                
                dx = front.x - back.x;
                dy = front.y - back.y;
                
                if (abs(dx) > 1 || abs(dy) > 1) {
                    back.x += sgn(dx);
                    back.y += sgn(dy);
                }
                
                switch (i) {
                    // insert the front-most tail
                    case 1: visited_1.insert(back); break;
                    // insert the back-most tail
                    case 9: visited_2.insert(back); break;
                }
            }
        }
    }
    
    cout << "Part 1: " << visited_1.size() << endl;
    cout << "Part 2: " << visited_2.size() << endl;
}
