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
#define _rrange(_x) _x.rbegin(), _x.rend()

// Source: http://www.usaco.org/index.php?page=viewproblem2&cpid=1183
//         USACO 2022 January Contest, Silver #2
//
// all test cases passed

int main() {
    setIO();
    
    int len;
    cin >> len; 
    vector<int> cows(len);
    repeat(i, len) cin >> cows[i];
    
    vector<pair<int, int>> stack;
    
    stack.push_back({0, cows[0]});
    ull acc = 0;
    for_range(i, 1, len, 1) {
        while (!stack.empty() && stack.back().second < cows[i]) {
            if (stack.empty()) {
                break;
            } else {
                acc += i - stack.back().first + 1;
                stack.pop_back();
            }
        }
        if (!stack.empty()) acc += i - stack.back().first + 1;
        stack.push_back({i, cows[i]});
    }
    
    cout << acc;
}
