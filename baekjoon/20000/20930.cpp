#include <bits/stdc++.h>
using namespace std;

struct line {
    int x1, y1, x2, y2, id;
};

struct disjoint_set {
    vector<int> par;
    disjoint_set(int n) : par(n, -1) {}
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

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, q;
    cin >> n >> q;

    vector<line> a(n + 1);
    for (int i = 0; i < n; ++i) {
        cin >> a[i].x1 >> a[i].y1 >> a[i].x2 >> a[i].y2;
        if (a[i].x1 > a[i].x2) swap(a[i].x1, a[i].x2);
        if (a[i].y1 > a[i].y2) swap(a[i].y1, a[i].y2);
        a[i].id = i;
    }
    a[n].x1 = a[n].y1 = INT_MAX; // sentinel

    disjoint_set dsu(n);

    sort(a.begin(), a.end(), [&](auto& a, auto& b) {
        return a.x1 < b.x1;
    });
    for (int i = 0, j = 0, mx; i < n; i = j) {
        mx = a[i].x2;
        for (; a[j].x1 <= mx; ++j)
            mx = max(mx, a[j].x2);

        for (int it = i + 1; it < j; ++it)
            dsu.merge(a[i].id, a[it].id);
    }

    sort(a.begin(), a.end(), [&](auto& a, auto& b) {
        return a.y1 < b.y1;
    });
    for (int i = 0, j = 0, mx; i < n; i = j) {
        mx = a[i].y2;
        for (; a[j].y1 <= mx; ++j)
            mx = max(mx, a[j].y2);

        for (int it = i + 1; it < j; ++it)
            dsu.merge(a[i].id, a[it].id);
    }

    for (int u, v; q--;) {
        cin >> u >> v, --u, --v;
        cout << (dsu.find(u) == dsu.find(v)) << '\n';
    }
}