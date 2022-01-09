#include <bits/stdc++.h>

int main() {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    constexpr int MAX = 200;
    array<array<bool, MAX>, MAX> grid;
    array<array<int, MAX>, MAX> colour;
    constexpr array<pair<int, int>, 4> MOVE {{{-1, 0}, {0, -1}, {0, 1}, {1, 0}}};
    vector<pair<int, int>> stk;
    for (int t = 1, n, m;; ++t) {
        cin >> n >> m;
        if (n == 0 || m == 0) break;
        m <<= 2;
        for (int i = 0; i != n; ++i) {
            for (int j = 0; j != m; j += 4) {
                char hex_digit;
                cin >> hex_digit;
                const auto bin = hex_digit < 'a' ? hex_digit - '0' : hex_digit - 'a' + 10;
                grid[i][j + 0] = bin >> 3 & 1;
                grid[i][j + 1] = bin >> 2 & 1;
                grid[i][j + 2] = bin >> 1 & 1;
                grid[i][j + 3] = bin >> 0 & 1;
            }
        }
        auto flood_fill = [&](int sx, int sy, int c) {
            const auto ori = grid[sx][sy];
            stk.emplace_back(sx, sy);
            while (!stk.empty()) {
                const auto [x, y] = stk.back();
                stk.pop_back();
                for (const auto& [dx, dy] : MOVE) {
                    const auto xx = x + dx, yy = y + dy;
                    if (xx == -1 || xx == n || yy == -1 || yy == m || grid[xx][yy] != ori || ~colour[xx][yy]) continue;
                    colour[xx][yy] = c;
                    stk.emplace_back(xx, yy);
                }
            }
        };
        for_each_n(colour.begin(), n, [&](auto& x) {
            fill_n(x.begin(), m, -1);
        });
        for (int i = 0; i != n; ++i) {
            if (!grid[i][0] && colour[i][0] == -1) flood_fill(i, 0, -2);
            if (!grid[i][m - 1] && colour[i][m - 1] == -1) flood_fill(i, m - 1, -2);
        }
        for (int j = 0; j != m; ++j) {
            if (!grid[0][j] && colour[0][j] == -1) flood_fill(0, j, -2);
            if (!grid[n - 1][j] && colour[n - 1][j] == -1) flood_fill(n - 1, j, -2);
        }
        int num_char = 0;
        for (int i = 0; i != n; ++i) {
            for (int j = 0; j != m; ++j) {
                if (grid[i][j] && colour[i][j] == -1) {
                    flood_fill(i, j, num_char++);
                }
            }
        }
        vector<int> num_hole(num_char);
        for (int i = 1; i + 1 < n; ++i) {
            for (int j = 1; j + 1 < m; ++j) {
                if (!grid[i][j] && colour[i][j] == -1) {
                    const auto id = accumulate(MOVE.begin(), MOVE.end(), -1, [&](const auto& acc, const auto& d) {
                        return acc & colour[i + d.first][j + d.second];
                    });
                    if (~id) {
                        ++num_hole[id];
                        flood_fill(i, j, -2);
                    }
                }
            }
        }
        string ans(num_char, 0);
        ranges::transform(num_hole, ans.begin(), [&](const auto& x) {
            switch (x) {
            case 1: return 'A';
            case 3: return 'J';
            case 5: return 'D';
            case 4: return 'S';
            case 0: return 'W';
            case 2: return 'K';
            default: return '?';
            }
        });
        assert(ans.find('?') == string::npos);
        ranges::sort(ans);
        cout << "Case " << t << ": " << ans << '\n';
    }
}
