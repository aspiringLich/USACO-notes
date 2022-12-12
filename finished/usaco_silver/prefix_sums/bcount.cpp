#include <bits/stdc++.h>
using namespace std;

// source: http://www.usaco.org/index.php?page=viewproblem2&cpid=572
//         USACO 2015 December Silver Contest #3
//
// all test cases passed 


int main() {
    // test with default case; comment out in final code
    // ifstream cin("test.in");
    
    ifstream cin("bcount.in");
    ofstream cout("bcount.out");
    
    // user input
    int len, tests;
    cin >> len >> tests; 
    
    vector<array<int, 3>> v(len + 1);
    
    array<int, 3> counts;
    counts.fill(0);
    
    for (int i = 1; i <= len; i++) {
        int x;
        cin >> x;
        
        counts[x - 1] += 1;
        v[i] = counts;
    }
    
    for (int i = 0; i < tests; i++) {
        int a, b;
        cin >> a >> b;
        
        cout << v[b][0] - v[a - 1][0] << " ";
        cout << v[b][1] - v[a - 1][1] << " ";
        cout << v[b][2] - v[a - 1][2] << endl;
    }
}