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
    setIO("input/5");
    const size_t height = 8;
    const size_t size = 9;
    
    string stack_raw[height];
    string line;
    
    for (int i = 0; i < height; i++) {
        getline(cin, line);
        stack_raw[i] = line;
    }
    getline(cin, line);
    // getline(cin, line);
    
    vector<char> stack1[size];
    vector<char> stack2[size];
    for (int i = 0; i < size; i++) { 
        char ch;
        for (int j = height - 1;  j >= 0; j--) {
            ch = stack_raw[j][i * 4 + 1];
            if (ch != ' ') {
                stack1[i].push_back(ch);
                stack2[i].push_back(ch);
            }
        }
    }
    
    while (getline(cin, line)) {
        stringstream ss(line);
        string buf;
        int n, a, b;
        cin >> buf >> n >> buf >> a >> buf >> b;
        a--, b--;
        buf = "";
        
        for (int i = 0; i < n; i++) {
            stack1[b].push_back(stack1[a].back());
            stack1[a].pop_back(); 
            
            buf.push_back(stack2[a].back());
            stack2[a].pop_back();
        }
        while (buf.length()) {
            stack2[b].push_back(buf.back());
            buf.pop_back();
        }
    }
    
    string out1 = "", out2 = "";
    for (int i = 0; i < size; i++) {
        out1.push_back(stack1[i].back());
        out2.push_back(stack2[i].back());
    }
    
    cout << "Part 1: " << out1 << endl;
    cout << "Part 2: " << out2 << endl;
}
