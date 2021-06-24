#include <bits/stdc++.h>
using namespace std;

constexpr int MX_N = 500;
constexpr int MX_V = MX_N * MX_N / 3 * 2;

char grid[MX_N][MX_N + 1];
int id[MX_N][MX_N];

vector<int> adj[MX_V];
int match[MX_V], rev[MX_V];
bool visited[MX_V];

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

void solve() {
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; ++i)
        cin >> grid[i];

    int b = 0, w = 0;
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (grid[i][j] == 'B')
                id[i][j] = b++;
            else if (grid[i][j] == 'W')
                id[i][j] = w++;

    if (b * 2 != w) {
        cout << "NO\n";
        return;
    }

    const int v = w; // # of vertices

    for (int i = 0; i < v; ++i)
        adj[i].clear();

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < m; ++j)
            if (grid[i][j] == 'B') {
                if (i && grid[i - 1][j] == 'W') adj[id[i][j]].emplace_back(id[i - 1][j]);
                if (i != n - 1 && grid[i + 1][j] == 'W') adj[id[i][j]].emplace_back(id[i + 1][j]);
                if (j && grid[i][j - 1] == 'W') adj[id[i][j] + b].emplace_back(id[i][j - 1]);
                if (j != m - 1 && grid[i][j + 1] == 'W') adj[id[i][j] + b].emplace_back(id[i][j + 1]);
            }

    memset(match, -1, v * 4);
    memset(rev, -1, v * 4);

    for (bool update = true; update;) {
        memset(visited, 0, v);
        update = false;

        for (int i = 0; i < v; ++i)
            if (match[i] == -1 && dfs(i))
                update = true;
    }
    cout << (find(match, match + v, -1) == match + v ? "YES\n" : "NO\n");
}

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int T;
    cin >> T;
    while (T--) solve();
}