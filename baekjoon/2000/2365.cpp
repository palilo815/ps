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

struct edge_t {
    int v, rev, cap;
    edge_t(int v, int rev, int cap) : v(v), rev(rev), cap(cap) {}
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    // s = 0, t = 2n + 1
    // row = [1, n], col = [n + 1, 2n]
    // size = 2n + 2
    int n;
    cin >> n;
    vector<int> rsum(n), csum(n);
    for (auto& x : rsum) cin >> x;
    for (auto& x : csum) cin >> x;
    vector<vector<edge_t>> adj(2 * n + 2);
    auto add_edge = [&](int u, int v, int c) {
        adj[u].emplace_back(v, adj[v].size(), c);
        adj[v].emplace_back(u, adj[u].size() - 1, 0);
    };
    const auto total = accumulate(rsum.begin(), rsum.end(), 0);
    const int s = 0, t = 2 * n + 1;
    for (int i = 0; i < n; ++i) {
        add_edge(s, i + 1, rsum[i]);
    }
    for (int i = 0; i < n; ++i) {
        add_edge(i + n + 1, t, csum[i]);
    }
    for (int r = 1; r <= n; ++r) {
        for (int c = n + 1; c <= n + n; ++c) {
            add_edge(r, c, 0);
        }
    }
    vector<int> level(2 * n + 2), ptr(2 * n + 2);
    auto bfs = [&]() {
        fill(level.begin(), level.end(), 0);
        level[s] = 1;
        queue<int> q;
        q.emplace(s);
        while (!q.empty()) {
            const auto u = q.front();
            q.pop();
            for (const auto& [v, rev, capa] : adj[u])
                if (capa && !level[v]) {
                    level[v] = level[u] + 1;
                    q.emplace(v);
                }
        }
        return level[t];
    };
    auto dfs = y_combinator([&](auto dfs, int u, int f) {
        if (u == t) return f;
        for (int &i = ptr[u], sz = adj[u].size(); i < sz; ++i) {
            auto& [v, rev, cap] = adj[u][i];
            if (cap && level[u] + 1 == level[v])
                if (const auto d = dfs(v, min(f, cap)); d) {
                    return cap -= d, adj[v][rev].cap += d, d;
                }
        }
        return 0;
    });
    auto f = [&](const int lim) -> bool {
        for (auto& [v, rev, cap] : adj[s]) {
            cap = rsum[v - 1];
        }
        for (int r = 1; r <= n; ++r) {
            for (auto& [v, rev, cap] : adj[r]) {
                cap = v == s ? 0 : lim;
            }
        }
        for (int c = n + 1; c <= n + n; ++c) {
            for (auto& [v, rev, cap] : adj[c]) {
                cap = v == t ? csum[c - n - 1] : 0;
            }
        }
        for (auto& [v, rev, cap] : adj[t]) {
            cap = 0;
        }
        int ret = 0;
        for (int f; bfs();) {
            fill(ptr.begin(), ptr.end(), 0);
            while ((f = dfs(s, INT_MAX))) ret += f;
        }
        return ret == total;
    };
    int lo = 0, hi = 1e4;
    while (lo != hi) {
        const auto mid = (lo + hi) >> 1;
        f(mid) ? hi = mid : lo = mid + 1;
    }
    f(lo);
    cout << lo << '\n';
    vector<int> flow(n);
    for (int r = 1; r <= n; ++r) {
        for (const auto& [v, rev, cap] : adj[r]) {
            if (v != s) {
                flow[v - n - 1] = lo - cap;
            }
        }
        for (const auto& f : flow) {
            cout << f << ' ';
        }
        cout << '\n';
    }
}