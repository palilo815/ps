#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;
    vector a(n, vector<int>(m));
    vector b(n, vector<int>(m));
    for (auto& row : a) {
        for (auto& x : row) {
            cin >> x;
        }
    }
    for (auto& row : b) {
        for (auto& x : row) {
            cin >> x;
        }
    }
    auto flood_fill = [&](pair<int, int> s) {
        constexpr array<pair<int, int>, 4> mov = {{{-1, 0}, {0, -1}, {0, 1}, {1, 0}}};
        const int new_colour = b[s.first][s.second];
        const int prv_colour = exchange(a[s.first][s.second], new_colour);
        vector<pair<int, int>> stk = {s};
        while (!stk.empty()) {
            const auto [x, y] = stk.back();
            stk.pop_back();
            for (const auto& [dx, dy] : mov) {
                const auto x2 = x + dx, y2 = y + dy;
                if (~x2 && x2 != n && ~y2 && y2 != m && a[x2][y2] == prv_colour) {
                    a[x2][y2] = new_colour;
                    stk.emplace_back(x2, y2);
                }
            }
        }
    };
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (a[i][j] != b[i][j]) {
                flood_fill(pair(i, j));
                return cout << (a == b ? "YES" : "NO"), 0;
            }
        }
    }
    cout << "YES";
}