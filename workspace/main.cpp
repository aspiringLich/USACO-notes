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

// const int testy = 2000000;
const int testy = 10;
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

// const int search_space = 4000000;
const int search_space = 20;

int part_2(vector<sensor>& sensors) {
    
}

// int part_2(vector<sensor>& sensors) {
//     vector<pos> search;
    
//     for (sensor s : sensors) {
//         pos t = s.p, b = s.p, l = s.p, r = s.p;
//         t.y += s.dist + 1, b.y -= s.dist + 1, l.x -= s.dist + 1, r.x += s.dist + 1;
        
//         // if (l.x > search_space) continue;
//         // if (r.x < 0) continue;
//         // if (t.y > search_space) continue;
//         // if (b.y < 0) continue;
        
//         // offsets
//         int left = max(0, -l.x);
//         int right = max(0, r.x - search_space);
        
//         // left -> top
//         for (pos p = l.tr(left); p.y <= t.y && p.y >= 0 && p.y <= search_space; p = p.tr(1)) 
//             search.push_back(p);
        
//         // left -> bottom
//         for (pos p = l.br(left); p.y >= b.y && p.y >= 0 && p.y <= search_space; p = p.br(1)) 
//             search.push_back(p);
        
//         // right -> top
//         for (pos p = r.tl(right); p.y <= t.y && p.y >= 0 && p.y <= search_space; p = p.tl(1)) 
//             search.push_back(p);
        
//         // right -> bottom
//         for (pos p = r.bl(right); p.y >= b.y && p.y >= 0 && p.y <= search_space; p = p.bl(1)) 
//             search.push_back(p);
//     }
    
//     // set<pos> seeearch;
//     // for (auto item : search) seeearch.insert(item);
//     // for_range(x, -10, 30, 1) {
//     //     for_range(y, -10, 30, 1) {
//     //         if (seeearch.count(pos(x, y))) cout << '#';
//     //         else cout << '.';
//     //     }
//     //     cout << '\n';
//     // }
    
//     cout << endl;
//     for (int i = 0; i < search.size(); i++) {
//         pos& p = search[i];
        
//         cout << "\r(" << i << "/" << search.size() << ")";
        
//         for (sensor s : sensors) {
//             if (s.p.dist(p) <= s.dist) goto jmp_out;
//         }
//         cout << endl;
//         cout << "found! " << p.x << ", " << p.y << " (" << p.x * 4000000 + p.y << ")" << endl;
//     jmp_out:;
//     }
// }

int main() {
    setIO();
    
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
