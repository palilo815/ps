#include <bits/stdc++.h>
#define left (i << 1)
#define right (i << 1 | 1)
using namespace std;
using ll = long long;

const int mxN = 1e5;

vector<pair<int, int>> adj[mxN];
int t, sz[mxN], par[mxN], top[mxN], in[mxN], ord[mxN];
ll dist[mxN];

void dfs(int u, int p) {
    sz[u] = 1, par[u] = p;
    for (auto& e : adj[u]) {
        int& v = e.second;
        if (v == p) continue;

        dist[v] = dist[u] + e.first;
        dfs(v, u);
        sz[u] += sz[v];

        if (adj[u][0].second == p || sz[v] > sz[adj[u][0].second])
            swap(e, adj[u][0]);
    }
}
void hld(int u) {
    ord[t] = u, in[u] = t;
    ++t;
    for (auto& [_, v] : adj[u]) {
        if (v == par[u]) continue;
        top[v] = (v == adj[u][0].second ? top[u] : v);
        hld(v);
    }
}
void q1() {
    int u, v;
    cin >> u >> v;
    ll ans = dist[--u] + dist[--v];

    while (top[u] != top[v])
        sz[top[u]] < sz[top[v]] ? (u = par[top[u]]) : (v = par[top[v]]);
    ans -= (in[u] < in[v] ? dist[u] : dist[v]) << 1;
    cout << ans << '\n';
}
void q2() {
    int u, v, k;
    cin >> u >> v >> k;
    --u, --v;

    stack<int> stk;
    while (top[u] != top[v])
        if (sz[top[u]] < sz[top[v]]) {
            if (in[u] - in[top[u]] + 1 < k) k -= in[u] - in[top[u]] + 1;
            else {
                cout << ord[in[u] - k + 1] + 1 << '\n';
                return;
            }
            u = par[top[u]];
        } else {
            stk.emplace(v);
            v = par[top[v]];
        }

    int tmp = abs(in[u] - in[v]) + 1;
    if (tmp < k) k -= tmp;
    else {
        cout << ord[in[u] + (in[u] < in[v] ? (k - 1) : (-k + 1))] + 1 << '\n';
        return;
    }

    for (;;) {
        tmp = stk.top();
        stk.pop();
        v = top[tmp];

        if (in[tmp] - in[v] + 1 < k) k -= in[tmp] - in[v] + 1;
        else {
            cout << ord[in[v] + k - 1] + 1 << '\n';
            return;
        }
    }
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N;
    cin >> N;
    for (int u, v, w, i = 1; i < N; ++i) {
        cin >> u >> v >> w;
        --u, --v;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }

    dfs(0, -1);
    hld(0);

    int M;
    cin >> M;
    for (char q; M--;) {
        cin >> q;
        q == '1' ? q1() : q2();
    }
    return 0;
}