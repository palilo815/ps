#include <bits/stdc++.h>
using namespace std;

const int mxN = 25e4;

vector<int> adj[mxN];
int N, t, in[mxN], out[mxN];

int fenwick[mxN + 1];

void update(int i, int val) {
    for (++i; i <= N; i += i & -i)
        fenwick[i] += val;
}
int read(int i) {
    int ret = 0;
    for (++i; i; i -= i & -i)
        ret += fenwick[i];
    return ret;
}
void dfs(int u) {
    in[u] = t++;
    for (int& v : adj[u]) dfs(v);
    out[u] = t;
}
void A() {
    int u, v;
    cin >> u >> v;
    update(in[v - 1], -1);
    update(out[v - 1], 1);
}
void W() {
    int u;
    cin >> u;
    cout << read(in[u - 1]) << '\n';
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    cin >> N;
    for (int i = 1, u, v; i < N; ++i) {
        cin >> u >> v;
        adj[u - 1].emplace_back(v - 1);
    }

    dfs(0);

    for (int i = 1; i < N; ++i)
        update(in[i], 1), update(out[i], -1);

    int M;
    cin >> M;
    M += N - 1;

    for (char q; M--;) {
        cin >> q;
        q == 'A' ? A() : W();
    }
    return 0;
}