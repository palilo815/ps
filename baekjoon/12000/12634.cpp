#include <bits/stdc++.h>
using namespace std;

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

int solve() {
    int n, k;
    cin >> n >> k;

    vector<vector<int>> chart(n, vector<int>(k));
    for (auto& vt : chart)
        for (auto& x : vt)
            cin >> x;

    bipartite_matching solver(n, n);
    for (int u = 0; u < n; ++u)
        for (int v = 0; v < n; ++v) {
            bool flag = true;
            for (int i = 0; i < k; ++i)
                if (chart[u][i] <= chart[v][i]) {
                    flag = false;
                    break;
                }
            if (flag) solver.add_edge(u, v);
        }
    return n - solver.maximum_matching();
}
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int T;
    cin >> T;
    for (int t = 1; t <= T; ++t)
        cout << "Case #" << t << ": " << solve() << '\n';
}