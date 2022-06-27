#include <bits/stdc++.h>

using f128 = long double;

auto main() -> int {
    using namespace std;
    cin.tie(nullptr)->sync_with_stdio(false);
    int t, k;
    cin >> t >> k, --t;
    auto init = [](int n, int r) {
        f128 res = n & 1 ? 0.5 : 1.0;
        for (int i = 0; i < r; ++i) {
            res = res * (n - i) / (i + 1) / 4;
        }
        return res;
    };
    auto r = init(t, t / 2);
    vector<f128> p(t + 1);
    int i = t >> 1, j = (t + 1) >> 1;
    p[i--] = p[j++] = r;
    for (int x = i + 1, y = j; x; --i, ++j, --x, ++y) {
        r = r * x / y;
        p[i] = p[j] = r;
    }
    vector<f128> pref_p(t + 2);
    vector<f128> suff_expected(t + 2);
    for (int i = 0; i < t + 1; ++i) {
        pref_p[i + 1] = p[i] + pref_p[i];
    }
    for (int i = t + 1; i--;) {
        suff_expected[i] += i * p[i] + suff_expected[i + 1];
    }
    auto mat_mul = [&](const array<array<f128, 2>, 2>& x, const array<array<f128, 2>, 2>& y) {
        array<array<f128, 2>, 2> ret;
        ret[0][0] = x[0][0] * y[0][0] + x[0][1] * y[1][0];
        ret[0][1] = x[0][0] * y[0][1] + x[0][1] * y[1][1];
        ret[1][0] = x[1][0] * y[0][0] + x[1][1] * y[1][0];
        ret[1][1] = x[1][0] * y[0][1] + x[1][1] * y[1][1];
        return ret;
    };
    auto mat_pow = [&](f128 a, f128 b, int p) {
        array<array<f128, 2>, 2> mat = {{{a, b}, {0.0, 1.0}}}, res = {{{1, 0}, {0, 1}}};
        for (; p; p >>= 1) {
            if (p & 1) res = mat_mul(res, mat);
            mat = mat_mul(mat, mat);
        }
        return res;
    };
    auto first_true = [&](int lo, int hi, f128 r) {
        size_t now = ceil(r);
        while (lo != hi) {
            auto mid = lo + (hi - lo) / 2;
            auto mat = mat_pow(pref_p[now], suff_expected[now], mid);
            auto res = mat[0][0] * r + mat[0][1];
            ceil(res) != now ? hi = mid : lo = mid + 1;
        }
        return lo;
    };
    for (r = t / 2.0, --k; k;) {
        int p = first_true(0, k, r);
        k -= p;
        size_t i = ceil(r);
        auto mat = mat_pow(pref_p[i], suff_expected[i], p);
        r = mat[0][0] * r + mat[0][1];
    }
    cout << fixed << setprecision(9) << r + 1;
}
