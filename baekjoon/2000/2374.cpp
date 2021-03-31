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

    vector<int> a(n);
    for (auto& x : a) cin >> x;

    auto ans = y_combinator([&](auto self, int l, int r) -> pair<int64_t, int> {
        auto cnt = 0LL;
        auto mx = *max_element(a.begin() + l, a.begin() + r);

        int prv = l;
        for (int i = l; i < r; ++i) {
            if (a[i] == mx) {
                if (prv != i) {
                    auto res = self(prv, i);
                    cnt += res.first + mx - res.second;
                }
                prv = i + 1;
            }
        }
        if (prv != r) {
            auto res = self(prv, r);
            cnt += res.first + mx - res.second;
        }
        return {cnt, mx};
    })(0, n);

    cout << ans.first;
}