#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e3;

struct disjoint_set {
    int par[mxN];
    void init(int n) {
        memset(par, -1, sizeof(int) * n);
    }
    int find(int u) {
        return par[u] < 0 ? u : par[u] = find(par[u]);
    }
    bool merge(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return false;

        if (par[u] > par[v]) swap(u, v);
        par[u] += par[v];
        par[v] = u;
        return true;
    }
};

bitset<mxN * mxN> visited;
disjoint_set dsu;

int solve() {
    int n, seed, a, b;
    cin >> n >> seed >> a >> b;

    dsu.init(n);
    visited.reset();

    for (int e = seed % (n * n), cnt = n - 1, i = 1; !visited[e]; e = ((int64_t)e * a + b) % (n * n), ++i) {
        visited[e] = true;
        if (dsu.merge(e / n, e % n) && !--cnt)
            return i;
    }
    return 0;
}
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int T;
    cin >> T;
    while (T--) cout << solve() << '\n';
}