#include <bits/stdc++.h>
using namespace std;

const int mxN = 50;

char mat[mxN][mxN];

struct bipartite_matching {
    vector<vector<int>> adj;
    vector<int> match, rev;
    vector<bool> visited;
    int n, m;

    bipartite_matching(int n, int m) : n(n), m(m) {
        adj.resize(n), match.resize(n, -1), rev.resize(m, -1), visited.resize(n);
    }
    void add_edge(int u, int v) { adj[u].emplace_back(v); }
    bool dfs(int u) {
        visited[u] = true;
        for (const auto& v : adj[u]) {
            if (rev[v] == -1 || (!visited[rev[v]] && dfs(rev[v]))) {
                match[u] = v, rev[v] = u;
                return true;
            }
        }
        return false;
    }
    int maximum_matching() {
        for (bool update = true; update;) {
            fill(visited.begin(), visited.end(), false);
            update = false;

            for (int i = 0; i < n; ++i)
                if (match[i] == -1 && dfs(i))
                    update = true;
        }
        return n - count(match.begin(), match.end(), -1);
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> mat[i][j];

    auto index = [&](int r, int c) {
        return m & 1 ? r / 2 * m + ((r & 1) * m + c) / 2 : r * m / 2 + c / 2;
    };

    bipartite_matching solver((n * m + 1) >> 1, n * m >> 1);

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j) {
            if ((i + j) & 1 || mat[i][j] == 'X') continue;
            int cur = index(i, j);
            if (i && mat[i - 1][j] == '.') solver.add_edge(cur, index(i - 1, j));
            if (j && mat[i][j - 1] == '.') solver.add_edge(cur, index(i, j - 1));
            if (j != m - 1 && mat[i][j + 1] == '.') solver.add_edge(cur, index(i, j + 1));
            if (i != n - 1 && mat[i + 1][j] == '.') solver.add_edge(cur, index(i + 1, j));
        }
    cout << count(mat[0], mat[n], '.') - solver.maximum_matching();
}