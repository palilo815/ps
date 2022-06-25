#include <bits/stdc++.h>

constexpr std::array<std::pair<int, int>, 4> MOVE {{{-1, 0}, {0, -1}, {0, 1}, {1, 0}}};

auto main() -> int {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m, k;
    cin >> n >> m >> k;
    vector grid(n, vector<int>(m));
    queue<pair<int, int>> q;
    pair<int, int> src {};
    for (int i {}; i < n; ++i) {
        for (int j {}; j < n; ++j) {
            cin >> grid[i][j];
            if (grid[i][j] == 3) {
                q.emplace(i, j);
                grid[i][j] = 1;
            } else if (grid[i][j] == 4) {
                src = {i, j};
            }
        }
    }
    while (k--) {
        for (auto sz {q.size()}; sz--;) {
            const auto [x, y] {q.front()};
            q.pop();
            for (const auto& [dx, dy] : MOVE) {
                const auto xx {x + dx};
                const auto yy {y + dy};
                if (xx != -1 && xx != n && yy != -1 && yy != m && grid[xx][yy] != 1) {
                    grid[xx][yy] = 1;
                    q.emplace(xx, yy);
                }
            }
        }
    }
    q = decltype(q) {{src}};
    grid[src.first][src.second] = 1;
    for (int ans {}; !q.empty(); ++ans) {
        for (auto sz {q.size()}; sz--;) {
            const auto [x, y] {q.front()};
            q.pop();
            if (grid[x][y] == 3) return cout << ans, 0;
            for (const auto& [dx, dy] : MOVE) {
                const auto xx {x + dx};
                const auto yy {y + dy};
                if (xx != -1 && xx != n && yy != -1 && yy != m && grid[xx][yy] != 1) {
                    grid[xx][yy] |= 1;
                    q.emplace(xx, yy);
                }
            }
        }
    }
    cout << -1;
}
