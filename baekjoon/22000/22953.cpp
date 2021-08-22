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
    int n, k, c;
    cin >> n >> k >> c;
    vector<int> a(n);
    for (auto& x : a) {
        cin >> x;
    }
    chmin(c, accumulate(a.begin(), a.end(), 0) - n);
    int64_t ans = LLONG_MAX;
    auto parametric = [&](int64_t lo, int64_t hi) -> int64_t {
        auto f = [&](int64_t mid) -> bool {
            const auto food = accumulate(a.begin(), a.end(), 0ll, [&](const auto& sum, const auto& x) {
                return sum + mid / x;
            });
            return food >= k;
        };
        // first true
        while (lo != hi) {
            auto mid = lo + (hi - lo) / 2;
            f(mid) ? hi = mid : lo = mid + 1;
        }
        return lo;
    };
    y_combinator([&](auto self, int cnt) -> void {
        if (cnt == 0) {
            chmin(ans, parametric(1, k * int64_t(1000000)));
            return;
        }
        for (auto& x : a) {
            if (x == 1) continue;
            --x;
            self(cnt - 1);
            ++x;
        }
    })(c);
    cout << ans;
}