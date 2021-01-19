#include <bits/stdc++.h>
using namespace std;

const int mxN = 2e5;

struct disjoint_set {
    vector<int> par;
    disjoint_set(int n) {
        par.resize(n, -1);
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

pair<int, int> a[mxN + 1];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;

    int sz = 0;
    for (int i = 0, m; i < n; ++i, sz += m) {
        cin >> m;
        for (int j = sz; j < sz + m; ++j)
            cin >> a[j].first, a[j].second = i;
    }

    sort(a, a + sz, [&](auto& a, auto& b) {
        return a.first < b.first;
    });
    a[sz].first = INT_MAX;

    disjoint_set dsu(n);

    vector<tuple<int, int, int>> ans;
    ans.reserve(n - 1);

    for (int i = 0, j = 1; i < sz; i = j++) {
        // a[sz] is sentinel
        for (int root = a[i].second; a[i].first == a[j].first; ++j)
            if (dsu.merge(root, a[j].second))
                ans.emplace_back(root, a[j].second, a[i].first);
    }

    if (ans.size() != n - 1) cout << "impossible";
    else
        for (auto& [x, y, z] : ans)
            cout << x + 1 << ' ' << y + 1 << ' ' << z << '\n';
}