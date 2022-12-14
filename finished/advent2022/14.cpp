#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using ull = unsigned long long;

#define repeat(_i, _x) for(int _i = 0; _i < (_x); ++_i)
#define for_range(_i, _start, _end, _itr) for (int _i = (_start); _i < (_end); _i += _itr)

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
#define _rrange(_x) _x.rbegin(), _x.rend()

const int left_pad = 0;

struct cave {
    vector<vector<bool>> inner;
    
    bool y_in_bounds(int x, int y) {
        return y < inner[x].size();
    }
    
    bool in_bounds(int x, int y) {
        return x < inner.size() && y < inner[x].size();
    }
    
    vector<bool>& operator[](size_t idx) {
        return inner[idx];
    }
    
    size_t size() {
        return inner.size();
    }
};

int part_1(cave& orig_cave) {
    int acc;
    cave cave = orig_cave;
    for (acc = 0; ; acc++) {
        // cout << acc << endl;
        // repeat (x, cave.size()) {
        //     bool flag = false;
        //     repeat (y, cave[x].size()) {
        //         flag = true;
        //         if (cave[x][y] && orig_cave[x][y]) cout << '#';
        //         else if (cave[x][y] && !orig_cave[x][y]) cout << 'o';
        //         else cout << '.';
        //     }
        //     if (flag) cout << endl;
        // }
        
        int x = 500 - left_pad, y = 0;
        
        
        while (true) {
            while (!cave[x][y+1]) {
                if (!cave.y_in_bounds(x, y+1)) return acc;
                y++;
            }
            // check bottom left
            if (cave.in_bounds(x-1,y+1)) { if (!cave[x-1][y+1]) {
                x--; 
                y++; 
                // cave[x][y] = true;
                continue;
            }} else return acc;
            
            // check bottom right
            if (cave.in_bounds(x+1,y+1)) { if (!cave[x+1][y+1]) {
                x++;
                y++;
                // cave[x][y] = true;
                continue;
            }}
            else return acc;
            
            // both are occupied
            cave[x][y] = true;
            break;
        }
    }
}

int part_2(cave& orig_cave, int maxy) {
    int acc;
    cave cave = orig_cave;
    // resize everything
    for (auto& v : cave.inner) {
        v.resize(maxy + 2);
        v[maxy + 1] = true;
    }
    
    for (acc = 0; ; acc++) {
        // cout << acc << endl;
        // for_range (x, 0, maxy + 2, 1) {
        //     bool flag = false;
        //     for_range (y, 500 - maxy - 2, 500 + maxy + 2, 1) {
        //         flag = true;
        //         if (cave[y][x]) cout << '#';
        //         // else if (cave[x][y] && !orig_cave[x][y]) cout << 'o';
        //         else cout << '.';
        //     }
        //     if (flag) cout << endl;
        // }
            
        int x = 500 - left_pad, y = 0;
        
        if (cave[x][y]) return acc;
        
        while (true) {
            while (!cave[x][y+1]) {
                if (!cave.y_in_bounds(x, y+1)) return acc;
                y++;
            }
            // check bottom left
            if (x >= 1) { if (!cave[x-1][y+1]) {
                x--; 
                y++; 
                // cave[x][y] = true;
                // acc++;
                continue;
            }}
            else return acc;
            
            // check bottom right
            if (x < cave.size() - 1) { if (!cave[x+1][y+1]) {
                x++;
                y++;
                // cave[x][y] = true;
                // acc++;
                continue;
            }}
            else return acc;
            
            // both are occupied
            cout << x << ", " << y << endl;
            cave[x][y] = true;
            break;
        }
    }
}

int main() {
    setIO("input/14");
    
    vector<vector<bool>> vec;
    
    string line;
    int maxy = 0;
    while (getline(cin, line)) {
        stringstream ss(line);
        int x1, y1, x2, y2;
        
        ss >> x1, ss.ignore(1), ss >> y1;
        x1 -= left_pad;
        
        while (ss.get() != EOF) {
            ss.ignore(3);
            ss >> x2, ss.ignore(1), ss >> y2;
            x2 -= left_pad;
            
            auto x = minmax(x1 + 1, x2 + 1);
            auto y = minmax(y1 + 1, y2 + 1);
            if (y.second > maxy) maxy = y.second;
            
            if (vec.size() < x.second) vec.resize(x.second);
            
            // its a vertical line
            if (x1 == x2) {
                if (vec[x1].size() < y.second) vec[x1].resize(y.second, false);
                for_range(i, y.first-1, y.second, 1) {
                    vec[x1][i] = true;
                    // cout << x1 << ", " << i << endl;
                }
            } 
            // its a horizontal line
            else if (y1 == y2) {
                for_range(i, x.first-1, x.second, 1) {
                    if (vec[i].size() < y1) vec[i].resize(y.second);
                    vec[i][y1] = true;
                    // cout << i << ", " << y1 << endl;
                }
            } 
            // scream and panic
            else abort();
            
            x1 = x2, y1 = y2;
        }
    }
    
    cave c = cave { vec };
    
    cout << "Part 1: " << part_1(c) << endl;
    
    vec.resize(1001);
    c = cave { vec };
    cout << "Part 2: " << part_2(c, maxy) << endl;
}
