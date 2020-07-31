#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
struct edge {
    int u, v, w;
};

const int mx = 25e4;
const string ans[2] = {"NO\n", "YES\n"};

int x[mx], y[mx], a[mx], par[mx];
edge e[(mx << 1) - 1];
edge q[mx];

int _find(int u) {
    return ~par[u] ? (par[u] = _find(par[u])) : u;
}
void _union(int i) {
    int u = _find(e[i].u), v = _find(e[i].v);
    if (u ^ v) par[u] = v;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, Q; cin >> N >> Q;
    loop(i, N) cin >> x[i] >> y[i];
    loop(i, Q) cin >> q[i].u >> q[i].v >> q[i].w;
    loop(i, Q) --q[i].u, --q[i].v;
    iota(a, a + N, 0);

    sort(a, a + N, [&](int& a, int& b) {
        return x[a] < x[b];
    });
    loop(i, N - 1) e[i] = {a[i], a[i + 1], x[a[i + 1]] - x[a[i]]};
    sort(a, a + N, [&](int& a, int& b) {
        return y[a] < y[b];
    });
    loop(i, N - 1) e[N - 1 + i] = {a[i], a[i + 1], y[a[i + 1]] - y[a[i]]};

    sort(e, e + (N - 1) * 2, [&](auto & a, auto & b) {
        return a.w < b.w;
    });
    e[(N - 1) * 2].w = INT_MAX;

    iota(a, a + Q, 0);
    sort(a, a + Q, [&](int& a, int& b) {
        return q[a].w < q[b].w;
    });

    memset(par, -1, sizeof(int) * N);
    int j = 0;
    loop(i, Q) {
        auto& [u, v, w] = q[a[i]];
        while (e[j].w <= w) _union(j++);
        w = _find(u) == _find(v);
    }
    loop(i, Q) cout << ans[q[i].w];
    return 0;
}