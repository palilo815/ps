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
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> adj(n);
    for (int u, v, w; m--;) {
        cin >> u >> v >> w, --u, --v;
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
    }
    int64_t x = LLONG_MAX;
    vector<int64_t> c(n);
    vector<char> coeff(n);
    coeff[0] = '+'; // value[0] = +x
    y_combinator([&](auto self, int u, int p) -> void {
        for (const auto& [w, v] : adj[u]) {
            if (v == p) continue;
            if (coeff[v]) {
                if (coeff[u] == coeff[v]) {
                    int64_t _2x = w - c[u] - c[v];
                    if (_2x & 1) {
                        cout << "No";
                        exit(0);
                    }
                    int64_t new_x = _2x / (coeff[u] == '+' ? 2 : -2);
                    if (x != LLONG_MAX && x != new_x) {
                        cout << "No";
                        exit(0);
                    }
                    x = new_x;
                } else if (c[u] + c[v] != w) {
                    cout << "No";
                    exit(0);
                }
            } else {
                coeff[v] = coeff[u] == '+' ? '-' : '+';
                c[v] = w - c[u];
                self(v, u);
            }
        }
    })(0, -1);
    if (x == LLONG_MAX) {
        auto c2 = c;
        for (int i = 0; i < n; ++i) {
            if (coeff[i] == '-') {
                c2[i] = -c2[i];
            }
        }
        sort(c2.begin(), c2.end());
        x = -c2[c2.size() >> 1];
    }
    cout << "Yes\n";
    for (int i = 0; i < n; ++i) {
        cout << (coeff[i] == '+' ? x : -x) + c[i] << ' ';
    }
}