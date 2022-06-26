#include <bits/stdc++.h>

constexpr std::array<std::pair<int, int>, 4> MOVE {{{-1, 0}, {1, 0}, {0, -1}, {0, 1}}};

auto main() -> int {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    int n, m, k;
    cin >> n >> m >> k;
    vector grid(n, vector<int>(m));
    for (int x, y; k--;) {
        cin >> x >> y;
        grid[x][y] = 1;
    }
    int x, y;
    cin >> x >> y;
    array<int, 4> dir;
    for (auto& x : dir) {
        cin >> x, --x;
    }
    auto go = [&]() {
        for (const auto& d : dir) {
            for (int xx, yy;; x = xx, y = yy) {
                grid[x][y] = 1;
                xx = x + MOVE[d].first, yy = y + MOVE[d].second;
                if (xx == -1 || xx == n || yy == -1 || yy == m || grid[xx][yy]) break;
            }
        }
    };
    for (;;) {
        const auto x0 {x}, y0 {y};
        go();
        if (x == x0 && y == y0) break;
    }
    cout << x << ' ' << y;
}
