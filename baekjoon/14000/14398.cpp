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
    int n;
    cin >> n;

    vector<int> a(n);
    for (auto& x : a) cin >> x;

    int mid = partition(a.begin(), a.end(), [&](auto& x) { return x & 1; }) - a.begin();

    bipartite_matching solver(mid, n - mid);

    for (int i = 0; i < mid; ++i)
        for (int j = mid; j < n; ++j) {
            if (gcd(a[i], a[j]) != 1) continue;
            int64_t p = int64_t(a[i]) * a[i] + int64_t(a[j]) * a[j];
            if (int64_t c = sqrt(p); c * c == p)
                solver.add_edge(i, j - mid);
        }
    cout << solver.maximum_matching();
}