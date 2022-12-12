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

vector<pair<int, int>> back_buffer;
vector<pair<int, int>> front_buffer;
set<pair<int, int>> visited;

int search_map(vector<vector<int>>& v, int n) {
    while (!front_buffer.empty()) {
        // vector<pair<int, int>> temp;
        n++;
        for (auto pos : front_buffer) {
            int x = pos.first, y = pos.second;
            // cout << x << ", " << y << endl;
            
            auto test = [&v, n, x, y](int nx, int ny) { 
                if (ny >= v.size() || ny < 0) return -1;
                if (nx >= v[0].size() || nx < 0) return -1;
                
                pair<int, int> pos = {nx, ny};
                // if weve not visisted this square before
                if (visited.count(pos) == 0) {
                    if (v[ny][nx] - v[y][x] <= 1 && v[ny][nx] != -1) {
                        back_buffer.push_back(pos);
                        visited.insert(pos);
                    } else if (v[ny][nx] == -1 && v[y][x] >= 25) {
                        return n;
                    }
                    return -1;
                } else {
                    return -1;
                }
            };
            int ret;
#define _test(_x, _y) ret = test((_x), (_y)); if (ret != -1) return ret;
            _test(x + 1, y);
            _test(x - 1, y);
            _test(x, y + 1);
            _test(x, y - 1);
        }
        
        front_buffer.clear();
        front_buffer = back_buffer;
        back_buffer.clear();
    }
    return -1;
}

int main() {
    setIO("input/12");
    
    vector<vector<int>> map;
    vector<pair<int, int>> starting_points;
    
    int sx, sy;
    int ex, ey;
    
    string line;
    for (int y = 0; getline(cin, line); y++) {
        vector<int> v;
        
        for (int x = 0; x < line.length(); x++) {
            char ch = line[x];
            if (ch == 'a') starting_points.push_back({x,y});
            if (ch >= 'a') v.push_back(ch - 'a');
            else if (ch == 'S') {
                v.push_back(0);
                sx = x, sy = y;
            } else if (ch == 'E') {
                v.push_back(-1);
            }
        }
        map.push_back(v);
    }
    front_buffer.push_back({sx, sy});
    
    cout << "Part 1: " << search_map(map, 0) << endl;
    
    int min = INT_MAX;
    starting_points.push_back({sx, sy});
    for (auto p : starting_points) {
        visited.clear();
        front_buffer.clear();
        back_buffer.clear();
        front_buffer.push_back(p);
        
        int ret = search_map(map, 0);
        if (ret < min && ret != -1) min = ret;
    }
    cout << "Part 2: " << min << endl;
}