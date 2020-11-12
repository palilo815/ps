#include <bits/stdc++.h>
using namespace std;

struct disjoint_set {
    vector<int> par;
    disjoint_set(int n) {
        par = vector<int>(n, -1);
    }
    int _find(int u) {
        return par[u] < 0 ? u : (par[u] = _find(par[u]));
    }
    void _union(int u, int v) {
        u = _find(u), v = _find(v);
        if (u == v) return;

        if (par[u] > par[v]) swap(u, v);
        par[u] += par[v];
        par[v] = u;
    }
};

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, M;
    cin >> N >> M;

    disjoint_set dset(N + 1);
    for (int u, v; M--;) {
        cin >> u >> v;
        dset._union(u, v);
    }

    int C, H, K;
    cin >> C >> H >> K;
    C = dset._find(C), H = dset._find(H);

    vector<int> vt;
    for (int i = 1; i <= N; ++i)
        if (i != C && i != H && dset.par[i] < 0)
            vt.emplace_back(dset.par[i]);

    sort(vt.begin(), vt.end());
    cout << -(dset.par[C] + accumulate(vt.begin(), min(vt.end(), vt.begin() + K), 0));
}