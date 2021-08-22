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
    int n, m, q;
    cin >> n >> m >> q;
    vector h(n, vector<pair<int, int>>(m));
    for (auto& row : h) {
        for (auto& x : row) {
            cin >> x.first;
            x.second = INT_MAX;
        }
    }
    vector t(n, vector<int>(m, -1));
    vector par(n, vector(m, pair(-1, -1)));
    auto _find = y_combinator([&](auto self, pair<int, int> u) -> pair<int, int> {
        return par[u.first][u.second] == pair(-1, -1) ? u : self(par[u.first][u.second]);
    });
    auto _union = [&](pair<int, int> u, pair<int, int> v) {
        u = _find(u), v = _find(v);
        if (u == v) return;
        if (h[u.first][u.second] > h[v.first][v.second]) swap(u, v);
        par[v.first][v.second] = u;
    };
    for (int i = 0, x, y, c; i < q; ++i) {
        cin >> x >> y >> c, --x, --y;
        h[x][y] = {h[x][y].first - c, i};
        if (x && h[x - 1][y].second != INT_MAX) _union(pair(x, y), pair(x - 1, y));
        if (x + 1 != n && h[x + 1][y].second != INT_MAX) _union(pair(x, y), pair(x + 1, y));
        if (y && h[x][y - 1].second != INT_MAX) _union(pair(x, y), pair(x, y - 1));
        if (y + 1 != m && h[x][y + 1].second != INT_MAX) _union(pair(x, y), pair(x, y + 1));
        auto root = _find(pair(x, y));
        if (h[x][y] < h[root.first][root.second]) {
            par[root.first][root.second] = pair(x, y);
            par[x][y] = pair(-1, -1);
            root = pair(x, y);
        }
        cout << root.first + 1 << ' ' << root.second + 1 << '\n';
    }
}