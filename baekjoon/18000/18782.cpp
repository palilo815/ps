#include <bits/stdc++.h>
using namespace std;

// http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2016/p0200r0.html
namespace std {
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
    int n;
    cin >> n;

    vector<vector<int>> adj(n);
    for (int i = n - 1, u, v; i--;) {
        cin >> u >> v, --u, --v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }

    vector<int> sz(n);
    y_combinator([&](auto self, int u) -> void {
        sz[u] = 1;
        for (const auto& v : adj[u]) {
            adj[v].erase(find(adj[v].begin(), adj[v].end(), u));
            self(v);
            sz[u] += sz[v];
        }
    })(0);

    vector<int> check(n - 1);
    auto valid = [&](int len) {
        fill(check.begin(), check.begin() + len, 0);
        for (int u = 0; u < n; ++u) {
            int cnt = 0, xorsum = 0;
            for (const auto& v : adj[u]) {
                int x = sz[v] % len;
                if (!x) continue;

                if (check[len - x])
                    --check[len - x], --cnt, xorsum ^= len - x;
                else
                    ++check[x], ++cnt, xorsum ^= x;
            }
            if (u && cnt > 1 || !u && cnt)
                return false;
            check[xorsum] = 0;
        }
        return true;
    };

    string ans = string(n - 1, '0');
    ans[0] = '1';
    for (int i = 1; i < n; ++i) {
        if ((n - 1) % (i + 1)) continue;
        if (valid(i + 1)) ans[i] = '1';
    }
    cout << ans;
}