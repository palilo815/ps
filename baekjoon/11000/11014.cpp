#include <bits/stdc++.h>
using namespace std;

const int mxN = 80;

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

void solve() {
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            cin >> mat[i][j];

    int even = n * (m + 1 >> 1);
    bipartite_matching solver(even, n * m - even);

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; j += 2) {
            if (mat[i][j] == 'x') continue;
            int cur = (j >> 1) * n + i;
            for (int k = -1; k <= 1; ++k) {
                if (i + k == -1 || i + k == n) continue;
                if (j && mat[i + k][j - 1] == '.') solver.add_edge(cur, cur - n + k);
                if (j != m - 1 && mat[i + k][j + 1] == '.') solver.add_edge(cur, cur + k);
            }
        }

    int seat = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (mat[i][j] == '.')
                ++seat;

    cout << seat - solver.maximum_matching() << '\n';
}
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int T;
    cin >> T;
    while (T--) solve();
}