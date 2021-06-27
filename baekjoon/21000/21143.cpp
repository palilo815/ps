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

    array<bool, 26> used {};
    for (const auto& x : s) {
        if (used[x - 'a']) return cout << 0, 0;
        used[x - 'a'] = true;
    }
    cout << 1;
}