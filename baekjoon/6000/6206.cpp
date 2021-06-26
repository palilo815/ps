#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    constexpr int salt = 31;
    constexpr int64_t p = 998244353, mod = 1e9 + 7;

    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    for (auto& x : a) cin >> x, x += salt;

    auto parametric = [&](auto lo, auto hi) {
        unordered_map<int, int> cnt;
        auto f = [&](auto mid) -> bool {
            int64_t hash_val = a[0], base = 1;
            for (int i = 1; i < mid; ++i) {
                hash_val = (hash_val * p + a[i]) % mod;
                base = base * p % mod;
            }

            cnt.clear();
            cnt[hash_val] = 1;
            for (int i = mid; i < n; ++i) {
                hash_val -= a[i - mid] * base % mod;
                if (hash_val < 0) hash_val += mod;
                hash_val = (hash_val * p + a[i]) % mod;
                if (++cnt[hash_val] >= k) return true;
            }
            return false;
        };

        // last true
        while (lo != hi) {
            auto mid = lo + (hi - lo + 1) / 2;
            f(mid) ? lo = mid : hi = mid - 1;
        }
        return lo;
    };

    cout << parametric(0, n - 1);
}