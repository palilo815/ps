#include <bits/stdc++.h>
using namespace std;

/**
 * @link https://github.com/ecnerwala/cp-book/blob/master/src/modnum.hpp
 */
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

template <int MAX>
class eratosthenes {
public:
    bitset<MAX> is_prime;
    vector<int> get_primes() {
        const int s = round(sqrt(MAX)), r = MAX >> 1;

        vector<int> primes = {2}, sieve(s + 1);
        primes.reserve(MAX / log(MAX) * 1.1);

        vector<pair<int, int>> cp;
        for (int i = 3; i <= s; i += 2)
            if (!sieve[i]) {
                cp.emplace_back(i, (i * i) >> 1);
                for (int j = i * i; j <= s; j += i << 1)
                    sieve[j] = 1;
            }

        for (int l = 1; l <= r; l += s) {
            array<bool, s> block {};
            for (auto& [p, idx] : cp)
                for (int i = idx; i < s + l; idx = (i += p))
                    block[i - l] = 1;

            for (int i = 0, j = min(s, r - l); i < j; ++i)
                if (!block[i])
                    primes.emplace_back((l + i) << 1 | 1);
        }

        for (const auto& i : primes)
            is_prime[i] = true;
        return primes;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    using mint = modnum<int(1e9 + 7)>;
    constexpr int MX_N = 1e7;
    const auto primes = eratosthenes<MX_N + 1>().get_primes();
TOP:;
    int n;
    cin >> n;
    if (!n) {
        return 0;
    }
    mint ans = 1;
    for (const auto& p : primes) {
        if (p > n) {
            break;
        }
        int cnt = 0;
        for (int64_t x = p; x <= n; x *= p) {
            cnt += n / x;
        }
        cnt -= cnt & 1;
        for (mint x = p; cnt; cnt >>= 1) {
            if (cnt & 1) {
                ans *= x;
            }
            x *= x;
        }
    }
    cout << ans << '\n';
    goto TOP;
}