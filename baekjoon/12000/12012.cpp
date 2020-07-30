#include <bits/stdc++.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
struct edge {
    int u, v;
};

const int mxN = 2e5;
const string s[2] = {"NO\n", "YES\n"};

edge e[mxN + 1];
int q[mxN + 1], par[mxN];

int _find(int u) {
    return par[u] < 0 ? u : (par[u] = _find(par[u]));
}
void _union(int i) {
    int u = _find(e[i].u), v = _find(e[i].v);
    if (u == v) return;
    if (u < v) swap(u, v);
    par[v] += par[u];
    par[u] = v;
}
int main() {
    cin.tie(0), cout.tie(0);
    ios::sync_with_stdio(0);

    int N, M; cin >> N >> M;
    loop(i, M) cin >> e[i].u >> e[i].v;
    loop(i, N) {
        int x; cin >> x;
        q[x] = i;
    }

    loop(i, M) {
        e[i].u = q[e[i].u], e[i].v = q[e[i].v];
        if (e[i].u < e[i].v) swap(e[i].u, e[i].v);
    }
    sort(e, e + M, [&](edge & a, edge & b) -> bool {
        return a.v > b.v;
    });
    e[M].v = -1;

    for (int i = N - 1, j = 0; ~i; --i) {
        par[i] = -1;
        while (e[j].v == i)
            _union(j++);
        q[i] = par[_find(i)] == i - N;
    }
    loop(i, N) cout << s[q[i]];
    return 0;
}