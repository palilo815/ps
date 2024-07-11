#include <bits/stdc++.h>

auto sum_digits(int n) -> int {
    int ret = 0;
    for (; n; n /= 10) {
        ret += n % 10;
    }
    return ret;
}

class primality_test {
    using num = unsigned long long;

public:
    [[nodiscard]] auto is_prime(num n) const -> bool {
        if (n < 2) return false;
        if (n == 2 || n == 3) return true;
        if (n % 6 != 1 && n % 6 != 5) return false;

        const auto s = __builtin_ctzll(n - 1);
        const auto d = n >> s;
        for (auto const b : base_small) {
            if (b >= n) break;
            if (check_composite(n, b, d, s)) {
                return false;
            }
        }
        return true;
    }
    [[nodiscard]] auto factorize(num n) const -> int {
        if (n == 1) return 0;
        if (is_prime(n)) return sum_digits(static_cast<int>(n));

        const auto x = pollard(n);
        auto l = factorize(x), r = factorize(n / x);
        return l + r;
    }

private:
    static constexpr std::array<num, 3> base_small = {2, 7, 61};
    // static constexpr std::array<num, 8> base_large = {2, 325, 9375, 28178, 450775, 9780504, 1795265022, 0};

    [[nodiscard]] auto pow_mod(num a, num p, num m) const -> num {
        num ret = 1;
        for (; p; p >>= 1) {
            if (p & 1) ret = mul_mod(ret, a, m);
            a = mul_mod(a, a, m);
        }
        return ret;
    }
    [[nodiscard]] auto mul_mod(num a, num b, num m) const -> num {
        int64_t ret = a * b - m * num(1.L / m * a * b);
        return ret + m * (ret < 0) - m * (ret >= int64_t(m));
    }
    [[nodiscard]] auto check_composite(num n, num x, num d, int s) const -> bool {
        x = pow_mod(x, d, n);
        if (x == 1 || x == n - 1) return false;
        while (--s) {
            x = mul_mod(x, x, n);
            if (x == n - 1) return false;
        }
        return true;
    };
    [[nodiscard]] auto pollard(num n) const -> num {
        auto f = [&](num x) { return mul_mod(x, x, n) + 1; };
        num x = 0, y = 0, prd = 2, i = 1, q;
        for (int t = 30; t++ % 40 || std::gcd(prd, n) == 1; x = f(x), y = f(f(y))) {
            if (x == y) x = ++i, y = f(x);
            if ((q = mul_mod(prd, x > y ? x - y : y - x, n))) prd = q;
        }
        return std::gcd(prd, n);
    }
};

auto main() -> int {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    primality_test solver;
    for (;;) {
        int n;
        cin >> n;
        if (!n) break;
        for (;;) {
            ++n;
            if (solver.is_prime(n)) continue;
            auto x = sum_digits(n);
            auto y = solver.factorize(n);
            if (x == y) {
                cout << n << '\n';
                break;
            }
        }
    }
}
