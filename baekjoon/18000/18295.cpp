#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;
    array<bool, int(1e6)> check {};
    for (string s; n--;) {
        cin >> s;
        if (s[0] == '-' || s.size() > 6) continue;
        check[stoi(s)] = true;
    }
    cout << find(check.begin(), check.end(), false) - check.begin();
}