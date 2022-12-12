#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using ull = unsigned long long;

#define repeat(_i, _x) for(int _i = 0; _i < (_x); ++_i)
#define for_range(_i, _start, _end, _itr) for (int _i = (_start); i < (_end); _i += _itr)

void setIO(const string str = "", const bool flag = true) {
    ios::sync_with_stdio(false);
#ifdef LOCAL // compile with -DLOCAL
    cout << "compiled locally" << endl;
    if (str.empty() && flag) freopen("test.in", "r", stdin);
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

// Source: http://www.usaco.org/index.php?page=viewproblem2&cpid=1182
//         USACO 2022 January Contest, Silver #1
// 
// all test cases passed

int calc() {
    int acc = 0;
    ull a, b;
    cin >> a >> b;
    
    // make sure a and b are within the same ballpark
    if (a > b) {
        do {
            if (a % 2 == 1) {
                acc++;
                a++;
            }
            a /= 2;
            acc++;
        } while (a > b);
    } else if (b >= a * 2) {
        do {
            if (b % 2 == 1) {
                b--;
                acc++;
            }
            b /= 2;
            acc++;
        } while (b >= a * 2);
    }
    if (a == b) return 0;
    
    // int initial = acc;
    
    int dif = b - a;
    while (1) {
        // cout << "(" << initial << " + " << acc - initial << ") " << a << " + " << dif << endl;
        if (a % 2) {
            a++;
            dif--;
            acc++;
            // cout << "(" << initial << " + " << acc - initial << ") " << a << " + " << dif << endl;
        }
        if (dif % 2) {
            dif--;
            acc++;
            // cout << "(" << initial << " + " << acc - initial << ") " << a << " + " << dif << endl;
        }
        
        if (dif <= 3) return dif + acc;
        a /= 2;
        dif /= 2; 
        acc += 2;
    }
}


int main() {
    setIO();
    
    int len;
    cin >> len; 
    
    repeat(i, len) cout << calc() << endl;
}
