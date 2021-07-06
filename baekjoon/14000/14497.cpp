#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    constexpr array<pair<int, int>, 4> mov = {{{-1, 0}, {0, -1}, {0, 1}, {1, 0}}};
    int n, m, sx, sy, tx, ty;
    cin >> n >> m >> sx >> sy >> tx >> ty;
    --sx, --sy, --tx, --ty;
    vector grid(n, vector<char>(m));
    for (auto& vt : grid) {
        for (auto& x : vt) {
            cin >> x;
        }
    }
    deque<int> dq;
    dq.emplace_back(sx << 16 | sy);
    dq.emplace_back(-1);
    int ans = 0;
    for (;;) {
        auto x = dq.front();
        dq.pop_front();
        if (x == -1) {
            dq.emplace_back(-1);
            ++ans;
            continue;
        }
        auto y = x & 0xffff;
        x >>= 16;
        if (x == tx && y == ty) {
            return cout << ans, 0;
        }
        for (const auto& [dx, dy] : mov) {
            int x2 = x + dx, y2 = y + dy;
            if (x2 == -1 || x2 == n || y2 == -1 || y2 == m || !grid[x2][y2]) {
                continue;
            }
            grid[x2][y2] == '0' ? dq.emplace_front(x2 << 16 | y2) : dq.emplace_back(x2 << 16 | y2);
            grid[x2][y2] = 0;
        }
    }
}