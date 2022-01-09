#include <bits/stdc++.h>

template <class T>
bool chmin(T& _old, T _new) { return _old > _new && (_old = _new, true); }
template <class T>
bool chmax(T& _old, T _new) { return _old < _new && (_old = _new, true); }

int main() {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;
    vector<string> grid(n);
    for (auto& x : grid) {
        cin >> x;
    }
    constexpr array<pair<int, int>, 4> MOVE {{{-1, 0}, {0, -1}, {0, 1}, {1, 0}}};
    vector seen(n, vector(m, INT_MAX));
    vector dist(n, vector<int>(m));
    queue<pair<int, int>> q;
    auto bfs = [&](int sx, int sy) {
        ranges::for_each(dist, [&](auto& x) {
            ranges::fill(x, -1);
        });
        q.emplace(sx, sy);
        dist[sx][sy] = 0;
        while (!q.empty()) {
            const auto [x, y] = q.front();
            q.pop();
            for (const auto& [dx, dy] : MOVE) {
                const auto xx = x + dx, yy = y + dy;
                if (xx == -1 || xx == n || yy == -1 || yy == m || grid[xx][yy] == 'I' || ~dist[xx][yy] || dist[x][y] + 1 >= seen[xx][yy]) continue;
                dist[xx][yy] = dist[x][y] + 1;
                q.emplace(xx, yy);
            }
        }
    };
    for (int i = 0; i != n; ++i) {
        for (int j = 0; j != m; ++j) {
            if (grid[i][j] == 'V') {
                bfs(i, j);
            }
        }
    }
    for (int i = 0; i != n; ++i) {
        for (int j = 0, dp = INT_MAX; j != m; ++j) {
            if (dist[i][j] == -1) {
                dp = INT_MAX;
            } else {
                chmin(dp, dist[i][j]);
            }
            chmin(seen[i][j], dp);
        }
    }
    for (int i = 0; i != n; ++i) {
        for (int j = m, dp = INT_MAX; j--;) {
            if (dist[i][j] == -1) {
                dp = INT_MAX;
            } else {
                chmin(dp, dist[i][j]);
            }
            chmin(seen[i][j], dp);
        }
    }
    for (int j = 0; j != m; ++j) {
        for (int i = 0, dp = INT_MAX; i != n; ++i) {
            if (dist[i][j] == -1) {
                dp = INT_MAX;
            } else {
                chmin(dp, dist[i][j]);
            }
            chmin(seen[i][j], dp);
        }
    }
    for (int j = 0; j != m; ++j) {
        for (int i = n, dp = INT_MAX; i--;) {
            if (dist[i][j] == -1) {
                dp = INT_MAX;
            } else {
                chmin(dp, dist[i][j]);
            }
            chmin(seen[i][j], dp);
        }
    }
    for (int i = 0; i != n; ++i) {
        for (int j = 0; j != m; ++j) {
            if (grid[i][j] == 'Y') {
                bfs(i, j);
            }
        }
    }
    for (int i = 0; i != n; ++i) {
        for (int j = 0; j != m; ++j) {
            if (grid[i][j] == 'T') {
                return cout << (~dist[i][j] ? "YES" : "NO"), 0;
            }
        }
    }
}
