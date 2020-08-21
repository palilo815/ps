#include <bits/stdc++.h>
using namespace std;
using p = pair<int, int>;

const int mx = 1001;

vector<p> adj[mx];
int dep[mx], dist[mx], par[mx];

void dfs(int u, int p) {
    par[u] = p;
    dep[u] = dep[p] + 1;

    for (auto& [w, v] : adj[u])
        if (v ^ p) {
            dist[v] = w;
            dfs(v, u);
        }
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, Q; cin >> N >> Q;
    for (int i = 1, u, v, w; i < N; ++i) {
        cin >> u >> v >> w;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }

    dfs(1, 0);

    for (int u, v, ans; Q--;) {
        cin >> u >> v;
        ans = 0;
        while (u ^ v) {
            int& n = dep[u] > dep[v] ? u : v;
            ans += dist[n];
            n = par[n];
        }
        cout << ans << '\n';
    }
    return 0;
}