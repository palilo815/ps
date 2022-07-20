#include <bits/stdc++.h>

template <typename T>
auto chmin(T& _old, T _new) { return _old > _new && (_old = _new, true); }
template <typename T>
auto chmax(T& _old, T _new) { return _old < _new && (_old = _new, true); }

auto main() -> int {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m;
    cin >> n >> m;
    constexpr int INF = 0x3f3f3f3f;
    vector dp(m + 1, INF);
    dp[0] = 0;
    for (int i = 0, x; i < n; ++i) {
        cin >> x;
        for (int j = m; ~j; --j) {
            dp[j] = INF;
            for (int w = 1; w * w <= j; ++w) {
                chmin(dp[j], dp[j - w * w] + (w - x) * (w - x));
            }
        }
    }
    cout << (dp[m] == INF ? -1 : dp[m]) << '\n';
}
