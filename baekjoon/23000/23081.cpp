#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    constexpr array<pair<int, int>, 8> mov {{{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}}};
    int n;
    cin >> n;
    vector<string> grid(n);
    for (auto& x : grid) {
        cin >> x;
    }
    vector cnt(n, vector<int>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (grid[i][j] == 'B') {
                for (const auto& [di, dj] : mov) {
                    int i2 = i + di, j2 = j + dj;
                    while (~i2 && i2 != n && ~j2 && j2 != n && grid[i2][j2] == 'W') {
                        i2 += di, j2 += dj;
                    }
                    if (~i2 && i2 != n && ~j2 && j2 != n && grid[i2][j2] == '.') {
                        cnt[i2][j2] += max(abs(i2 - i) - 1, abs(j2 - j) - 1);
                    }
                }
            }
        }
    }
    int mx = 0, i2 = -1, j2 = -1;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (cnt[i][j] > mx) {
                mx = cnt[i][j], i2 = i, j2 = j;
            }
        }
    }
    if (!mx) return cout << "PASS", 0;
    cout << j2 << ' ' << i2 << '\n'
         << mx;
}