#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
struct edge {
    int u, v, w;
};

const int mxN = 1e4;
const int mxM = 1e5;

int a[mxN], par[mxN];
edge e[mxM];

int _find(int u) {
    return ~par[u] ? (par[u] = _find(par[u])) : u;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M; cin >> N >> M;
    loop(i, N) cin >> a[i];
    loop(i, M) {
        cin >> e[i].u >> e[i].v >> e[i].w;
        e[i].w = 2 * e[i].w + a[--e[i].u] + a[--e[i].v];
    }
    sort(e, e + M, [&](auto & a, auto & b) {
        return a.w < b.w;
    });
    memset(par, -1, sizeof(int) * N);

    int ans = *min_element(a, a + N), cnt = N - 1;
    loop(i, M) {
        int u = _find(e[i].u), v = _find(e[i].v);
        if (u ^ v) {
            par[u] = v, ans += e[i].w;
            if (--cnt == 0) break;
        }
    }
    cout << ans;
    return 0;
}