#include <bits/stdc++.h>
using namespace std;

struct query {
    int t, u, v;
};

struct disjoint_set {
    vector<int> par;
    vector<pair<int, int>> stk;

    disjoint_set(int n) : par(n, -1) {}
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
    for (auto& [t, u, v] : q) {
        cin >> t >> u >> v, --u, --v;
        if (u > v) swap(u, v);
    }

    vector<int> psum(m + 1);
    unordered_map<int, int> mp;
    for (int i = m; i--;) {
        auto& [t, u, v] = q[i];
        if (t == 1) {
            if (auto it = mp.find(u << 17 | v); it != mp.end())
                t = it->second, q[it->second].t = ~i;
            else
                t = m;
        } else if (t == 2)
            mp[u << 17 | v] = i;
        else
            t = 0, psum[i + 1] = 1;
    }
    unordered_map<int, int>().swap(mp);

    partial_sum(psum.begin(), psum.end(), psum.begin());
    auto cnt = [&](int l, int r) { return psum[r] - psum[l]; };

    disjoint_set dsu(n);
    function<void(int, int, bool)> solve = [&](int l, int r, bool f) {
        if (l + 1 == r) {
            cout << (dsu.find(q[l].u) == dsu.find(q[l].v)) << '\n';
            return;
        }

        int m = l + r >> 1;
        if (cnt(l, m)) {
            auto check_point = dsu.stk.size();
            for (int i = m; i < r; ++i)
                if (q[i].t < 0 && ~q[i].t <= l)
                    dsu.merge(q[i].u, q[i].v, true);
            solve(l, m, true);
            dsu.roll_back(check_point);
        }
        if (cnt(m, r)) {
            for (int i = l; i < m; ++i)
                if (q[i].t > 0 && r <= q[i].t)
                    dsu.merge(q[i].u, q[i].v, f);
            solve(m, r, f);
        }
    };
    solve(0, m, false);
}