#include <bits/stdc++.h>
using namespace std;

struct miller_rabin {
    using u64 = uint64_t;
    using u128 = __uint128_t;

    bool is_prime(u64 n) {
        if (n < 2) return false;
        if (n == 2 || n == 3) return true;
        if (n % 6 != 1 && n % 6 != 5) return false;

        const auto& base = n > 4759123141ULL ? base_large : base_small;
        const int s = __builtin_ctzll(n - 1);
        const u64 d = n >> s;

        for (const auto& b : base) {
            if (b >= n) break;
            if (not_prime(b, s, d, n)) return false;
        }
        return true;
    }

private:
    const vector<u64> base_small = {2, 7, 61},
                      base_large = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};

    u128 pow(u128 a, u64 p, u64 m) {
        u128 r = 1;
        for (; p; p >>= 1) {
            if (p & 1) r = r * a % m;
            a = a * a % m;
        }
        return r;
    }
    bool not_prime(u64 a, int s, u64 d, u64 n) {
        u128 x = pow(a, d, n);
        if (x == 1) return false;
        for (int r = 0; r < s; ++r) {
            if (x == n - 1) return false;
            x = x * x % n;
        }
        return true;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;

    miller_rabin mr;

    int ans = 0;
    for (uint64_t area; n--;) {
        cin >> area;
        if (mr.is_prime(area << 1 | 1)) ++ans;
    }
    cout << ans;
}