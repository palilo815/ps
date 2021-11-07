#include <bits/stdc++.h>
using namespace std;

template <class T>
bool chmin(T& _old, T _new) { return _old > _new && (_old = _new, true); }
template <class T>
bool chmax(T& _old, T _new) { return _old < _new && (_old = _new, true); }

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    constexpr array<pair<int, int>, 8> mov {{{-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}}};
    int n;
    cin >> n;
    vector grid(n + 2, vector<char>(n + 2));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            cin >> grid[i][j];
        }
    }
    vector dp(n + 2, vector<array<int, 8>>(n + 2));
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            for (int k = 0; k < 4; ++k) {
                if (grid[i][j] == '1') {
                    const auto ii = i + mov[k].first, jj = j + mov[k].second;
                    dp[i][j][k] = dp[ii][jj][k] + 1;
                }
            }
        }
    }
    for (int i = n; i; --i) {
        for (int j = n; j; --j) {
            for (int k = 4; k < 8; ++k) {
                if (grid[i][j] == '1') {
                    const auto ii = i + mov[k].first, jj = j + mov[k].second;
                    dp[i][j][k] = dp[ii][jj][k] + 1;
                }
            }
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            chmax(ans, *max_element(dp[i][j].begin(), dp[i][j].end()));
        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int j = 1; j <= n; ++j) {
            if (grid[i][j] == '2') {
                for (int k = 0; k < 8; ++k) {
                    chmax(ans, 1 + dp[i + mov[k].first][j + mov[k].second][k] + dp[i + mov[7 ^ k].first][j + mov[7 ^ k].second][7 ^ k]);
                }
            }
        }
    }
    cout << ans;
}