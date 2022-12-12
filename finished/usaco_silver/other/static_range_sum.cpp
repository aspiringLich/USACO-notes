#include <bits/stdc++.h>
using namespace std;

// source: https://judge.yosupo.jp/problem/static_range_sum
//
// all test cases passed

using u64 = uint64_t;

int main() {
    // test with default case; comment out in final code
    ifstream cin("test.in");
    
    // input
    u64 len, tests;
    cin >> len >> tests; 
    vector<u64> v(len + 1);
    for (auto it = (v.begin() + 1); it != v.end(); it++) cin >> *it;
    
    partial_sum(v.begin(), v.end(), v.begin());
    
    for (u64 i = 0; i < tests; i++) {
        u64 a, b;
        cin >> a >> b;
        cout << (v[b] - v[a]) << endl;
    }
}
