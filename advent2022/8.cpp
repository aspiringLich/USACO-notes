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

int part_1(vector<int> trees, int width, int height) {
    vector<bool> visible(trees.size());
    
    for (int x = 0; x < width; x++) {
        int top = -1, btm = -1;
        // check the top
        for (int y = 0; y < height; y++) {
            int i = x + y * width;
            if (trees[i] > top) {
                visible[i] = true;
                top = trees[i];
            }
        }
        // check the bottom
        for (int y = height - 1; y >= 0; y--) {
            int i = x + y * width;
            int d = trees[i];
            if (trees[i] > btm) {
                visible[i] = true;
                btm = trees[i];
            }
        }
    }
    for (int y = 0; y < height; y++) {
        int lft = -1, rgt = -1;
        // check the left
        for (int x = 0; x < width; x++) {
            int i = x + y * width;
            if (trees[i] > lft) {
                visible[i] = true;
                lft = trees[i];
            }
        }
        // check the right
        for (int x = width - 1; x >= 0; x--) {
            int i = x + y * width;
            if (trees[i] > rgt) {
                visible[i] = true;
                rgt = trees[i];
            }
        }
    }
    
    return count(visible.begin(), visible.end(), true);
}

int part_2(vector<int> trees, int width, int height) {
    int max = 0;
    
    for (int y = 1; y < height - 1; y++) {
        for (int x = 1; x < width - 1; x++) {
            int h = trees[x + y * width];
            int u = 0, d = 0, l = 0, r = 0;
            // count up
            for (int cy = y - 1; cy >= 0; cy--) {
                u++;
                if (trees[x + cy * width] >= h) break;
            }
            // count down
            for (int cy = y + 1; cy < height; cy++) {
                d++;
                if (trees[x + cy * width] >= h) break;
            }
            // count left
            for (int cx = x - 1; cx >= 0; cx--) {
                l++;
                if (trees[cx + y * width] >= h) break;
            }
            // count right
            for (int cx = x + 1; cx < width; cx++) {
                r++;
                if (trees[cx + y * width] >= h) break;
            }
            
            int res = u * d * l * r;
            if (res > max) max = res;
        }
    }
    return max;
}

int main() {
    setIO("8");
    
    vector<int> trees;
    int width = 0, height = 0;
    string line;
    while (getline(cin, line)) {
        width = line.length();
        for (int i = 0; i < line.length();i++) trees.push_back(line[i]);
    }
    height = trees.size() / line.length();
    
    cout << "Part 1: " << part_1(trees, width, height) << endl;
    cout << "Part 2: " << part_2(trees, width, height) << endl;
}
