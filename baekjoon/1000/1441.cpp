#include <bits/stdc++.h>
using namespace std;

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

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, l, r;
    cin >> n >> l >> r, --l;
    // (l,r]

    vector<int> a(n);
    for (auto& x : a) cin >> x;

    cout << r - l - y_combinator([&](auto self, int64_t num, int i, bool in) -> int {
                if (num > r) return 0;

                int ret = r / num - l / num;
                if (!in) ret = -ret;

                for (; i < n; ++i)
                    ret += self(lcm(num, a[i]), i + 1, !in);
                return ret;
            })(1, 0, true);
}