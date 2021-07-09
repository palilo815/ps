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
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) {
        cin >> x;
    }
    const auto res = y_combinator([&](auto self, int l, int r) -> pair<int, int> {
        if (l + 1 == r) {
            return {a[l], a[l]};
        }
        const int m = (l + r) >> 1;
        const auto [lgcd, lsum] = self(l, m);
        const auto [rgcd, rsum] = self(m, r);
        const int g = gcd(lgcd, rgcd);
        return {g, max(lgcd + rsum, rgcd + lsum)};
    })(0, n);
    cout << res.second;
}