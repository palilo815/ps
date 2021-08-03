#include <bits/stdc++.h>
using namespace std;

/**
 * @link https://github.com/ecnerwala/cp-book/blob/master/src/modnum.hpp
 */
namespace ecnerwala {
template <typename T>
T mod_inv_in_range(T a, T m) {
    T x = a, y = m;
    T vx = 1, vy = 0;
    while (x) {
        T k = y / x;
        y %= x;
        vy -= k * vx;
        std::swap(x, y);
        std::swap(vx, vy);
    }
    assert(y == 1);
    return vy < 0 ? m + vy : vy;
}

template <typename T>
T mod_inv(T a, T m) {
    a %= m;
    a = a < 0 ? a + m : a;
    return mod_inv_in_range(a, m);
}

template <int MOD_>
struct modnum {
    static constexpr int MOD = MOD_;
    static_assert(MOD_ > 0, "MOD must be positive");

private:
    using ll = long long;

    int v;

public:
    modnum() : v(0) {}
    modnum(ll v_) : v(int(v_ % MOD)) {
        if (v < 0) v += MOD;
    }
    explicit operator int() const { return v; }
    friend std::ostream& operator<<(std::ostream& out, const modnum& n) { return out << int(n); }
    friend std::istream& operator>>(std::istream& in, modnum& n) {
        ll v_;
        in >> v_;
        n = modnum(v_);
        return in;
    }

    friend bool operator==(const modnum& a, const modnum& b) { return a.v == b.v; }
    friend bool operator!=(const modnum& a, const modnum& b) { return a.v != b.v; }

    modnum inv() const {
        modnum res;
        res.v = mod_inv_in_range(v, MOD);
        return res;
    }
    friend modnum inv(const modnum& m) { return m.inv(); }
    modnum neg() const {
        modnum res;
        res.v = v ? MOD - v : 0;
        return res;
    }
    friend modnum neg(const modnum& m) { return m.neg(); }

    modnum operator-() const {
        return neg();
    }
    modnum operator+() const {
        return modnum(*this);
    }

    modnum& operator++() {
        v++;
        if (v == MOD) v = 0;
        return *this;
    }
    modnum& operator--() {
        if (v == 0) v = MOD;
        v--;
        return *this;
    }
    modnum& operator+=(const modnum& o) {
        v -= MOD - o.v;
        v = (v < 0) ? v + MOD : v;
        return *this;
    }
    modnum& operator-=(const modnum& o) {
        v -= o.v;
        v = (v < 0) ? v + MOD : v;
        return *this;
    }
    modnum& operator*=(const modnum& o) {
        v = int(ll(v) * ll(o.v) % MOD);
        return *this;
    }
    modnum& operator/=(const modnum& o) {
        return *this *= o.inv();
    }

    friend modnum operator++(modnum& a, int) {
        modnum r = a;
        ++a;
        return r;
    }
    friend modnum operator--(modnum& a, int) {
        modnum r = a;
        --a;
        return r;
    }
    friend modnum operator+(const modnum& a, const modnum& b) { return modnum(a) += b; }
    friend modnum operator-(const modnum& a, const modnum& b) { return modnum(a) -= b; }
    friend modnum operator*(const modnum& a, const modnum& b) { return modnum(a) *= b; }
    friend modnum operator/(const modnum& a, const modnum& b) { return modnum(a) /= b; }
};
}; // namespace ecnerwala

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    using mint = ecnerwala::modnum<int(1e9 + 7)>;
    constexpr int MX_K = 447; // sum[1...447] > 1e5
    array<vector<mint>, MX_K> dp;
    dp[0] = {0, 1};
    for (int i = 1; i < MX_K; ++i) {
        dp[i].resize(dp[i - 1].size() + i);
        memcpy(dp[i].data() + i, dp[i - 1].data(), sizeof(mint) * dp[i - 1].size());
        transform(dp[i - 1].begin(), dp[i - 1].end(), dp[i].begin(), dp[i].begin(), plus<mint>());
    }
    for (auto& row : dp) {
        partial_sum(row.begin(), row.end(), row.begin());
    }
    int T;
    cin >> T;
    for (int a, b; T--;) {
        cin >> a >> b;
        mint ans;
        for (int k = 1, s = 0; k < MX_K; ++k) {
            s += k;
            const auto rt = min(a + 1, int(dp[k].size()) - 1);
            const auto lt = max(s - b, 0);
            if (lt >= rt) break;
            ans += dp[k][rt] - dp[k][lt];
        }
        cout << ans << '\n';
    }
}