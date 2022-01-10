#include <bits/stdc++.h>

int main() {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    constexpr size_t MX_N = 50;
    char grid[MX_N][MX_N];
    int dp[MX_N + 1][MX_N + 1][2][5];
    int t;
    cin >> t;
    while (t--) {
        int n, k;
        cin >> n >> k;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                cin >> grid[i][j];
            }
        }
        memset(dp, 0, sizeof(dp));
        if (grid[0][0] == '.') {
            if (grid[0][1] == '.') dp[1][2][0][0] = 1;
            if (grid[1][0] == '.') dp[2][1][1][0] = 1;
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (i + j < 2 || grid[i][j] == 'H') continue;
                for (int dir = 0; dir != 2; ++dir) {
                    for (int c = 0; c <= k; ++c) {
                        dp[i + 1][j + 1][1][c + (dir == 0)] += dp[i][j + 1][dir][c];
                        dp[i + 1][j + 1][0][c + (dir == 1)] += dp[i + 1][j][dir][c];
                    }
                }
            }
        }
        int64_t ans = 0;
        for (int i = 0; i != 2; ++i) {
            for (int j = 0; j <= k; ++j) {
                ans += dp[n][n][i][j];
            }
        }
        cout << ans << '\n';
    }
}
