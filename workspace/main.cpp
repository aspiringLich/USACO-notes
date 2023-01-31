#include <bits/stdc++.h>
#include <cstddef>
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

enum dir {
    R,
    D,
};

struct pos {
    int x = 0;
    int y = 0;

    pos() = default;
    pos(int x, int y) : x(x), y(y) {}

    int operator<(const pos &p) const { return memcmp(this, &p, sizeof(pos)); }

    pos(const initializer_list<int> list) {
        auto i = list.begin();
        x = *i;
        i++;
        y = *i;
    }
};

struct tree {
    set<pos> contained;
    int cost;
};

struct tile {
    dir d;
    int tree;
};

int N;

struct farm {
    vector<vector<tile>> v;

    farm(int N) { v = vector<vector<tile>>(N, vector<tile>(N, tile{R, 0})); }

    tile *get(pos p) {
        if (p.x < 0 || p.y < 0)
            return nullptr;
        if (p.x >= N || p.y >= N)
            return nullptr;
        return &v[p.y][p.x];
    }

    int tree_at(pos p) {
        if (p.x >= N)
            return p.y;
        if (p.y >= N)
            return N + p.x;
        return get(p)->tree;
    }
};

ull cost(vector<tree> &trees) {
    ull c = 0;
    for (auto &t : trees) {
        c += (ull)t.cost * t.contained.size();
    }
    return c;
}

set<pos> search(farm &farm, pos p, const dir d, const bool backwards = false, const bool yee = false) {
    queue<pair<pos, dir>> q;
    set<pos> visited;
    set<pos> out;
    
    visited.insert(p);
    out.insert(p);
    if (yee) {
        q.push({p, D});
        q.push({p, R});
    } else {
        q.push({p, d});
    }

    while (!q.empty()) {
        pos p;
        dir d;
        tie(p, d) = q.front();
        q.pop();

        if (visited.count(p) != 0)
            continue;
        visited.insert(p);

        auto tile = farm.get(p);
        if (tile == nullptr)
            continue;
        if (tile->d != d)
            continue;
        out.insert(p);

        q.push({{p.x - 1, p.y}, backwards ? D : R});
        q.push({{p.x, p.y - 1}, backwards ? R : D});
    }

    return out;
}

int main() {
    setIO();

    cin >> N;

    // first N-1 are the right trees, last N-1 are the down trees
    vector<tree> trees(N * 2);
    farm farm(N);

    // get input
    repeat(i, N) {
        string s;
        int cost;
        cin >> s >> cost;

        trees[i].cost = cost;

        repeat(j, s.size()) {
            if (s[j] == 'D') {
                farm.get({j, i})->d = D;
            }
        }
    }
    repeat(i, N) cin >> trees[N + i].cost;

    auto reconstruct_tree = [&](const int n) {
        set<pos> visited;

        if (n >= N) {
            visited = search(farm, {n - N, N - 1}, D);
        } else {
            visited = search(farm, {N - 1, n}, R);
        }

        trees[n].contained = visited;
        for (auto &p : visited) {
            farm.get(p)->tree = n;
        }
    };

    // construct trees
    repeat(i, N * 2) { reconstruct_tree(i); }

    int rounds;
    cin >> rounds;

    cout << cost(trees) << endl;

    repeat(i, rounds) {
        pos p;
        cin >> p.y >> p.x;
        p.x--, p.y--;
        
        // swap dir
        tile &t = *farm.get(p);
        t.d = t.d == R ? D : R;
        tree& orig = trees[t.tree];

        // get the tree that will inherit all these tiles
        tree& tree = trees[0];
        if (t.d == R) {
            tree = trees[farm.tree_at({p.x + 1, p.y})];
        } else {
            tree = trees[farm.tree_at({p.x, p.y + 1})];
        }
        // get all the tiles that should be moved, remove them from the original tree
        // add them to the new tree
        set<pos> ret = search(farm, p, D, true, true);
        set_union(_range(ret), _range(tree.contained), inserter(tree.contained, tree.contained.begin()));
        set_difference(_range(orig.contained), _range(ret), inserter(orig.contained, orig.contained.begin()));

        cout << cost(trees) << endl;
    }
    // cout << "";
}
