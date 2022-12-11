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

int get_priority(char c) {
    if (c >= 'a' && c <= 'z')  return c - 'a' + 1;
    else if (c >= 'A' && c <= 'Z') return c - 'A' + 27;
    return 0;
}

int part_1(vector<string> *lines) {
    int priority = 0;
    for (string line : *lines) {
        unordered_set<int> s;
        string a = line.substr(0, line.length() / 2);
        string b = line.substr(line.length() / 2);
        
        char same = '!';
        for (char c : a) s.insert(c);
        for (char c : b) {
            if (s.count(c)) {
                same = c;
                break;
            }
        }
        
        priority += get_priority(same);
    }
    return priority;
}

int part_2(vector<string> *lines) {
    string a, b, c;
    int priority = 0;
    
    for (int i = 0; i < lines->size(); i+=3) {
        a = (*lines)[i];
        b = (*lines)[i+1];
        c = (*lines)[i+2];
        
        set<char> set_a;
        set<char> set_b;
        set<char> set_c;
        for (char ch : a) set_a.insert(ch);
        for (char ch : b) set_b.insert(ch);
        for (char ch : c) set_c.insert(ch);
        
        vector<char> insc(set_a.size());
        auto end = set_intersection(_range(set_a), _range(set_b), insc.begin());
        insc.resize(end - insc.begin());
        end = set_intersection(_range(insc), _range(set_c), insc.begin());
        insc.resize(end - insc.begin());
        
        priority += get_priority(insc.begin()[0]);
    }
    return priority;
}

int main() {
    setIO("input/3");
    
    vector<string> lines;
    string line;
    while (getline(cin, line)) lines.push_back(line);
    
    cout << "Part 1: " << part_1(&lines) << endl;
    cout << "Part 2: " << part_2(&lines) << endl;
}
