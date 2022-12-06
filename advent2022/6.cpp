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

int part_1_and_2(string input, int len) {
    map<char, int> m;
    
    for (int i = 0; i < len - 1; i++) m[input[i]]++;

    for (int i = len - 1; i < input.length(); i++) {
        m[input[i]]++;
        bool flag = false;
        for (auto item : m) {
            if (item.second > 1) {
                flag = true;
                break;
            }
        }
        if (flag) m[input[i - (len - 1)]]--;
        else return i + 1;
    }
    return -1;
}

int main() {
    setIO("6");
    
    string input = "";
    cin >> input;
    
    cout << "Part 1: " << part_1_and_2(input, 4) << endl;
    cout << "Part 2: " << part_1_and_2(input, 14) << endl;
}
