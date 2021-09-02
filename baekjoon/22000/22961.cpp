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

template <class T>
bool chmin(T& _old, T _new) { return _old > _new && (_old = _new, true); }
template <class T>
bool chmax(T& _old, T _new) { return _old < _new && (_old = _new, true); }

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;
    vector<int64_t> c(n), d(n);
    for (auto& x : c) cin >> x;
    for (auto& x : d) cin >> x;
    vector<vector<int>> adj(n);
    {
        vector<vector<pair<int, int>>> tree(n);
        for (int i = n - 1, u, v, w; i--;) {
            cin >> u >> v >> w, --u, --v;
            tree[u].emplace_back(w, v);
            tree[v].emplace_back(w, u);
        }
        vector<pair<int64_t, int>> stk;
        vector<bool> visited(n);
        for (int s = 0; s < n; ++s) {
            fill(visited.begin(), visited.end(), false);
            visited[s] = true;
            stk.emplace_back(d[s], s);
            while (!stk.empty()) {
                const auto [can, u] = stk.back();
                stk.pop_back();
                for (const auto& [w, v] : tree[u]) {
                    if (!visited[v] && w <= can) {
                        visited[v] = true;
                        stk.emplace_back(max(can - w, d[v]), v);
                        adj[s].emplace_back(v);
                    }
                }
            }
        }
    }
    vector<vector<int>> scc;
    {
        vector<int> dis(n, -1), low(n), stk;
        int dfs_time = 0;
        for (int i = 0; i < n; ++i) {
            if (~dis[i]) continue;
            y_combinator([&](auto self, int u) -> void {
                dis[u] = low[u] = dfs_time++;
                stk.emplace_back(u);
                for (const auto& v : adj[u]) {
                    if (dis[v] == -1) {
                        self(v);
                        chmin(low[u], low[v]);
                    } else {
                        chmin(low[u], dis[v]);
                    }
                }
                if (dis[u] == low[u]) {
                    scc.emplace_back();
                    int x;
                    do {
                        x = stk.back();
                        stk.pop_back();
                        dis[x] = INT_MAX;
                        scc.back().emplace_back(x);
                    } while (x != u);
                }
            })(i);
        }
        assert(stk.empty());
    }
    vector<int64_t> best(n, LLONG_MIN), worst(n, LLONG_MAX);
    for (const auto& component : scc) {
        const auto mnmx = minmax_element(component.begin(), component.end(), [&](const auto& lhs, const auto& rhs) {
            return c[lhs] < c[rhs];
        });
        auto w = c[*mnmx.first], b = c[*mnmx.second];
        for (const auto& u : component) {
            for (const auto& v : adj[u]) {
                chmax(b, best[v]), chmin(w, worst[v]);
            }
        }
        for (const auto& u : component) {
            best[u] = b, worst[u] = w;
        }
    }
    transform(best.begin(), best.end(), worst.begin(), best.begin(), minus());
    for (const auto& x : best) {
        cout << x << '\n';
    }
}