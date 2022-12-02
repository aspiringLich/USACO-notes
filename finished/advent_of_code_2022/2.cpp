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


int main() {
    setIO("2");
    
    string line;
    int acc1 = 0, acc2 = 0;
    while (getline(cin, line)) {
        int opp = line[0] - 'A';
        int x = line[2] - 'X';
        
        int res = ((x - opp) % 3 + 3) % 3;
        int table[] = {3, 6, 0};
        int score = table[res] + x + 1;
        acc1 += score;
        
        int you = ((opp - res) % 3 + 3) % 3;
        score = (2 - you) + (x * 3) + 1;
        acc2 += score;
    }
    cout << "Part 1: " << acc1 << endl;
    cout << "Part 2: " << acc2 << endl;
    
}
