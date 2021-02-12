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

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;

    vector<int> a(n);
    int com = 0, soft = 0;
    for (int x; n--;) {
        char d;
        cin >> x >> d, --x;
        a[x] = d == 'c' ? com++ : ~(soft++);
    }

    bipartite_matching solver(com, soft);
    for (int u, v; m--;) {
        cin >> u >> v;
        u = a[u - 1], v = a[v - 1];
        if (u < v) swap(u, v);
        solver.add_edge(u, ~v);
    }
    cout << com + soft - solver.maximum_matching();
}