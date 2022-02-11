#include <bits/stdc++.h>

int main() {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    constexpr size_t MAX_N = 300;
    array<array<int16_t, MAX_N>, MAX_N> grid, next_grid;
    array<array<int8_t, MAX_N>, MAX_N> visited;
    int n, m;
    cin >> n >> m;
    for (auto& row : grid | ranges::views::take(n)) {
        for (auto& cell : row | ranges::views::take(m)) {
            cin >> cell;
        }
    }
    constexpr array<pair<int, int>, 4> MOVE {{{-1, 0}, {0, -1}, {0, 1}, {1, 0}}};
    vector<pair<int, int>> stk;
    auto sink = [&]() {
        memcpy(next_grid.data(), grid.data(), sizeof grid);
        bool found = false;
        for (const auto x : views::iota(1, n - 1)) {
            for (const auto y : views::iota(1, m - 1)) {
                if (grid[x][y] > 0) {
                    found = true;
                    for (const auto& [dx, dy] : MOVE) {
                        next_grid[x][y] -= grid[x + dx][y + dy] <= 0;
                    }
                }
            }
        }
        grid.swap(next_grid);
        return found;
    };
    auto divided = [&]() {
        auto dfs = [&](int sx, int sy) {
            visited[sx][sy] = 1;
            stk.emplace_back(sx, sy);
            while (!stk.empty()) {
                const auto [x, y] = stk.back();
                stk.pop_back();
                for (const auto& [dx, dy] : MOVE) {
                    const auto xx = x + dx, yy = y + dy;
                    if (grid[xx][yy] > 0 && !visited[xx][yy]) {
                        visited[xx][yy] = 1;
                        stk.emplace_back(xx, yy);
                    }
                }
            }
        };
        bool found = false;
        memset(visited.data(), 0, sizeof visited);
        for (const auto x : views::iota(1, n - 1)) {
            for (const auto y : views::iota(1, m - 1)) {
                if (grid[x][y] > 0 && !visited[x][y]) {
                    if (found) return true;
                    found = true;
                    dfs(x, y);
                }
            }
        }
        return false;
    };
    for (int ans = 1;; ++ans) {
        if (!sink()) return cout << 0, 0;
        if (divided()) return cout << ans, 0;
    }
}
