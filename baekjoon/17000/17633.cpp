#include <bits/stdc++.h>
using namespace std;

struct miller_rabin {
    using u64 = uint64_t;

    bool is_prime(u64 n) {
        if (n < 2) return false;
        if (n == 2 || n == 3) return true;
        if (n % 6 != 1 && n % 6 != 5) return false;

        const auto& base = n < 4759123141ULL ? base_small : base_large;
        const int s = __builtin_ctzll(n - 1);
        const u64 d = n >> s;

        for (const auto& b : base) {
            if (b >= n) break;
            if (check_composite(n, b, d, s)) return false;
        }
        return true;
    }

protected:
    u64 mul(u64 a, u64 b, u64 m) {
        int64_t ret = a * b - m * u64(1.L / m * a * b);
        return ret + m * (ret < 0) - m * (ret >= int64_t(m));
    }

private:
    const vector<u64> base_small = {2, 7, 61},
                      base_large = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};

    u64 pow(u64 a, u64 p, u64 m) {
        u64 ret = 1;
        for (; p; p >>= 1) {
            if (p & 1) ret = mul(ret, a, m);
            a = mul(a, a, m);
        }
        return ret;
    }
    bool check_composite(u64 n, u64 x, u64 d, int s) {
        x = pow(x, d, n);
        if (x == 1 || x == n - 1) return false;
        while (--s) {
            x = mul(x, x, n);
            if (x == n - 1) return false;
        }
        return true;
    };
};

struct pollard_rho : miller_rabin {
    u64 pollard(u64 n) {
        auto f = [&](u64 x) { return mul(x, x, n) + 1; };
        u64 x = 0, y = 0, prd = 2, i = 1, q;
        for (int t = 30; t++ % 40 || gcd(prd, n) == 1; x = f(x), y = f(f(y))) {
            if (x == y) x = ++i, y = f(x);
            if ((q = mul(prd, x > y ? x - y : y - x, n))) prd = q;
        }
        return gcd(prd, n);
    }
    vector<u64> factorize(u64 n) {
        if (n == 1) return {};
        if (is_prime(n)) return {n};

        const u64 x = pollard(n);
        auto l = factorize(x), r = factorize(n / x);

        decltype(l) ret(l.size() + r.size());
        merge(l.begin(), l.end(), r.begin(), r.end(), ret.begin());
        return ret;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    uint64_t n;
    cin >> n;

    // Legendre's
    while (!(n & 3ull)) n >>= 2;
    if (n % 8 == 7) return cout << 4, 0;

    // Sum of two squares theorem
    pollard_rho pr;
    const auto f = pr.factorize(n);
    for (int i = 0, j; i < int(f.size()); i = j) {
        for (j = i + 1; j < int(f.size()) && f[i] == f[j]; ++j)
            ;
        if (j - i & 1 && (f[i] & 3ull) == 3ull)
            return cout << 3, 0;
    }

    // Perfect square
    const auto sq = uint64_t(sqrt(n));
    cout << (sq * sq == n ? 1 : 2);
}