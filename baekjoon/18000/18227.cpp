#include <bits/stdc++.h>
using namespace std;

const int mxN = 2e5 + 1;

vector<int> adj[mxN];
int t, d[mxN], in[mxN], out[mxN], fenwick[mxN];

void dfs(int u, int p) {
    d[u] = d[p] + 1;
    in[u] = ++t;
    for (int v : adj[u])
        if (v ^ p)
            dfs(v, u);
    out[u] = t;
}
void update(int i) {
    for (; i <= t; i += i & -i)
        ++fenwick[i];
}
int read(int i) {
    int ret = 0;
    for (; i; i -= i & -i)
        ret += fenwick[i];
    return ret;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, root; cin >> N >> root;
    for (int i = 1, u, v; i < N; ++i) {
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    dfs(root, 0);

    int Q; cin >> Q;
    for (int q, i; Q; --Q) {
        cin >> q >> i;
        if (q == 1) update(in[i]);
        else cout << (long long)d[i] * (read(out[i]) - read(in[i] - 1)) << '\n';
    }
    return 0;
}