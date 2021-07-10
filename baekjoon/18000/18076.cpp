#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    auto sub = [&](char& x, char y) {
        x += 10 - y;
        if (x >= 10) x -= 10;
    };
    int n;
    cin >> n;
    vector a(n, vector<char>(n));
    for (auto& vt : a) {
        for (auto& x : vt) {
            cin >> x, x -= '0';
        }
    }
    vector ans(n, vector<bool>(n));
    for (int u = n - 1; u--;) {
        auto dp = a[u];
        for (int v = u + 1; v < n; ++v) {
            if (dp[v]) {
                ans[u][v] = true;
                for (int i = v + 1; i < n; ++i) {
                    sub(dp[i], a[v][i]);
                }
            }
        }
    }
    for (const auto& vt : ans) {
        for (const auto& x : vt) {
            cout << x;
        }
        cout << '\n';
    }
}