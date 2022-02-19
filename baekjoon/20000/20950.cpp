#include <bits/stdc++.h>

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
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;
    vector<array<int, 3>> a(n);
    for (auto& [r, g, b] : a) {
        cin >> r >> g >> b;
    }
    array<int, 3> gom, res {};
    for (auto& x : gom) {
        cin >> x;
    }
    int ans = INT_MAX;
    y_combinator([&](auto self, int mask, int cnt) -> void {
        if (cnt > 1) chmin(ans, abs(gom[0] - res[0] / cnt) + abs(gom[1] - res[1] / cnt) + abs(gom[2] - res[2] / cnt));
        if (cnt == 7) return;
        for (const auto i : views::iota(0, n) | views::filter([&](const auto& i) { return ~mask >> i & 1; })) {
            ranges::transform(res, a[i], res.begin(), plus());
            self(mask | 1 << i, cnt + 1);
            ranges::transform(res, a[i], res.begin(), minus());
        }
    })(0, 0);
    cout << ans;
}
