#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using ull = unsigned long long;

#define repeat(_i, _x) for (int _i = 0; _i < (_x); ++_i)
#define for_range(_i, _start, _end, _itr) \
    for (int _i = (_start); i < (_end); _i += _itr)

void setIO(const string str = "") {
    ios::sync_with_stdio(false);
#ifdef LOCAL  // compile with -DLOCAL
    cout << "compiled locally" << endl;
    if (str.empty()) freopen("test.in", "r", stdin);
    else {
        freopen((str + ".in").c_str(), "r", stdin);
    }
#else
    if (!str.empty()) {
        freopen((str + ".in").c_str(), "r", stdin);
        freopen((str + ".out").c_str(), "w", stdout);
    }
#endif
}

int main() {
    setIO("1");
    
    int acc = 0, out = 0, i;
    string line;
    
    while (getline(cin, line)) {
        istringstream iss(line);
        
        if (iss >> i) {
            acc += i;
        } else {
            out = max(acc, out);
            acc = 0;
        }
    }
    cout << out << endl;
}
