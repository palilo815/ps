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
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<pair<int, int>>> adj(n);
    for (int i = 0, u, v; i < m; ++i) {
        cin >> u >> v, --u, --v;
        adj[u].emplace_back(i, v);
        adj[v].emplace_back(i, u);
    }
    vector<int> gganbu(k);
    for (auto& x : gganbu) {
        cin >> x, --x;
    }
    vector<char> colour(n);
    vector<bool> banned(m);
    auto dfs = y_combinator([&](auto self, int u) -> bool {
        for (const auto& [id, v] : adj[u]) {
            if (banned[id]) continue;
            if (colour[v]) {
                if (colour[u] == colour[v]) return false;
            } else {
                colour[v] = colour[u] == 'w' ? 'b' : 'w';
                if (!self(v)) return false;
            }
        }
        return true;
    });
    auto f = [&](auto mid) -> bool {
        fill(banned.begin(), banned.end(), false);
        for_each(gganbu.begin(), gganbu.begin() + mid, [&](const auto& x) {
            banned[x] = true;
        });
        fill(colour.begin(), colour.end(), '\0');
        colour[0] = 'w';
        return dfs(0);
    };
    auto parametric = [&](auto lo, auto hi) {
        // first true
        while (lo != hi) {
            auto mid = lo + (hi - lo) / 2;
            f(mid) ? hi = mid : lo = mid + 1;
        }
        return lo;
    };
    auto res = parametric(0, k + 1);
    if (res == k + 1) return cout << -1, 0;
    f(res);
    if (any_of(colour.begin(), colour.end(), [&](const auto& x) { return !x; })) {
        return cout << -1, 0;
    }
    const auto w = count(colour.begin(), colour.end(), 'w'), b = n - w;
    cout << res << '\n'
         << min(w, b) << ' ' << max(w, b);
}