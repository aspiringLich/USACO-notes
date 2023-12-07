#include <bits/stdc++.h>
#include <initializer_list>
using namespace std;

using ll = long long;
using ld = long double;
using ull = unsigned long long;

#define repeat(_i, _x) for (int _i = 0; _i < (_x); ++_i)
#define for_range(_i, _start, _end, _itr)                                      \
    for (int _i = (_start); _i < (_end); _i += _itr)

void setIO(const string str = "") {
    ios::sync_with_stdio(false);
#ifdef LOCAL // compile with -DLOCAL
    cout << "compiled locally" << endl;
    if (str.empty())
        freopen("test.in", "r", stdin);
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

#define _range(_x) _x.begin(), _x.end()
#define _rrange(_x) _x.rbegin(), _x.rend()

struct pos {
    int x;
    int y;

    int operator<(const pos &other) const {
        return memcmp(this, &other, sizeof(pos));
    }

    pos() = default;
    pos(int x, int y) : x(x), y(y) {}
    pos(const initializer_list<int> list) {
        auto i = list.begin();
        x = i[0];
        y = i[1];
    }
};

int main() {
    setIO("fenceplan");

    int cow_n, moo_n;
    cin >> cow_n >> moo_n;

    vector<pos> cows(cow_n);
    vector<unordered_set<int>> moos(cow_n);

    repeat(i, cow_n) {
        cows.push_back(pos());
        cin >> cows[i].x >> cows[i].y;
    }

    repeat(i, moo_n) {
        int a, b;
        cin >> a >> b;
        moos[a - 1].insert(b - 1);
        moos[b - 1].insert(a - 1);
    }

    int min_perimeter = INT_MAX;
    unordered_set<int> visited = {};
    int start = 0;

    while (visited.size() < cow_n) {
        while (visited.count(start))
            start++;

        queue<int> q;
        q.push(start);

        pos min = {INT_MAX, INT_MAX};
        pos max = pos();

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            if (visited.count(current))
                continue;
            visited.insert(current);

            pos &c = cows[current];
            min.x = std::min(min.x, c.x);
            min.y = std::min(min.y, c.y);
            max.x = std::max(max.x, c.x);
            max.y = std::max(max.y, c.y);

            for (int i : moos[current])
                q.push(i);
        }

        int perimeter = (max.x - min.x) * 2 + (max.y - min.y) * 2;
        min_perimeter = std::min(min_perimeter, perimeter);
    }

    cout << min_perimeter;
}
