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
#define _rrange(_x) _x.rbegin(), _x.rend()

enum ord {
    less,
    equal,
    greater,
};

enum packet_type {
    num,
    vec,
};

struct packet;
ord order(packet* p1, packet* p2);

struct packet {
    packet_type item;
    union {
        int num;
        vector<packet*>* vec;
    };
    
    packet(int n) : 
        item {packet_type::num}, 
        num(n)
    {}
    
    packet() :
        item{packet_type::vec},
        vec{new vector<packet*>()}
    {}
    
    void push(int n) {
        vec->push_back(new packet(n));
    }
    
    void push() {
        vec->push_back(new packet());
    }
    
    void push(packet* p) {
        vec->push_back(p);
    }
    
    packet* operator[](size_t idx) {
        return (*vec)[idx];
    }
    
    bool operator<(packet* other) {
        return order(this, other) != ord::greater;
    };
};

packet* from_line(stringstream &ss) {
    packet* p = new packet();
    while(1) {
        switch (ss.peek()) {
        case '[':
            ss.get();
            p->push(from_line(ss));
            break;
        case ']':
            ss.get();
            return p;
        case ',': ss.get(); break;
        default: 
            int n; 
            ss >> n; 
            p->push(n); 
            break;
        }
    }
}

ord order(packet* p1, packet* p2) {
    auto type_1 = p1->item;
    auto type_2 = p2->item;
    
    if (type_1 == type_2) {
        // both are numbers
        if (type_1 == packet_type::num) {
            int a = p1->num, b = p2->num;
            if (a < b) return ord::less;
            if (a > b) return ord::greater;
        }
        // both are lists
        else {
            int len_1 = p1->vec->size();
            int len_2 = p2->vec->size();
            
            // if they are the same length
            repeat (i, min(len_1, len_2)) {
                ord ret = order((*p1)[i], (*p2)[i]);
                if (ret != ord::equal) return ret;
            }
            
            if (len_1 < len_2) return ord::less;
            if (len_1 > len_2) return ord::greater;
        }
    } else {
        packet* p;
        // 1 is num 2 is vec
        if (type_1 == packet_type::num) p = p1;
        // 1 is vec 2 is num
        else p = p2;
        
        int n = p->num;
        *p = packet();
        p->push(n);
        
        return order(p1, p2);
    }
    return ord::equal;
}

bool divider(packet* p) {
    return p->item == packet_type::vec
        && p->vec->size() == 1
        && (*p)[0]->item == packet_type::vec
        && (*p)[0]->vec->size() == 1
        && (*(*p)[0])[0]->item == packet_type::num;
}

int main() {
    setIO("input/13");
    
    vector<string> lines;
    string line;
    while (getline(cin, line)) lines.push_back(line);
    
    int acc = 0;
    vector<packet*> v;
    
    for_range(i, 0, lines.size(), 3) {
        stringstream ss;
        
        ss = stringstream(lines[i]);
        ss.get();
        packet* p1 = from_line(ss);
        v.push_back(p1);
        
        ss = stringstream(lines[i + 1]);
        ss.get();
        packet* p2 = from_line(ss);
        v.push_back(p2);
        
        if (order(p1, p2) != ord::greater) acc += i / 3 + 1;
    }
    
    cout << "Part 1: " << acc << endl;
    
    stringstream s1("[2]]"), s2("[6]]");
    packet* div1 = from_line(s1); 
    packet* div2 = from_line(s2);
    
    v.push_back(div1);
    v.push_back(div2);
    
    acc = 1;
    sort(_range(v), [](packet* a, packet* b) { return order(a, b) != ord::greater; });
    repeat (i, v.size()) if (v[i] == div1 || v[i] == div2) {
        acc *= i + 1;
    }
    
    cout << "Part 2: " << acc << endl;
}