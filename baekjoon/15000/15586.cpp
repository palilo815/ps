#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
struct edge {
    int u, v, w;
};
struct query {
    int k, u, i;
};

const int mx = 1e5;

int par[mx + 1], ans[mx];
edge e[mx];
query q[mx];

int _find(int u) {
    return par[u] < 0 ? u : (par[u] = _find(par[u]));
}
void _union(int i) {
    int u = _find(e[i].u), v = _find(e[i].v);
    if (u == v) return;
    if (par[u] < par[v]) swap(u, v);
    par[v] += par[u];
    par[u] = v;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, Q; cin >> N >> Q;
    loop(i, N - 1) cin >> e[i].u >> e[i].v >> e[i].w;
    loop(i, Q) cin >> q[i].k >> q[i].u;
    loop(i, Q) q[i].i = i;

    sort(e, e + N - 1, [&](auto & a, auto & b) -> bool {
        return a.w > b.w;
    });
    sort(q, q + Q, [&](auto & a, auto & b) -> bool {
        return a.k > b.k;
    });
    e[N].w = -1;

    memset(par + 1, -1, sizeof(int) * N);
    for (int i = 0, j = 0; i < Q; ++i) {
        auto& [k, u, id] = q[i];
        while (e[j].w >= k)
            _union(j++);
        ans[id] = ~par[_find(u)];
    }
    loop(i, Q) cout << ans[i] << '\n';
    return 0;
}