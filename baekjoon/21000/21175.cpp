#include <bits/stdc++.h>
using namespace std;

constexpr int MX_N = 100;

char adj[MX_N][MX_N];
int eid[MX_N][MX_N];
bool visited[MX_N][MX_N][MX_N];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int n, m, r, b, y;
    cin >> n >> m >> r >> b >> y, --r, --b, --y;

    vector<char> colour(m);
    for (int i = 0, u, v; i < m; ++i) {
        cin >> u >> v >> colour[i], --u, --v;
        adj[u][v] = adj[v][u] = colour[i];
        eid[u][v] = eid[v][u] = i;
    }

    vector<bool> coloured(m);
    auto dfs = [&](int sr, int sb, int sy) {
        vector<tuple<int, int, int>> stk;
        stk.emplace_back(sr, sb, sy);
        visited[sr][sb][sy] = true;

        while (!stk.empty()) {
            const auto [r, b, y] = stk.back();
            stk.pop_back();

            for (int v = 0; v < n; ++v) {
                if (adj[r][v] == 'X' || adj[r][v] == 'R') {
                    coloured[eid[r][v]] = true;
                    if (!visited[v][b][y]) {
                        visited[v][b][y] = true;
                        stk.emplace_back(v, b, y);
                    }
                }
                if (adj[b][v] == 'X' || adj[b][v] == 'B') {
                    coloured[eid[b][v]] = true;
                    if (!visited[r][v][y]) {
                        visited[r][v][y] = true;
                        stk.emplace_back(r, v, y);
                    }
                }
                if (adj[y][v] == 'X' || adj[y][v] == 'Y') {
                    coloured[eid[y][v]] = true;
                    if (!visited[r][b][v]) {
                        visited[r][b][v] = true;
                        stk.emplace_back(r, b, v);
                    }
                }
                if (adj[r][v] == 'P' && r == b) {
                    coloured[eid[r][v]] = true;
                    if (!visited[v][v][y]) {
                        visited[v][v][y] = true;
                        stk.emplace_back(v, v, y);
                    }
                }
                if (adj[b][v] == 'G' && b == y) {
                    coloured[eid[b][v]] = true;
                    if (!visited[r][v][v]) {
                        visited[r][v][v] = true;
                        stk.emplace_back(r, v, v);
                    }
                }
                if (adj[y][v] == 'O' && y == r) {
                    coloured[eid[y][v]] = true;
                    if (!visited[v][b][v]) {
                        visited[v][b][v] = true;
                        stk.emplace_back(v, b, v);
                    }
                }
            }
        }
    };

    dfs(r, b, y);

    for (int i = 0; i < m; ++i)
        if (colour[i] != 'X' && !coloured[i])
            return cout << 0, 0;
    cout << 1;
}