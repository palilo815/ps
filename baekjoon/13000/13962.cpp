#include <bits/stdc++.h>
using namespace std;
using ll = long long;
struct info {
    int id, r, t;
};

const int mxN = 1e5;

vector<int> adj[mxN];
info a[mxN];
int N, t, in[mxN], out[mxN];
ll ans[mxN], fenwick[mxN + 1];

void update(int i, int val) {
    for (++i; i <= N; i += i & -i)
        fenwick[i] += val;
}
ll read(int i) {
    ll ret = 0;
    for (; i; i -= i & -i)
        ret += fenwick[i];
    return ret;
}
void dfs(int u) {
    in[u] = t++;
    for (int& v : adj[u]) dfs(v);
    out[u] = t;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    cin >> N;
    int rt;
    for (int v = 0, u; v < N; ++v) {
        cin >> u >> a[v].r >> a[v].t;
        a[v].id = v;
        ~u ? adj[u - 1].emplace_back(v) : (rt = v);
    }

    dfs(rt);

    sort(a, a + N, [&](auto& a, auto& b) {
        return a.r == b.r ? in[a.id] < in[b.id] : a.r < b.r;
    });

    for (int i = 0; i < N; ++i) {
        ans[a[i].id] = read(out[a[i].id]) - read(in[a[i].id]);
        update(in[a[i].id], a[i].t);
    }

    for (int i = 0; i < N; ++i)
        cout << ans[i] << '\n';
    return 0;
}