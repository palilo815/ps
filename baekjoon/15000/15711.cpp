#include <bits/stdc++.h>
using namespace std;

class primality_test {
    using num = unsigned long long;
    const vector<num> base_small = {2, 7, 61},
                      base_large = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};

public:
    bool is_prime(num n) const {
        if (n < 2) return false;
        if (n == 2 || n == 3) return true;
        if (n % 6 != 1 && n % 6 != 5) return false;

        const auto& base = n < 4759123141ULL ? base_small : base_large;
        const int s = __builtin_ctzll(n - 1);
        const num d = n >> s;

        for (const auto& b : base) {
            if (b >= n) break;
            if (check_composite(n, b, d, s)) return false;
        }
        return true;
    }
    vector<num> factorize(num n) const {
        if (n == 1) return {};
        if (is_prime(n)) return {n};

        const num x = pollard(n);
        auto l = factorize(x), r = factorize(n / x);

        decltype(l) ret(l.size() + r.size());
        merge(l.begin(), l.end(), r.begin(), r.end(), ret.begin());
        return ret;
    }

private:
    num pow_mod(num a, num p, num m) const {
        num ret = 1;
        for (; p; p >>= 1) {
            if (p & 1) ret = mul_mod(ret, a, m);
            a = mul_mod(a, a, m);
        }
        return ret;
    }
    num mul_mod(num a, num b, num m) const {
        int64_t ret = a * b - m * num(1.L / m * a * b);
        return ret + m * (ret < 0) - m * (ret >= int64_t(m));
    }
    bool check_composite(num n, num x, num d, int s) const {
        x = pow_mod(x, d, n);
        if (x == 1 || x == n - 1) return false;
        while (--s) {
            x = mul_mod(x, x, n);
            if (x == n - 1) return false;
        }
        return true;
    };
    num pollard(num n) const {
        auto f = [&](num x) { return mul_mod(x, x, n) + 1; };
        num x = 0, y = 0, prd = 2, i = 1, q;
        for (int t = 30; t++ % 40 || gcd(prd, n) == 1; x = f(x), y = f(f(y))) {
            if (x == y) x = ++i, y = f(x);
            if ((q = mul_mod(prd, x > y ? x - y : y - x, n))) prd = q;
        }
        return gcd(prd, n);
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    primality_test solver;
    int t;
    cin >> t;
    for (int64_t x, y; t--;) {
        cin >> x >> y;
        x += y - 2;
        bool yes = x & 1 ? solver.is_prime(x) : !!x;
        cout << (yes ? "YES\n" : "NO\n");
    }
}