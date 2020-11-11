#include <bits/stdc++.h>
using namespace std;
using ll = long long;

const int mxN = 1e4;

int N;
vector<pair<int, int>> adj[mxN];
int sz[mxN], par[mxN];

void dfs(int u) {
    sz[u] = 1;
    for (auto& [_, v] : adj[u]) {
        if (v == par[u]) continue;
        par[v] = u;
        dfs(v);
        sz[u] += sz[v];
    }
}
ll total(int u) {
    ll ret = 0;
    for (auto& [w, v] : adj[u]) {
        if (v == par[u]) continue;
        ret += sz[v] * w + total(v);
    }
    return ret;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    for (;;) {
        cin >> N;
        if (!N) break;

        for (int i = 0; i < N; ++i)
            adj[i].clear();

        for (int i = 1, u, v, w; i < N; ++i) {
            cin >> u >> v >> w;
            adj[u].emplace_back(w, v);
            adj[v].emplace_back(w, u);
        }

        dfs(0);

        ll ans = total(0);

        for (int u = 0, heavy;; u = heavy) {
            heavy = -1;
            for (auto& [w, v] : adj[u]) {
                if (v == par[u]) continue;
                if (sz[v] > N / 2) {
                    heavy = v;
                    ans -= w * (sz[v] * 2 - N);
                    break;
                }
            }
            if (heavy == -1) break;
        }
        cout << ans << '\n';
    }
}