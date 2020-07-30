#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
using ll = long long;
struct edge {
    int u, v, w;
};

const int mxN = 1e5;

int par[mxN + 1];
edge e[mxN - 1];

int _find(int u) {
    return par[u] < 0 ? u : (par[u] = _find(par[u]));
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N; cin >> N;
    loop(i, N - 1) cin >> e[i].u >> e[i].v >> e[i].w;
    sort(e, e + N - 1, [&](auto & a, auto & b) -> bool {
        return a.w > b.w;
    });

    ll ans = 0;
    memset(par + 1, -1, sizeof(int) * N);
    loop(i, N - 1) {
        int u = _find(e[i].u), v = _find(e[i].v);
        if (u ^ v) {
            ans += (ll)e[i].w * par[u] * par[v];
            if (par[u] < par[v]) swap(u, v);
            par[v] += par[u];
            par[u] = v;
        }
    }
    cout << ans;
    return 0;
}