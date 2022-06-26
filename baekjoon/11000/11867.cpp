#include <bits/stdc++.h>

auto main() -> int {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    array<array<int, 101>, 101> dp {};
    int n, m;
    cin >> n >> m;
    const auto mx {max(n, m)};
    for (auto t {3}; t <= n + m; ++t) {
        for (auto i {1}; i < t; ++i) {
            const auto j {t - i};
            if (i > mx || j > mx) continue;
            if (i != 1) {
                for (auto k {1}; k < i; ++k) {
                    dp[i][j] |= !dp[k][i - k];
                }
            }
            if (j != 1) {
                for (auto k {1}; k < j; ++k) {
                    dp[i][j] |= !dp[k][j - k];
                }
            }
        }
    }
    cout << (dp[n][m] ? 'A' : 'B');
}
