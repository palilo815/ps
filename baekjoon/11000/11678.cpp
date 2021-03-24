#include <bits/stdc++.h>
using namespace std;

struct disjoint_set {
    vector<int> par, enemy;
    disjoint_set(int n) : par(n, -1), enemy(n, -1) {}
    void clear() {
        fill(par.begin(), par.end(), -1);
        fill(enemy.begin(), enemy.end(), -1);
        enemy[26] = 27, enemy[27] = 26;
    }
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
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;

    vector<tuple<int, int, int, int>> a(n);
    for (auto& [card0, card1, player, cnt] : a) {
        char c0, c1;
        cin >> c0 >> c1 >> player >> cnt;
        card0 = c0 - 'A', card1 = c1 - 'A', player += 25;
    }

    disjoint_set dsu(28);

    vector<bool> secret(26);
    secret[0] = secret[1] = secret[2] = true;

    int ans = 0;
    do {
        dsu.clear();
        bool ok = true;
        for (const auto& [c0, c1, p, cnt] : a) {
            if (int num_secret = secret[c0] + secret[c1]; num_secret == 0)
                switch (cnt) {
                case 0: ok = dsu.dis(c0, p) && dsu.dis(c1, p); break;
                case 1: ok = dsu.dis(c0, c1); break;
                case 2: ok = dsu.ack(c0, p) && dsu.ack(c1, p);
                }
            else if (num_secret == 1)
                switch (cnt) {
                case 0: ok = dsu.dis(secret[c0] ? c1 : c0, p); break;
                case 1: ok = dsu.ack(secret[c0] ? c1 : c0, p); break;
                case 2: ok = false;
                }
            else if (cnt)
                ok = false;
            if (!ok) break;
        }
        if (ok) ++ans;
    } while (prev_permutation(secret.begin(), secret.end()));
    cout << ans;
}