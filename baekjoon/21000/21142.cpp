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

    int n, k;
    cin >> n >> k;

    array<array<int, 26>, 26> cnt {};
    for (int t = 0; t < n; ++t) {
        string s;
        cin >> s;
        for (int i = 0; i < k - 1; ++i)
            for (int j = i + 1; j < k; ++j)
                ++cnt[s[i] - 'A'][s[j] - 'A'];
    }

    vector dp(k, -1);
    auto solve = y_combinator([&](auto self, int u) -> int {
        if (~dp[u]) return dp[u];
        dp[u] = 1;
        for (int v = 0; v < k; ++v)
            if (cnt[u][v] == n)
                chmax(dp[u], self(v) + 1);
        return dp[u];
    });

    int ans = 0;
    for (int i = 0; i < k; ++i)
        chmax(ans, solve(i));
    cout << ans;
}