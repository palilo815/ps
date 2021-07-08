#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    constexpr array<pair<int, int>, 8> mov = {{{-2, -1}, {-2, 1}, {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {2, -1}, {2, 1}}};
    constexpr int mod = 1e9 + 9;
    int n, m;
    cin >> n >> m;
    vector dp(n, vector(m, pair(-1, -1)));
    dp[0][0] = {0, 1};
    queue<int> q;
    q.emplace(0);
    while (!q.empty()) {
        const auto x = q.front() >> 16, y = q.front() & 0xffff;
        q.pop();
        for (const auto& [dx, dy] : mov) {
            int x2 = x + dx, y2 = y + dy;
            if (x2 < 0 || x2 >= n || y2 < 0 || y2 >= m) {
                continue;
            } else if (dp[x2][y2].first == -1) {
                dp[x2][y2] = {dp[x][y].first + 1, dp[x][y].second};
                q.emplace(x2 << 16 | y2);
            } else if (dp[x2][y2].first == dp[x][y].first + 1) {
                dp[x2][y2].second += dp[x][y].second;
                dp[x2][y2].second %= mod;
            }
        }
    }
    if (dp[n - 1][m - 1].first == -1) {
        cout << "None";
    } else {
        cout << dp[n - 1][m - 1].first << ' ' << dp[n - 1][m - 1].second;
    }
}