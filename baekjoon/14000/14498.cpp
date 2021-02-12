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
    int n, m, k;
    cin >> n >> m >> k;

    vector<pair<int, int>> ppock, kkock;
    // c = 0 -> 뽁뽁이
    for (int x, y, c; k--;) {
        cin >> x >> y >> c, --x, --y;
        (c ? kkock : ppock).emplace_back(x, y);
    }

    bipartite_matching solver(ppock.size(), kkock.size());
    for (int i = 0; i < int(ppock.size()); ++i)
        for (int j = 0; j < int(kkock.size()); ++j)
            if (ppock[i].first == kkock[j].first || ppock[i].second == kkock[j].second)
                solver.add_edge(i, j);
    cout << solver.maximum_matching() << '\n';
}