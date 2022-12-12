#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using db = double; 
using ull = unsigned long long;

#define repeat(_i, _x) for(int _i = 0; _i < (_x); ++_i)
#define for_range(_i, _start, _end, _itr) for (int _i = (_start); i < (_end); _i += _itr)

void setIO(const string str = "") {
    ios::sync_with_stdio(false);
#ifdef LOCAL // compile with -DLOCAL
    freopen("test.in","r",stdin);
#else
    if (!str.empty()) { 
        freopen((str + ".in").c_str(),"r",stdin);
        freopen((str + ".out").c_str(),"w",stdout);
    }
#endif
}

// Source: http://www.usaco.org/index.php?page=viewproblem2&cpid=738
//         USACO 2017 US Open Contest, Silver #1
// 
// all test cases passed

int main() {
    setIO("pairup");
    
    int len;
    cin >> len; 
    
    map<int, int> count;
    
    repeat(i, len) {
        int cnt, prd;
        cin >> cnt >> prd;
        count[prd] += cnt;
    }
    
    auto front = begin(count);
    auto back = end(count);
    back--;
    int out = 0;
    
    while (front != back) {
        if (front->first + back->first > out)
            out = front->first + back->first;
        
        front->second--;
        back->second--;
        if (!front->second) front++;
        if (!back->second) back--;
    }
    cout << out;
}