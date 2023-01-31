#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using ull = unsigned long long;

#define repeat(_i, _x) for(int _i = 0; _i < (_x); ++_i)
#define for_range(_i, _start, _end, _itr) for (int _i = (_start); _i < (_end); _i += _itr)

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

struct valve_raw {
    int rate;
    vector<string> tunnels;
};

struct valve{
    string name;
    int rate;
    vector<pair<valve&, int>> tunnels;
    
    valve() : rate(0), tunnels() {};
    valve(int rate, string name) : name(name), rate(rate), tunnels() {};
};

// struct state {
//     valve* on;
//     set<string> visited;
//     set<string> opened;
//     int rate, total, n;
    
//     void inc() {
//         total += rate;
//     }
// };
    
// map<tuple<set<string>, string>, pair<int, int>> max_flow;
// int max_total[31] = {};

map<pair<valve*, valve*>, int> distances;
map<string, valve> valves;

// int total(vector<valve*>& list) {
//     int n = 0;
//     int total = 0;
//     valve* on = &valves["AA"];
//     // string debug = "";
//     // go through every valve
//     for (valve* valve : list) {
//         // go to that valve, if theres not enough space nevermind
//         int dist = distances[{valve, on}] + 1;
//         if (n + dist >= 30) {
//             return total;
//         }
//         n += dist;
//         on = valve;
//         total += (30 - n) * valve->rate;
//         // debug += "(" + to_string(n) + ") - " + valve->name + " " + to_string(total) + "\n";
//     }
//     return total;
// }

set<pair<valve*, int>> childrens_children(valve* v) {
    set<pair<valve*, int>> s;
    for (auto item : v->tunnels) {
        int dist = item.second;
        s.insert({&item.first, dist});
        for (auto child : item.first.tunnels) {
            s.insert({&child.first, dist + child.second});
        }
    }
    return s;
}

// void search(valve* on, vector<valve*> path) {
//     for (auto item : on->tunnels) {
//         valve* to = &item.first;
//         if (find(_range(path), to) != path.end()) continue;
//         path.push_back(to);
//         search(to, path);
//         path.pop_back();
//     }
// }

struct state {
    valve* on;
    set<valve*> visited;
    int total;
    int n;
};

int part_1() {
    // set<state> visited;
    queue<state> q;
    
    q.push(state { &valves["AA"], set<valve*> { &valves["AA"] }, 0, 0 });
    
    int ans = 0;
    for (int i = 0; q.size() != 0;) {
        state& s = q.front();
        auto itr = childrens_children(s.on);
        bool flag = true;
        for (auto item : itr) {
            valve* v = item.first; 
            int dist = item.second+1;
            // returns
            if (s.n + dist >= 30) continue;
            if (s.visited.count(v)) continue;
            flag = false;
            // new state
            state n = s;
            n.n += dist;
            n.total += (30 - n.n) * v->rate;
            if (n.total > ans) ans = n.total;
            n.on = v;
            n.visited.insert(v);
            q.push(n);
        }
        if (flag) {
            for (auto item : s.on->tunnels) {
                valve* v = &item.first; 
                int dist = item.second;
                // returns
                if (s.n + dist >= 30) continue;
                // new state
                state n = s;
                n.n += dist;
                // n.total += (30 - n.n) * v->rate;
                // if (n.total > ans) ans = n.total;
                n.on = v;
                n.visited.insert(v);
                q.push(n);
            }
        }
        q.pop();
    }
    return ans;
}

int main() {
    setIO("input/16");
    
    map<string, valve_raw> valves_raw;
    
    string line;
    while (getline(cin, line)) {
        valve_raw v;
        char name[3];
        sscanf(line.c_str(), 
            "Valve %s has flow rate=%d", 
            &name, 
            &v.rate
        );
        valves_raw.insert({name, v});
        valve_raw& v_ref = valves_raw[name];
        
        auto itr = line.rbegin();
        while (true) {
            string name = "";
            name += *itr++;
            name += *itr++;
            itr += 2;
            if (!(name[0] >= 'A' && name[0] <= 'Z')) break;
            v_ref.tunnels.push_back(name);
        }
    }
    
    for (auto v : valves_raw)  
        if (v.second.rate || v.first == "AA") valves[v.first] = valve(v.second.rate, v.first);
    
    for (auto& v : valves) {
        string name = v.first;
        valve& valve = v.second;
        set<string> visited { name };
        
        queue<string> q;
        for (auto c : valves_raw[name].tunnels) q.push(c);
        
        int i = 0;
        while (!q.empty()) {
            i++;
            auto to = q.front();
            q.pop();
            if (valves.count(to)) {
                valve.tunnels.push_back({valves[to], i});
                continue;
            }
            // if (valves_raw.count(to)) {
            //     cout << "";
            // }
            for (auto child : valves_raw[to].tunnels) {
                if (visited.count(child)) continue;
                visited.insert(child);
                    q.push(child);
            }
        }
        
        if (valve.tunnels.empty()) {
            cout << "!" << endl;
        }
    }
    
    for (auto& _from: valves) {
        valve& from = _from.second;
    }
    // total(valves);
    cout << "Part 1: " << part_1() << endl;
}


