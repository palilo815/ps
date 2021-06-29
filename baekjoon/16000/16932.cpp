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

    constexpr array<pair<int, int>, 4> mov = {{{-1, 0}, {0, -1}, {0, 1}, {1, 0}}};

    int n, m;
    cin >> n >> m;

    vector grid(n, vector<char>(m));
    for (auto& vt : grid)
        for (auto& x : vt)
            cin >> x;

    vector id(n, vector<int>(m, -1));
    vector<int> sz;
    sz.reserve((n * m + 1) / 2);

    vector<pair<int, int>> stk;
    auto dfs = [&](int sx, int sy) {
        const int i = sz.size();
        sz.emplace_back();
        stk.emplace_back(sx, sy);

        while (!stk.empty()) {
            const auto [x, y] = stk.back();
            stk.pop_back();

            id[x][y] = i, ++sz[i];
            for (const auto& [dx, dy] : mov) {
                const auto nx = x + dx, ny = y + dy;
                if (~nx && nx != n && ~ny && ny != m && grid[nx][ny] == '1' && id[nx][ny] == -1) {
                    id[nx][ny] = i;
                    stk.emplace_back(nx, ny);
                }
            }
        }
    };

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (grid[i][j] == '1' && id[i][j] == -1)
                dfs(i, j);

    int ans = 0;

    array<int, 4> neighbor;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (grid[i][j] == '0') {
                neighbor.fill(-1);
                for (int t = 0; t < 4; ++t) {
                    const auto ni = i + mov[t].first, nj = j + mov[t].second;
                    if (~ni && ni != n && ~nj && nj != m && ~id[ni][nj])
                        neighbor[t] = id[ni][nj];
                }

                int sum = 1;
                for (auto it = neighbor.begin(); it != neighbor.end(); ++it)
                    if (~*it && find(neighbor.begin(), it, *it) == it)
                        sum += sz[*it];
                chmax(ans, sum);
            }
    cout << ans;
}