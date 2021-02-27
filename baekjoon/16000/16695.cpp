#include <bits/stdc++.h>
using namespace std;

struct query {
    int t, u, v, lv;
};

struct disjoint_set {
    vector<int> par;
    vector<pair<int, int>> stk;

    disjoint_set(int n) : par(n, -1) {}
    void clear() {
        fill(par.begin(), par.end(), -1);
        stk.clear();
    }
    int find(int u) {
        while (par[u] >= 0) u = par[u];
        return u;
    }
    bool merge(int u, int v, bool f) {
        u = find(u), v = find(v);
        if (u == v) return false;

        if (par[u] > par[v]) swap(u, v);
        if (f) stk.emplace_back(v, par[v]);
        par[u] += par[v];
        par[v] = u;
        return true;
    }
    void roll_back(size_t check_point) {
        for (; stk.size() != check_point; stk.pop_back()) {
            const auto [u, sz] = stk.back();
            par[par[u]] -= sz, par[u] = sz;
        }
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;

    vector<query> q(m);
    int k = 0;
    for (auto& [t, u, v, lv] : q) {
        cin >> t >> u >> v;
        if (u > v) swap(u, v);
        if (t == 0) cin >> lv;
        else if (t == 2)
            lv = k++;
    }

    unordered_map<int, int> mp;
    for (int i = m; i--;) {
        auto& [t, u, v, lv] = q[i];
        if (t == 0) {
            if (auto it = mp.find(u << 17 | v); it != mp.end())
                t = it->second, q[it->second].t = ~i, q[it->second].lv = lv;
            else
                t = m;
        } else if (t == 1)
            mp[u << 17 | v] = i;
        else
            t = 0;
    }
    unordered_map<int, int>().swap(mp);

    vector<int> ans(k, -1);
    disjoint_set dsu(n);
    int level = 0;
    function<void(int, int, bool)> solve = [&](int l, int r, bool f) {
        if (l + 1 == r) {
            if (q[l].t == 0 && ans[q[l].lv] == -1 && dsu.find(q[l].u) == dsu.find(q[l].v))
                ans[q[l].lv] = level;
            return;
        }

        int m = l + r >> 1;
        auto check_point = dsu.stk.size();

        for (int i = m; i < r; ++i)
            if (q[i].t < 0 && ~q[i].t <= l && q[i].lv <= level)
                dsu.merge(q[i].u, q[i].v, true);
        solve(l, m, true);

        dsu.roll_back(check_point);

        for (int i = l; i < m; ++i)
            if (q[i].t > 0 && r <= q[i].t && q[i].lv <= level)
                dsu.merge(q[i].u, q[i].v, f);
        solve(m, r, f);
    };

    for (; level < 10; ++level) {
        dsu.clear();
        solve(0, m, false);
    }

    for (const auto& x : ans)
        cout << x << '\n';
}