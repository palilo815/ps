#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    constexpr array<pair<int, int>, 4> mov {{{-1, 0}, {0, -1}, {0, 1}, {1, 0}}};
    int n, m, k;
    cin >> n >> m >> k;
    vector wall(n, vector<char>(m));
    for (int x, y; k--;) {
        cin >> x >> y, --x, --y;
        wall[x][y] = 1;
    }
    vector dp(n, vector<int>(m));
    for (int i = 0; i < n; ++i) {
        dp[i].back() = !wall[i].back();
    }
    for (int i = 0; i < m; ++i) {
        dp.back()[i] = !wall.back()[i];
    }
    for (int i = n - 1; i--;) {
        for (int j = m - 1; j--;) {
            if (wall[i][j]) continue;
            dp[i][j] = min({dp[i][j + 1], dp[i + 1][j], dp[i + 1][j + 1]}) + 1;
        }
    }
    int sx = 0, sy = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (dp[i][j] > dp[sx][sy]) {
                sx = i, sy = j;
            }
        }
    }
    vector visited(n, vector<char>(m));
    vector pref(n + 1, vector<int>(m + 1));
    auto parametric = [&](auto lo, auto hi) {
        auto f = [&](auto mid) -> bool {
            for (auto& x : visited) {
                fill(x.begin(), x.end(), 0);
            }
            visited[sx][sy] = true;
            queue<pair<int, int>> q;
            q.emplace(sx, sy);
            while (!q.empty()) {
                const auto [x, y] = q.front();
                q.pop();
                for (const auto& [dx, dy] : mov) {
                    const auto x2 = x + dx, y2 = y + dy;
                    if (x2 == -1 || x2 == n || y2 == -1 || y2 == m || dp[x2][y2] < mid || visited[x2][y2]) {
                        continue;
                    }
                    visited[x2][y2] = true;
                    q.emplace(x2, y2);
                }
            }
            for (auto& x : pref) {
                fill(x.begin(), x.end(), 0);
            }
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= m; ++j) {
                    if (visited[i - 1][j - 1]) {
                        pref[i][j] += 1;
                        if (j + mid <= m) pref[i][j + mid] -= 1;
                        if (i + mid <= n) pref[i + mid][j] -= 1;
                        if (i + mid <= n && j + mid <= m) pref[i + mid][j + mid] += 1;
                    }
                }
            }
            for (int i = 1; i <= n; ++i) {
                for (int j = 1; j <= m; ++j) {
                    pref[i][j] += -pref[i - 1][j - 1] + pref[i - 1][j] + pref[i][j - 1];
                }
            }
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    if (!wall[i][j] && !pref[i + 1][j + 1]) {
                        return false;
                    }
                }
            }
            return true;
        };
        // last true
        while (lo != hi) {
            auto mid = hi - (hi - lo) / 2;
            f(mid) ? lo = mid : hi = mid - 1;
        }
        return lo;
    };
    const auto ans = parametric(0, dp[sx][sy]);
    cout << (ans ? ans : -1);
}
