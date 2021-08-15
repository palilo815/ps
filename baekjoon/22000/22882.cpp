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
    constexpr size_t MX_N = 20;
    int n;
    int64_t k;
    cin >> n >> k;
    int a[MX_N][MX_N];
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> a[i][j];
        }
    }
    if (n == 1) return cout << (a[0][0] == k), 0;
    array<vector<int64_t>, MX_N> dp_equal_k0, dp_equal_k1;
    array<vector<int64_t>, MX_N> dp_less_k0, dp_less_k1;
    vector<int> path;
    y_combinator([&](auto self, int r, int c) -> void {
        if (r + c == n - 1) {
            int64_t mmax = LLONG_MIN, rmax = LLONG_MIN;
            int64_t sum = 0, rsum = 0;
            for (int i = n - 1; i--;) {
                rsum += path[i];
                sum = sum + path[i] < path[i] ? path[i] : sum + path[i];
                chmax(mmax, sum);
                chmax(rmax, rsum);
            }
            if (mmax == k) {
                dp_equal_k0[r].emplace_back(rmax);
            } else if (mmax < k) {
                dp_less_k0[r].emplace_back(rmax);
            }
            return;
        }
        path.emplace_back(a[r][c]);
        if (c + 1 != n) self(r, c + 1);
        if (r + 1 != n) self(r + 1, c);
        path.pop_back();
    })(0, 0);
    y_combinator([&](auto self, int r, int c) -> void {
        path.emplace_back(a[r][c]);
        if (r + c == n - 1) {
            int64_t mmax = LLONG_MIN, lmax = LLONG_MIN;
            int64_t sum = 0, lsum = 0;
            for (int i = n; i--;) {
                lsum += path[i];
                sum = sum + path[i] < path[i] ? path[i] : sum + path[i];
                chmax(mmax, sum);
                chmax(lmax, lsum);
            }
            if (mmax == k) {
                dp_equal_k1[r].emplace_back(lmax);
            } else if (mmax < k) {
                dp_less_k1[r].emplace_back(lmax);
            }
            path.pop_back();
            return;
        }
        if (c) self(r, c - 1);
        if (r) self(r - 1, c);
        path.pop_back();
    })(n - 1, n - 1);
    for (auto& vt : dp_equal_k0) sort(vt.begin(), vt.end());
    for (auto& vt : dp_equal_k1) sort(vt.begin(), vt.end());
    for (auto& vt : dp_less_k0) sort(vt.begin(), vt.end());
    for (auto& vt : dp_less_k1) sort(vt.begin(), vt.end());
    int64_t ans = 0;
    for (int i = 0; i < n; ++i) {
        for (auto& rsum : dp_equal_k0[i]) {
            ans += upper_bound(dp_equal_k1[i].begin(), dp_equal_k1[i].end(), k - rsum) - dp_equal_k1[i].begin();
            ans += upper_bound(dp_less_k1[i].begin(), dp_less_k1[i].end(), k - rsum) - dp_less_k1[i].begin();
        }
        for (auto& rsum : dp_less_k0[i]) {
            ans += upper_bound(dp_equal_k1[i].begin(), dp_equal_k1[i].end(), k - rsum) - dp_equal_k1[i].begin();
            auto range = equal_range(dp_less_k1[i].begin(), dp_less_k1[i].end(), k - rsum);
            ans += range.second - range.first;
        }
    }
    cout << ans;
}