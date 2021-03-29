#include <bits/stdc++.h>
using namespace std;

constexpr array<pair<int, int>, 4> mov = {{{-1, 0}, {0, -1}, {0, 1}, {1, 0}}};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;

    vector<vector<char>> mat(n, vector<char>(m));
    for (auto& row : mat)
        for (auto& x : row)
            cin >> x;

    array<pair<int, int>, 3> src;
    for (auto& [x, y] : src) cin >> x >> y, --x, --y;

    vector<vector<array<int, 3>>> dist(n, vector<array<int, 3>>(m, {-1, -1, -1}));
    auto bfs = [&](int id) {
        queue<int> q;
        q.emplace(src[id].first << 8 | src[id].second);

        dist[src[id].first][src[id].second][id] = 0;

        while (!q.empty()) {
            auto r = q.front(), c = r & 0xff;
            r >>= 8;
            q.pop();

            for (const auto& [dr, dc] : mov) {
                const auto R = r + dr, C = c + dc;
                if (~R && R != n && ~C && C != m && mat[R][C] == '0' && dist[R][C][id] == -1) {
                    dist[R][C][id] = dist[r][c][id] + 1;
                    q.emplace(R << 8 | C);
                }
            }
        }
    };

    bfs(0), bfs(1), bfs(2);

    int mn = INT_MAX, cnt = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            if (dist[i][j][0] == -1 || dist[i][j][1] == -1 || dist[i][j][2] == -1) continue;
            if (auto t = max({dist[i][j][0], dist[i][j][1], dist[i][j][2]}); t < mn)
                mn = t, cnt = 1;
            else if (t == mn)
                ++cnt;
        }

    if (mn == INT_MAX) cout << -1;
    else
        cout << mn << '\n'
             << cnt;
}