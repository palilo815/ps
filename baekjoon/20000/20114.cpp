#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, x, y;
    cin >> n >> x >> y;
    string ans(n, '?');
    for (string s; x--;) {
        cin >> s;
        for (int i = 0; i < n; ++i) {
            if (ans[i] != '?') continue;
            const auto key = find_if_not(s.begin() + y * i, s.begin() + y * (i + 1), [&](const auto& x) {
                return x == '?';
            });
            if (key != s.begin() + y * (i + 1)) {
                ans[i] = *key;
            }
        }
    }
    cout << ans;
}