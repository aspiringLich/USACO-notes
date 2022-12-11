#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using ld = long double;
using ull = unsigned long long;

#define repeat(_i, _x) for(ull _i = 0; _i < (_x); ++_i)
#define for_range(_i, _start, _end, _itr) for (ull _i = (_start); i < (_end); _i += _itr)

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

enum operation {
    addition,
    multiplication,
    squaring,
};

struct monkey {
    vector<ull> items;
    operation op;
    ull factor;
    ull test_factor;
    ull if_true;
    ull if_false;
};

vector<monkey> parse_input(vector<string>& lines) {
    vector<monkey> monkeys;
    
    // input parsing:
    for (ull i = 0; i < lines.size(); i += 7) {
        monkey m;
        string buf;
        stringstream ss;
        ull n = i;
        
        // 0 | Monkey 0:
        // 1 |   Starting items: 79, 98
        ss = stringstream(lines[++n]);
        ss.ignore(sizeof("  Starting items:"));
        while (getline(ss, buf, ',')) {
            m.items.push_back(stoi(buf));
        }
        // 2 |   Operation: new = old * 19
        ss = stringstream(lines[++n]);
        ss.ignore(sizeof("  Operation: new = old"));
        switch (ss.get()) {
            case '*': m.op = multiplication; break;
            case '+': m.op = addition; break;
        }
        ss >> buf;
        if (buf.find("old") < buf.size()) m.op = squaring;
        else m.factor = stoi(buf);
        // 3 |   Test: divisible by 23
        ss = stringstream(lines[++n]);
        ss.ignore(sizeof("  Test: divisible by"));
        ss >> m.test_factor;
        // 4 |     If true: throw to monkey 2
        ss = stringstream(lines[++n]);
        ss.ignore(sizeof("    If true: throw to monkey"));
        ss >> m.if_true;
        // 5 |     If false: throw to monkey 0
        ss = stringstream(lines[++n]);
        ss.ignore(sizeof("    If false: throw to monkey"));
        ss >> m.if_false;
        // now we should be done
        monkeys.push_back(m);
    }
    return monkeys;
}

vector<ull> inspected_1;

void do_round_1(vector<monkey>& monkeys) {
    for (ull i = 0; i < monkeys.size(); i++) {
        monkey& m = monkeys[i];
        inspected_1[i] += m.items.size();
        for (ull& item : m.items) {
            // "monkey inspects item"
            switch (m.op) {
                case addition:       item += m.factor; break;
                case multiplication: item *= m.factor; break;
                case squaring:       item *= item;     break;
            }
            // "monkey gets bored with item"
            item /= 3;
            // divisibility test
            if (item % m.test_factor == 0) {
                monkeys[m.if_true].items.push_back(item);
            } else {
                monkeys[m.if_false].items.push_back(item);
            }
        }
        // weve thrown them all out so clear
        m.items.clear();
    }
}

vector<ull> inspected_2;
ull gcf = 1;

void do_round_2(vector<monkey>& monkeys) {
    for (ull i = 0; i < monkeys.size(); i++) {
        monkey& m = monkeys[i];
        inspected_2[i] += m.items.size();
        for (ull& item : m.items) {
            item %= gcf;
            // "monkey inspects item"
            switch (m.op) {
                case addition:       item += m.factor; break;
                case multiplication: item *= m.factor; break;
                case squaring:       item *= item;     break;
            }
            // divisibility test
            if (item % m.test_factor == 0) {
                monkeys[m.if_true].items.push_back(item);
            } else {
                monkeys[m.if_false].items.push_back(item);
            }
        }
        // weve thrown them all out so clear
        m.items.clear();
    }
}

int main() {
    setIO("input/11");
    
    vector<string> lines;
    string line;
    while (getline(cin, line)) lines.push_back(line);
    
    vector<monkey> monkeys = parse_input(lines);
    inspected_1 = vector<ull>(monkeys.size());
    inspected_2 = vector<ull>(monkeys.size());
    
    for (ull i = 0; i < 20; i++) do_round_1(monkeys);
    
    monkeys = parse_input(lines);
    
    for (auto m : monkeys) {
        gcf *= m.test_factor;
    } 
    // vector<ull> checks = { 10000, 9000, 8000, 7000, 6000, 5000, 4000, 3000, 2000, 1000, 20, 1 };
    for (ull i = 0; i < 10000; i++) {
        do_round_2(monkeys);
        // if (i == checks.back() - 1) {
        //     cout << "Round " << checks.back() << endl;
        //     for (ull j = 0; j < inspected_2.size(); j++) {
        //         cout << "Monkey " << j << ": " << inspected_2[j] << endl;
        //     }
        //     cout << endl;
        //     checks.pop_back();
        // }
    }
    sort(_rrange(inspected_1));
    sort(_rrange(inspected_2));
    
    cout << "Part 1: " << inspected_1[0] * inspected_1[1] << endl;
    cout << "Part 2: " << inspected_2[0] * inspected_2[1] << endl;
}
