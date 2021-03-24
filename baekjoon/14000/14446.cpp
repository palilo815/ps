#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct BIT {
    BIT(int _n) : n(_n), tree(_n + 1) {}
    void update(int i, T val) {
        for (++i; i <= n; i += i & -i)
            tree[i] += val;
    }
    T query(int i) {
        T ret = 0;
        for (; i; i &= i - 1)
            ret += tree[i];
        return ret;
    }
    T query(int l, int r) {
        return query(r) - query(l);
    }

private:
    const int n;
    vector<T> tree;
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;

    vector<int> p(n);
    for (auto& x : p) cin >> x;

    vector<vector<int>> adj(n);
    for (int i = 1, p; i < n; ++i) {
        cin >> p, --p;
        adj[p].emplace_back(i);
    }

    vector<int> in(n), out(n);
    int t = 0;
    auto dfs = [&](auto&& self, int u) -> void {
        in[u] = t++;
        for (const auto& v : adj[u]) self(self, v);
        out[u] = t;
    };
    dfs(dfs, 0);

    vector<int> ans(n), idx(n);
    iota(idx.begin(), idx.end(), 0);
    sort(idx.begin(), idx.end(), [&](auto& a, auto& b) {
        return p[a] > p[b];
    });

    BIT<int> bit(n);
    for (const auto& u : idx) {
        ans[u] = bit.query(in[u], out[u]);
        bit.update(in[u], 1);
    }
    for (const auto& x : ans) cout << x << '\n';
}