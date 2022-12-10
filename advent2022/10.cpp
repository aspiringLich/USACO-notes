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

int part_1(vector<string> &lines) {
    vector<int> check_values = { 220, 180, 140, 100, 60, 20 };
    int x = 1, clock = 1, acc = 0;
    
    for (string line : lines) {
        stringstream ss(line);
        string buf;
        int next;
        
        ss >> buf;
        if (buf == "addx") {
            next = clock + 2;
        } else if (buf == "noop") {
            next = clock + 1;
        }
        
        for (;clock < next; clock++) {
            int back = check_values.back();
            if (clock == back) {
                check_values.pop_back();
                acc += back * x;
            }
        }
        
        if (buf == "addx") {
            int v;
            ss >> v;
            x += v;
        }
    }
    return acc;
}

void part_2(vector<string> &lines) {
    int x = 1, clock = 1, acc = 0;
    
    for (string line : lines) {
        stringstream ss(line);
        string buf;
        int next;
        
        ss >> buf;
        if (buf == "addx") {
            next = clock + 2;
        } else if (buf == "noop") {
            next = clock + 1;
        }
        
        for (;clock < next; clock++) {
            int pos = (clock - 1) % 40;
            int diff = pos - x;
            
            if (abs(diff) <= 1) cout << "#";
            else cout << " ";
            
            if (clock % 40 == 0) cout << endl;
        }
        
        if (buf == "addx") {
            int v;
            ss >> v;
            x += v;
        }
    }
}

int main() {
    setIO("10");
    
    vector<string> lines;
    string line;
    while (getline(cin, line)) lines.push_back(line);
    
    cout << "Part 1: " << part_1(lines) << endl;
    cout << "Part 2: " << endl;
    part_2(lines);
}