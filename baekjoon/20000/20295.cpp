#include <bits/stdc++.h>
#define left (i << 1)
#define right (i << 1 | 1)
using namespace std;

const int mxN = 1e5 + 1;

vector<int> adj[mxN];
int t, sz[mxN], par[mxN], top[mxN], in[mxN];
char a[mxN], segT[mxN - 1 << 1];

void dfs(int u) {
    sz[u] = 1;
    for (int i = 0; i < adj[u].size(); ++i) {
        int& v = adj[u][i];
        if (v == par[u]) {
            swap(v, adj[u].back());
            adj[u].pop_back();
            --i;
            continue;
        }

        par[v] = u;
        dfs(v);
        sz[u] += sz[v];

        if (sz[v] > sz[adj[u][0]])
            swap(v, adj[u][0]);
    }
}
void hld(int u) {
    in[u] = t++;
    bool heavy = true;
    for (int& v : adj[u]) {
        top[v] = heavy ? top[u] : v;
        hld(v);
        heavy = false;
    }
}
bool query(int u, int v, char x) {
    for (; top[u] != top[v]; u = par[top[u]]) {
        if (sz[top[u]] > sz[top[v]]) swap(u, v);
        for (int l = in [top[u]], r = in[u] + 1; l != r; l >>= 1, r >>= 1) {
            if (l & 1 && segT[l++] & x) return true;
            if (r & 1 && segT[--r] & x) return true;
        }
    }
    if (in[u] > in[v]) swap(u, v);
    for (int l = in[u], r = in[v] + 1; l != r; l >>= 1, r >>= 1) {
        if (l & 1 && segT[l++] & x) return true;
        if (r & 1 && segT[--r] & x) return true;
    }
    return false;
}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N;
    cin >> N;

    for (int i = 1, x; i <= N; ++i) {
        cin >> x;
        a[i] = 1 << x;
    }

    for (int i = 1, u, v; i < N; ++i) {
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    t = N;
    top[1] = 1;
    dfs(1);
    hld(1);

    for (int i = 1; i <= N; ++i)
        segT[in[i]] = a[i];
    for (int i = N - 1; i; --i)
        segT[i] = segT[left] | segT[right];

    int M, u, v, x;
    cin >> M >> u >> x;

    for (cout << (segT[1] & (1 << x) ? "PLAY" : "CRY"); --M; u = v) {
        cin >> v >> x;
        cout << (query(u, v, 1 << x) ? "\nPLAY" : "\nCRY");
    }
}