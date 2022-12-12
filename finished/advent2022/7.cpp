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


#define IMAP map<string, item*>

struct item  {
    IMAP children;
    int size;
    
    item () {
        this->children = IMAP();
        this->size = 0;
    }
    
    item (int size) {
        this->children = IMAP();
        this->size = size;
    }
    
    int calc_size() {
        if (this->children.empty()) return this->size;
        for (auto item : this->children) this->size += item.second->calc_size();
        return this->size;
    }
};

vector<int> get_dir_sizes(item* root) {
    if (root->children.empty()) return vector<int>();
    vector<int> v;
    v.push_back(root->size);
    for (auto item : root->children) {
        for (auto size : get_dir_sizes(item.second)) v.push_back(size);
    }
    return v;
}

int main() {
    setIO("input/7");
    
    item root = item();
    item* ptr = &root;
    vector<item*> stack;
    
    string line;
    while (getline(cin, line)) {
        stringstream ss(line);
        string buf;
        ss >> buf;
        // command
        if (buf == "$") {
            ss >> buf;
            if (buf == "cd") {
                ss >> buf;
                if (buf == "..")  {
                    ptr = stack.back();
                    stack.pop_back();
                } else if (buf == "/") {
                    stack.clear();
                    ptr = &root;
                } else {
                    stack.push_back(ptr);
                    ptr = ptr->children[buf];
                }
            }
        } else if (buf == "dir") {
            ss >> buf;
            ptr->children[buf] = new item();
        } else {
            int size = stoi(buf);
            ss >> buf;
            ptr->children[buf] = new item(size);
        }
    }
    root.calc_size();
    
    vector<int> sizes = get_dir_sizes(&root);
    
    const int limit = 100000;
    
    int acc = 0;
    for (int i : sizes) {
        if (i < limit) acc += i;
    }
    
    cout << "Part 1: " << acc << endl;
    
    const int free_space = 30000000;
    const int filesystem_size = 70000000;
    int space_left = filesystem_size - root.size;
    int target_space = free_space - space_left;

    int min = INT_MAX;
    for (int i : sizes) {
        if (i > target_space && i < min) min = i;
    }
    
    cout << "Part 2: " << min << endl;
}
