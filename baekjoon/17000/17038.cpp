#include <bits/stdc++.h>
using namespace std;

class disjoint_set {
    vector<int> par, enemy;

public:
    disjoint_set(int n) : par(n, -1), enemy(n, -1) {}

    int find(int u) {
        return par[u] < 0 ? u : par[u] = find(par[u]);
    }
    int merge(int u, int v) {
        if (u == -1) return v;
        if (v == -1) return u;
        u = find(u), v = find(v);
        if (u == v) return u;
        if (par[u] > par[v]) swap(u, v);
        par[u] += par[v];
        par[v] = u;
        return u;
    }
    bool ack(int u, int v) {
        u = find(u), v = find(v);
        if (enemy[u] == v) return false;
        int a = merge(u, v), b = merge(enemy[u], enemy[v]);
        enemy[a] = b;
        if (~b) enemy[b] = a;
        return true;
    }
    bool dis(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return false;
        int a = merge(u, enemy[v]), b = merge(v, enemy[u]);
        enemy[a] = b, enemy[b] = a;
        return true;
    }
    int get_ans() {
        int ret = 0;
        for (size_t i = 0; i < par.size(); ++i) {
            if (par[i] < 0) {
                ++ret;
                if (~enemy[i]) par[enemy[i]] = 0;
            }
        }
        return ret;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;
    disjoint_set dsu(n);
    for (int u, v; m--;) {
        char t;
        cin >> t >> u >> v, --u, --v;
        if (!(t == 'S' ? dsu.ack(u, v) : dsu.dis(u, v))) return cout << 0, 0;
    }
    cout << '1' << string(dsu.get_ans(), '0');
}