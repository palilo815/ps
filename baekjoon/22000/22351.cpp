#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    string s;
    cin >> s;
    string t;
    for (int a = 1, b; a != 1000; ++a) {
        t.clear();
        for (b = a; t.size() < s.size(); ++b) {
            t += to_string(b);
        }
        if (s == t) {
            return cout << a << ' ' << b - 1, 0;
        }
    }
    assert(false);
}