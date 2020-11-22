#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5 + 1;

struct mark {
    int when, s, e;
};

vector<int> adj[mxN];
int t, sz[mxN], par[mxN], top[mxN], in[mxN];
mark visited[mxN];

void dfs(int u) {
    sz[u] = 1;
    for (int& v : adj[u])
        if (v != par[u]) {
            par[v] = u;
            dfs(v);
            sz[u] += sz[v];
        }
}
void hld(int u) {
    in[u] = t++;

    int heavy = 0;
    for (int& v : adj[u])
        if (v != par[u] && sz[v] > sz[heavy])
            heavy = v;

    if (heavy) {
        top[heavy] = top[u];
        hld(heavy);
    }

    for (int& v : adj[u])
        if (v != par[u] && v != heavy) {
            top[v] = v;
            hld(v);
        }
}
#define book visited[top[u]]
void visit(int when, int u, int v) {
    for (; top[u] != top[v]; u = par[top[u]]) {
        if (sz[top[u]] > sz[top[v]]) swap(u, v);
        book = {when, in[top[u]], in[u]};
    }
    if (in[u] > in[v]) swap(u, v);
    book = {when, in[u], in[v]};
}
void query(int when, int u, int v) {
    int ans = 0;
    for (; top[u] != top[v]; u = par[top[u]]) {
        if (sz[top[u]] > sz[top[v]]) swap(u, v);
        if (book.when == when && book.s <= in[u])
            ans += min(in[u], book.e) - book.s + 1;
    }
    if (in[u] > in[v]) swap(u, v);
    if (book.when == when)
        ans += max(0, min(in[v], book.e) - max(in[u], book.s) + 1);
    cout << ans << '\n';
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, q;
    cin >> n >> q;

    for (int i = 1, u, v; i < n; ++i) {
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    top[1] = 1;
    dfs(1);
    hld(1);

    for (int i = 1, u, v; i <= q; ++i) {
        cin >> u >> v;
        visit(i, u, v);
        cin >> u >> v;
        query(i, u, v);
    }
}