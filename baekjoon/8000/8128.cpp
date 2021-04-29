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

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, l;
    cin >> n >> l;
    if (!l) return cout << 0, 0;

    vector<vector<int>> adj(n);
    for (int i = n - 1, u, v; i--;) {
        cin >> u >> v, --u, --v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    auto bfs = [&](int s) {
        vector dist(n, -1);
        dist[s] = 0;

        queue<int> q;
        q.emplace(s);

        while (!q.empty()) {
            const auto u = q.front();
            q.pop();

            for (const auto& v : adj[u])
                if (dist[v] == -1) {
                    dist[v] = dist[u] + 1;
                    q.emplace(v);
                }
        }
        return max_element(dist.begin(), dist.end()) - dist.begin();
    };
    int root = bfs(bfs(0));

    auto rev_dfs_ord = [&](int src) {
        vector<int> stk = {src}, ord(n);

        for (int i = 0; i < n; ++i) {
            const auto u = stk.back();
            stk.pop_back();

            ord[i] = u;
            for (const auto& v : adj[u]) {
                adj[v].erase(find(adj[v].begin(), adj[v].end(), u));
                stk.emplace_back(v);
            }
        }
        reverse(ord.begin(), ord.end());
        return ord;
    }(root);

    vector<int> dp(n);
    for (const auto& u : rev_dfs_ord) {
        if (adj[u].empty()) {
            dp[u] = 1;
            continue;
        }
        auto heavy = *max_element(adj[u].begin(), adj[u].end(), [&](auto& a, auto& b) {
            return dp[a] < dp[b];
        });
        dp[u] = dp[heavy] + 1;
        dp[heavy] = 0;
    }

    auto pivot = dp.begin() + min(n, (l << 1) - 1);
    nth_element(dp.begin(), pivot, dp.end(), greater<int>());
    cout << accumulate(dp.begin(), pivot, 0);
}