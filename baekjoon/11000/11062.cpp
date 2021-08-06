#include <bits/stdc++.h>
using namespace std;

template <class T>
bool chmin(T& _old, T _new) { return _old > _new && (_old = _new, true); }
template <class T>
bool chmax(T& _old, T _new) { return _old < _new && (_old = _new, true); }

constexpr int MX_N = 1e3;

int pref[MX_N + 1];
int dp[MX_N][MX_N + 1];

void solve() {
    int n;
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        cin >> pref[i];
    }
    for (int i = 0; i < n; ++i) {
        dp[i][i + 1] = pref[i + 1];
    }
    for (int i = 1; i < n; ++i) {
        pref[i + 1] += pref[i];
    }
    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i + len <= n; ++i) {
            dp[i][i + len] = pref[i + len] - pref[i] - min(dp[i][i + len - 1], dp[i + 1][i + len]);
        }
    }
    cout << dp[0][n] << '\n';
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