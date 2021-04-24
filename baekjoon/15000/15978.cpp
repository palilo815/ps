#include <bits/stdc++.h>
using namespace std;

namespace std {
// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0200r0.html
template <class Fun>
class y_combinator_result {
    Fun fun_;

public:
    template <class T>
    explicit y_combinator_result(T&& fun) : fun_(std::forward<T>(fun)) {}

    template <class... Args>
    decltype(auto) operator()(Args&&... args) {
        return fun_(std::ref(*this), std::forward<Args>(args)...);
    }
};

template <class Fun>
decltype(auto) y_combinator(Fun&& fun) {
    return y_combinator_result<std::decay_t<Fun>>(std::forward<Fun>(fun));
}
}; // namespace std

struct disjoint_set {
    vector<int> par;
    disjoint_set(int n) : par(n, -1) {}
    int find(int u) {
        return par[u] < 0 ? u : par[u] = find(par[u]);
    }
    int get_size(int u) {
        return -par[find(u)];
    }
    void merge(int u, int v) {
        u = find(u), v = find(v);
        if (u == v) return;

        if (par[u] > par[v]) swap(u, v);
        par[u] += par[v];
        par[v] = u;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n1, n2, k;
    cin >> n1 >> n2 >> k;

    int root1 = -1, root2 = -1;
    vector<vector<int>> tree1(n1), tree2(n2);
    for (int i = 0, p; i < n1; ++i) {
        cin >> p, --p;
        if (p == -1) root1 = i;
        else
            tree1[p].emplace_back(i);
    }
    for (int i = 0, p; i < n2; ++i) {
        cin >> p, --p;
        if (p == -1) root2 = i;
        else
            tree2[p].emplace_back(i);
    }

    assert(~root1);
    assert(~root2);

    vector<pair<int, int>> a;
    auto dfs = [&](vector<vector<int>>& tree, int root) {
        vector<int> dp(tree.size());
        fill(dp.begin(), dp.begin() + k, 1);

        vector<int> leaf(tree.size());
        iota(leaf.begin(), leaf.begin() + k, 0);

        y_combinator([&](auto self, int u) -> void {
            for (const auto& v : tree[u]) {
                self(v);
                dp[u] += dp[v];
                leaf[u] = leaf[v];
            }
        })(root);
        return make_pair(dp, leaf);
    };

    const auto [dp1, leaf1] = dfs(tree1, root1);
    const auto [dp2, leaf2] = dfs(tree2, root2);

    assert(dp1[root1] == k);
    assert(dp2[root2] == k);

    for (int i = k; i < n1; ++i)
        if (int(tree1[i].size() != 1))
            a.emplace_back(dp1[i], ~i);
    for (int i = k; i < n2; ++i)
        if (int(tree2[i].size() != 1))
            a.emplace_back(dp2[i], i);

    sort(a.begin(), a.end(), [&](auto& a, auto& b) {
        return a.first < b.first;
    });

    disjoint_set dsu(k);

    for (auto [sz, u] : a) {
        const auto& tree = u < 0 ? tree1 : tree2;
        const auto& leaf = u < 0 ? leaf1 : leaf2;
        if (u < 0) u = ~u;

        for (const auto& v : tree[u])
            dsu.merge(leaf[u], leaf[v]);

        if (sz != dsu.get_size(leaf[u]))
            return cout << "NO", 0;
    }
    cout << "YES";
}