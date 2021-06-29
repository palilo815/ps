#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    constexpr array<pair<int, int>, 4> mov = {{{-1, 0}, {0, -1}, {0, 1}, {1, 0}}};

    int n, m;
    cin >> n >> m;

    n = n * 2 + 2;
    m = m * 2 + 2;

    vector wall(n, vector<bool>(m));
    for (int i = 1; i < n - 1; i += 2) {
        string s;
        cin >> s;
        for (int j = 1; j < m - 1; j += 2) {
            if (s[j / 2] == '/')
                wall[i][j + 1] = wall[i + 1][j] = true;
            else if (s[j / 2] == '\\')
                wall[i][j] = wall[i + 1][j + 1] = true;
        }
    }

    vector visited(n, vector<bool>(m));
    vector<pair<int, int>> stk;
    auto dfs = [&](int sx, int sy) {
        visited[sx][sy] = true;
        stk.emplace_back(sx, sy);

        while (!stk.empty()) {
            const auto [x, y] = stk.back();
            stk.pop_back();

            for (const auto& [dx, dy] : mov) {
                auto X = x + dx, Y = y + dy;
                if (~X && X != n && ~Y && Y != m && !wall[X][Y] && !visited[X][Y]) {
                    visited[X][Y] = true;
                    stk.emplace_back(X, Y);
                }
            }
        }
    };

    int ans = -1;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (!wall[i][j] && !visited[i][j]) {
                dfs(i, j);
                ++ans;
            }

    if (ans == -1) ans = 0;
    cout << ans;
}