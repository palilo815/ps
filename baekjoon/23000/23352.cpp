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
    constexpr array<pair<int, int>, 4> mov {{{-1, 0}, {0, -1}, {0, 1}, {1, 0}}};
    int n, m;
    cin >> n >> m;
    vector grid(n, vector<char>(m));
    for (auto& row : grid) {
        for (auto& x : row) {
            cin >> x;
        }
    }
    queue<pair<int, int>> q;
    vector dist(n, vector<int>(m));
    const auto bfs = [&](const pair<int, int> s) {
        for_each(dist.begin(), dist.end(), [&](auto& x) {
            fill(x.begin(), x.end(), -1);
        });
        dist[s.first][s.second] = 0;
        q.emplace(s);
        while (!q.empty()) {
            const auto [x, y] = q.front();
            q.pop();
            for (const auto& [dx, dy] : mov) {
                const auto xx = x + dx, yy = y + dy;
                if (~xx && xx != n && ~yy && yy != m && grid[xx][yy] != '0' && dist[xx][yy] == -1) {
                    dist[xx][yy] = dist[x][y] + 1;
                    q.emplace(xx, yy);
                }
            }
        }
        pair ret(0, 0);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                chmax(ret, pair(dist[i][j], grid[s.first][s.second] - '0' + grid[i][j] - '0'));
            }
        }
        return ret;
    };
    pair ans(0, 0);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] != '0') {
                chmax(ans, bfs(pair(i, j)));
            }
        }
    }
    cout << ans.second;
}