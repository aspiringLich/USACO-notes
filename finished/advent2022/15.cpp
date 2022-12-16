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


struct pos {
    int x;
    int y;
    
    pos () : x(0), y(0) {};
    pos (int x, int y) : x(x), y(y) {};
    
    int dist(pos& other) {
        return abs(x - other.x) + abs(y - other.y);
    }
    
    pos tr(int n) {
        return pos(x+n, y+n);
    }
    
    pos tl(int n) {
        return pos(x-n, y+n);
    }
    
    pos bl(int n) {
        return pos(x-n, y-n);
    }
    
    pos br(int n) {
        return pos(x+n, y-n);
    }
    
    bool operator<(pos const &other) const {
        return *(ull*)this < *(ull*)&other;
    }
};

struct sensor {
    pos p;
    int dist;
};

const int testy = 2000000;
// const int testy = 10;
vector<int> sack;

int part_1(vector<sensor>& sensors) {
    vector<pair<int, int>> intervals;
    for (sensor s : sensors) {
        int diff = abs(testy - s.p.y);
        int x = (s.dist - diff);
        if (x < 1) continue;
        int l = s.p.x - x;
        int r = s.p.x + x;
        intervals.push_back({l, r});
    }
    
    set<int> seen;
    for (auto pair : intervals) {
        for_range(i, pair.first, pair.second + 1, 1) seen.insert(i);
    }
    
    for (auto i : sack) seen.erase(i);
    
    return seen.size();
}

const int search_space = 4000000;
// const int search_space = 20;

ull part_2(vector<sensor>& sensors) {
    vector<int> edges[4];
    
    for (sensor s : sensors) {
        int p = s.p.y - s.p.x;
        int n = s.p.y + s.p.x;
        edges[0].push_back(p - s.dist);
        edges[1].push_back(p + s.dist);
        edges[2].push_back(n - s.dist);
        edges[3].push_back(n + s.dist);
    }
    
    set<int> pos_edge;
    set<int> neg_edge;
    
    for (auto p : edges[0]) {
        bool b = false;
        for (auto check : edges[1]) {
            if (check - 2 == p) pos_edge.insert(p + 1);
            if (check + 2 == p) pos_edge.insert(p - 1);
        }
    }
    for (auto p : edges[2]) {
        bool b = false;
        for (auto check : edges[3]) {
            if (check - 2 == p) neg_edge.insert(p + 1);
            if (check + 2 == p) neg_edge.insert(p - 1);
        }
    }
    set<pos> check;
    
    for (int p : pos_edge) {
        for (int n : neg_edge) {
            // x + p = -x + n
            // 2x + p - n = 0
            // 2x = n - p
            if ((n - p) % 2 == 0) {
                int ans = (n - p) / 2;
                if (ans < 0 || ans > search_space) continue;
                if (ans + p < 0 || ans + p > search_space) continue; 
                check.insert(pos(ans, ans + p));
            }
        }
    }
    
    for (auto p : check) {
        for (sensor s : sensors) {
            if (s.p.dist(p) <= s.dist) goto jmp_out;
        }
        return (ull)p.x * (ull)4000000 + (ull)p.y ;
    jmp_out:;
    }
}

int main() {
    setIO("input/15");
    
    vector<sensor> sensors;
    
    string line;
    
    while (getline(cin, line)) {
        stringstream ss(line);
        sensor s;
        ss.ignore(sizeof("Sensor at x=")-1);
        ss >> s.p.x;
        ss.ignore(sizeof(", y=")-1);
        ss >> s.p.y;
        
        int x, y;
        ss.ignore(sizeof(": closest beacon is at x=")-1);
        ss >> x;
        ss.ignore(sizeof(", y=")-1);
        ss >> y;
        
        pos beacon(x, y);
        
        if (y == testy) sack.push_back(x);

        s.dist = s.p.dist(beacon);
        sensors.push_back(s);
    }
    
    cout << "Part 1: " << part_1(sensors) << endl;
    cout << "Part 2: " << part_2(sensors) << endl;
}
