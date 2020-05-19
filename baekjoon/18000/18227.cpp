#include <bits/stdc++.h>
using namespace std;

const int max_N = 200001;

vector<int> adj[max_N];
int _time;
int d[max_N];
int in[max_N];
int out[max_N];
int fenwick[max_N];

void DFS(int u, int p) {
    d[u] = d[p] + 1;
    in[u] = ++_time;
    for (int v : adj[u]) if (v != p)
        DFS(v, u);
    out[u] = _time;
}
void update(int i, int w) {
    while (i <= _time) {
        fenwick[i] += w;
        i += i & -i;
    }
}
long long read(int i) {
    long long ret = 0;
    while (i) {
        ret += fenwick[i];
        i -= i & -i;
    }
    return ret;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, rt; cin >> N >> rt;
    for (int i = 1; i < N; ++i) {
        int u, v; cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    DFS(rt, 0);

    int Q; cin >> Q;
    while (Q--) {
        int q, i; cin >> q >> i;
        if (q == 1) update(in[i], 1);
        else cout << d[i] * (read(out[i]) - read(in[i] - 1)) << '\n';
    }
    return 0;
}