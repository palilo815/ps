#include <bits/stdc++.h>
using namespace std;

struct disjoint_set {
    vector<int> par, enemy;
    disjoint_set(int n) {
        par.resize(n, -1);
        enemy.resize(n);
    }
    int find(int u) {
        return par[u] < 0 ? u : par[u] = find(par[u]);
    }
    void merge(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return;

        if (par[u] > par[v]) swap(u, v);
        par[u] += par[v];
        par[v] = u;
    }
    bool split(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return false;

        if (enemy[u]) merge(enemy[u], v);
        if (enemy[v]) merge(enemy[v], u);
        enemy[u] = v, enemy[v] = u;
        return true;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;

    disjoint_set dsu(n + 1);

    for (int u, v; m--;) {
        cin >> u >> v;
        if (!dsu.split(u, v))
            return cout << 0, 0;
    }
    cout << 1;
}