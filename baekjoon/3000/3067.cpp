#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) {
        cin >> x;
    }
    int m;
    cin >> m;
    vector<int> dp(m + 1);
    dp[0] = 1;
    for (const auto& coin : a) {
        for (int i = 0; i + coin <= m; ++i) {
            dp[i + coin] += dp[i];
        }
    }
    cout << dp[m] << '\n';
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int T;
    cin >> T;
    while (T--) solve();
}