#include <bits/stdc++.h>
using namespace std;

template <class T>
bool chmin(T& _old, T _new) { return _old > _new && (_old = _new, true); }
template <class T>
bool chmax(T& _old, T _new) { return _old < _new && (_old = _new, true); }

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    constexpr int INF = 0x3f3f3f3f;
    int n, k;
    cin >> n >> k;
    vector c(n, vector<int>(n));
    for (auto& vt : c) {
        for (auto& x : vt) {
            cin >> x;
        }
    }
    vector<int> dp(1 << n, INF);
    dp.back() = 0;
    for (int cnt = n; cnt > k; --cnt) {
        for (int f = 1 << n, x = (1 << cnt) - 1; x < f;) {
            for (int i = 0; i < n; ++i) {
                if (x >> i & 1) {
                    for (int j = 0; j < n; ++j) {
                        if (i != j && (x >> j & 1)) {
                            chmin(dp[x ^ (1 << i)], dp[x] + c[i][j]);
                        }
                    }
                }
            }
            auto t = x | (x - 1);
            x = (t + 1) | (((~t & -~t) - 1) >> (__builtin_ctz(x) + 1));
        }
    }
    int ans = INF;
    for (int f = 1 << n, x = (1 << k) - 1; x < f;) {
        chmin(ans, dp[x]);
        auto t = x | (x - 1);
        x = (t + 1) | (((~t & -~t) - 1) >> (__builtin_ctz(x) + 1));
    }
    cout << ans;
}