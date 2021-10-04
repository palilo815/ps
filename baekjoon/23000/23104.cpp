#include <bits/stdc++.h>
using namespace std;

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

    template <typename T>
    modnum pow(T p) const {
        assert(p >= 0);
        modnum res, x = *this;
        res.v = 1;
        for (; p; p >>= 1) {
            if (p & 1) res *= x;
            x *= x;
        }
        return res;
    }
    template <typename T>
    friend modnum pow(const modnum& x, T p) { return x.pow(p); }
    modnum inv() const {
        int x = v, y = MOD;
        int vx = 1, vy = 0;
        while (x) {
            const int k = y / x;
            y %= x;
            vy -= k * vx;
            std::swap(x, y);
            std::swap(vx, vy);
        }
        assert(y == 1);
        if (vy < 0) vy += MOD;
        modnum res;
        res.v = vy;
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
        ++v;
        if (v == MOD) v = 0;
        return *this;
    }
    modnum& operator--() {
        if (v == 0) v = MOD;
        --v;
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

using mint = modnum<int(1e9 + 7)>;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, k;
    cin >> n >> k;
    vector<int> num(k), prev_num(k);
    vector<mint> dp(k, 1), prev_dp(k);
    for (auto& x : num) cin >> x;
    for (int i = 1; i < n; ++i) {
        num.swap(prev_num);
        for (auto& x : num) cin >> x;
        dp.swap(prev_dp);
        mint pref = 0;
        for (int i = 0, j = 0; i < k; ++i) {
            while (j != k && prev_num[j] <= num[i]) {
                pref += prev_dp[j++];
            }
            dp[i] = pref;
        }
    }
    cout << accumulate(dp.begin(), dp.end(), mint(0));
}