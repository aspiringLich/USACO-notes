# USACO Notes
## Data Structures
### Common Methods
- these are methods that may be shared between data structures
```cpp
x.size();               // # of elements
x.resize();             // resize x to a given element count
x.capacity();           // how much it could hold rn
x.empty();              // is x empty?
x[0] = 0;               // index into x
x.erase();              // erase something
x.count(y);             // does y show up? / how many times
x.insert(y);            // stick y in there somewhere
```

### `array<T>` [docs](https://cplusplus.com/reference/array/array/)
- compile-time size
```cpp
//  1 2 4 6 0
array<int, 5> a;        // int arr w/ len 5
a.fill(0);              // fill w/ 0
a[1] = 1;               // index into array
a.size();               // size of a
a.empty();              // if a is empty
a.front();              // the front
a.back();               // the back
```

### `vector<T>` [docs](https://cplusplus.com/reference/vector/vector/)
- standard growable array
```cpp
vector<int> v;          // empty
vector<int> v(0, 25);   // 25 0's
vector<int> copy(v);    // copy v into copy
v.resize(30);

// prints 0 25 times
for (int item : v) cout << item << endl;

v[1] = 1;               // index into vec
v.size();               // size of v
v.front();              // the front
v.back();               // the back
v.push_back(1);         // push 1 into the back
v.pop_back();           // destroy last element
v.clear();              // goodbye
```

### `string` [docs](https://cplusplus.com/reference/string/string/)
- store strings of characters (noway)
```cpp {linenos=false}
string s;               // empty string
string s = "string";    // "string"

// s t r i n g
for (char ch : s) cout << ch << ' ';

string s;
cin >> s;               // get input from stdin
getline(cin, s);        // get a line from stdin
cout << s << endl;      // write to stdout

char buf[20];
s.copy(buf, 0, 3);      // copy [0,3) into buf, ret 3-0
s.substring(0, 3);      // returns [0,3) of s

s[0] = 's';             // index into string
s += str;               // append, string -> stringstr

t.push_back('r');       // push a ch, str -> strr
t.pop_back();           // pop a ch, strr -> str
```

### `pair` [docs](https://cplusplus.com/reference/utility/pair/pair/)
- pretty simple: a pair of two types
```cpp
pair<int, int> a = {0, 1};
a.first == 0;
a.second == 1;
```

### `tuple` [docs](https://cplusplus.com/reference/tuple/tuple/)
```cpp
tuple<int, int> pair = {0, 1};
get<1>(pair); // 1 HAS TO BE CONSTANT
tuple<string, float, int> tup = {"lala", 0.1, 492};
```

### `unordered_set<T>` [docs](https://cplusplus.com/reference/unordered_set/unordered_set/)
- store unique elements
- faster for searching by key
```cpp
unordered_set<int> s;
s.insert(1);            // {1}
s.insert(4);            // {1, 4}
s.insert(1);            // does nothing
s.count(1);             // 1
s.erase(1);             // {2}
s.count(5)              // 0
s.erase(0);             // does nothing
```

### `set<T>` [docs](https://cplusplus.com/reference/set/set/)
- elements are sorted in order of element
```cpp
set<int> s;
s.insert(1);  // [1]
s.insert(4);  // [1, 4]
s.insert(2);  // [1, 2, 4]
// set<int> s{1, 2, 4};

// Outputs 1, 2, and 4 on separate lines
for (int element : s) {
	cout << element << endl;
}
```

### `map<T, U>` [docs](https://cplusplus.com/reference/map/map/)
- stores mapped values (U) associated with key values (T)
```cpp
map<int, int> m;
m[1] = 5;
m[2] = 5;
m[3] = 5;
// map<int, int> m{{1, 5}, {2, 5}, {3, 5}};

for (auto& x : m) {
	x.second = 3;
}
// 1 3
// 2 3
// 3 3
for (pair<int,int> x : m) {
	cout << x.first << " " << x.second << endl;
}
```