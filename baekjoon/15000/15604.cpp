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
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    // 2 3 5 7 11 13 17 19 = 9,699,690
    // # of primes = 664579;
    constexpr int MX_FACTOR = 8;
    constexpr int MX_X = 1e7 + 1;
    constexpr int NUM_PRIMES = 664579;

    int n;
    cin >> n;

    vector<int> a(n);
    for (auto& x : a) cin >> x;

    vector<array<int, MX_FACTOR>> factors(n, array<int, MX_FACTOR> {-1, -1, -1, -1, -1, -1, -1, -1});
    {
        vector<int> factor(MX_X, 1), primes;
        primes.reserve(NUM_PRIMES);

        for (int64_t i = 2; i < MX_X; ++i) {
            if (factor[i] != 1) continue;
            factor[i] = i;
            primes.emplace_back(i);
            for (int64_t j = i * i; j < MX_X; j += i)
                factor[j] = i;
        }

        assert(primes.size() == NUM_PRIMES);

        for (int i = 0; i < n; ++i) {
            for (int prv_f = 0, num = 0, x = a[i]; x != 1; x /= factor[x])
                if (prv_f != factor[x]) {
                    factors[i][num++] = lower_bound(primes.begin(), primes.end(), factor[x]) - primes.begin();
                    prv_f = factor[x];
                }
        }
    }

    vector<int> par(n);
    vector<int> cnt(NUM_PRIMES);

    y_combinator([&](auto self, int st, int ed, int p, bool recorded) -> void {
        if (st == ed) return;
        if (st + 1 == ed) {
            par[st] = p;
            if (recorded) {
                for (const auto& f : factors[st]) {
                    if (f == -1) break;
                    --cnt[f];
                }
            }
            return;
        }

        if (!recorded) {
            for (int i = st; i < ed; ++i) {
                for (const auto& f : factors[i]) {
                    if (f == -1) break;
                    ++cnt[f];
                }
            }
        }

        int root = -1;
        for (int i = st, j = ed - 1; i <= j; ++i, --j) {
            bool is_root = true;
            for (const auto& f : factors[i]) {
                if (f == -1) break;
                if (cnt[f] != 1) {
                    is_root = false;
                    break;
                }
            }
            if (is_root) {
                root = i;
                break;
            }

            if (i == j) break;

            is_root = true;
            for (const auto& f : factors[j]) {
                if (f == -1) break;
                if (cnt[f] != 1) {
                    is_root = false;
                    break;
                }
            }
            if (is_root) {
                root = j;
                break;
            }
        }

        if (root == -1) {
            cout << "impossible";
            exit(0);
        }
        par[root] = p;

        if (root - st < ed - root) {
            // clear leftside
            for (int i = st; i <= root; ++i)
                for (const auto& f : factors[i]) {
                    if (f == -1) break;
                    --cnt[f];
                }

            self(root + 1, ed, root, true);
            self(st, root, root, false);
        } else {
            // clear rightside
            for (int i = root; i < ed; ++i)
                for (const auto& f : factors[i]) {
                    if (f == -1) break;
                    --cnt[f];
                }

            self(st, root, root, true);
            self(root + 1, ed, root, false);
        }
    })(0, n, -1, false);

    for (const auto& x : par)
        cout << x + 1 << ' ';
}