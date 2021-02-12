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

void solve() {
    int c, d, v;
    cin >> c >> d >> v;

    vector<pair<int, int>> cat_lover, dog_lover;
    for (int i = 0, x, y; i < v; ++i) {
        char op;
        cin >> op >> x >> op >> y, --x, --y;
        (op == 'D' ? cat_lover : dog_lover).emplace_back(x, y);
    }

    bipartite_matching solver(cat_lover.size(), dog_lover.size());
    for (int i = 0; i < int(cat_lover.size()); ++i)
        for (int j = 0; j < int(dog_lover.size()); ++j)
            if (cat_lover[i].first == dog_lover[j].second || cat_lover[i].second == dog_lover[j].first)
                solver.add_edge(i, j);

    cout << v - solver.maximum_matching() << '\n';
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