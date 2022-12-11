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

int main() {
    setIO("input/4");
    
    string line;
    int ovlp = 0, cntn = 0;
    while (getline(cin, line)) {
        stringstream ss(line);
        string buffer;
        getline(ss, buffer, '-');
        int a = stoi(buffer);
        getline(ss, buffer, ',');
        int b = stoi(buffer);
        getline(ss, buffer, '-');
        int c = stoi(buffer);
        getline(ss, buffer);
        int d = stoi(buffer);
        
        bool contains = ((a >= c) && (b <= d)) || ((a <= c) && (b >= d));
        if ((c <= b && c >= a) || (d <= b && d >= a) || contains) {
            ovlp++;
            if (contains) cntn++;
        }
    }
    
    cout << "Part 1: " << cntn << endl;
    cout << "Part 2: " << ovlp << endl;
}
