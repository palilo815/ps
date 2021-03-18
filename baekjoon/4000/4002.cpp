#include <bits/stdc++.h>
using namespace std;

template <typename node_t>
struct complete_seg {
    complete_seg(int _n, vector<int>& _val) : n(_n), val(_val), tree(n << 1) {}

    node_t& operator[](int i) { return tree[n + i]; }
    void build() {
        for (int i = n - 1; i; --i)
            pull(i);
    }
    void erase(int idx) {
        tree[idx += n] = n;
        while (idx >>= 1) pull(idx);
    }
    node_t query(int l, int r) const {
        node_t ret = n;
        for (l += n, r += n; l != r; l >>= 1, r >>= 1) {
            if (l & 1) ret = op(ret, tree[l++]);
            if (r & 1) ret = op(tree[--r], ret);
        }
        return ret;
    }

private:
    const int n;
    const vector<int>& val;
    vector<node_t> tree;

    void pull(int i) {
        tree[i] = op(tree[i << 1], tree[i << 1 | 1]);
    }
    node_t op(node_t lhs, node_t rhs) const {
        return val[lhs] > val[rhs] ? lhs : rhs;
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

    vector<vector<int>> adj(n);
    vector<int> c(n + 1), l(n); // c[n] is sentinel
    for (int i = 0, b; i < n; ++i) {
        cin >> b >> c[i] >> l[i], --b;
        if (~b) adj[b].emplace_back(i);
    }

    vector<int> in(n), out(n);
    int t = 0;
    auto dfs = [&](auto&& self, int u) -> void {
        in[u] = t++;
        for (const auto& v : adj[u]) self(self, v);
        out[u] = t;
    };
    dfs(dfs, 0);

    complete_seg<int> seg(n, c);
    for (int i = 0; i < n; ++i)
        seg[in[i]] = i;
    seg.build();

    vector<pair<int, int>> sub(n);
    for (int u = n; u--;) {
        int64_t salary = c[u];
        int sz = 1;

        for (const auto& v : adj[u])
            salary += sub[v].first, sz += sub[v].second;

        for (; salary > m; --sz) {
            const auto who = seg.query(in[u], out[u]);
            salary -= c[who];
            seg.erase(in[who]);
        }
        sub[u] = {int(salary), sz};
    }

    int64_t ans = 0;
    for (int i = 0; i < n; ++i)
        if (const auto val = 1LL * l[i] * sub[i].second; val > ans)
            ans = val;
    cout << ans;
}