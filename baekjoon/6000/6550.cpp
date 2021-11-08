#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    for (string s, t; cin >> s >> t;) {
        auto it = s.begin();
        for (const auto& c : t) {
            if (c == *it) ++it;
            if (it == s.end()) break;
        }
        cout << (it == s.end() ? "Yes\n" : "No\n");
    }
}