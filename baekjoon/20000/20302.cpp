#include <bits/stdc++.h>
using namespace std;

class eratosthenes {
public:
    vector<int> get_primes(int MAX) {
        const int s = round(sqrt(MAX)), r = MAX >> 1;
        vector<int> primes = {2}, sieve(s + 1);
        primes.reserve(MAX / log(MAX) * 1.1);
        vector<pair<int, int>> cp;
        for (int i = 3; i <= s; i += 2) {
            if (!sieve[i]) {
                cp.emplace_back(i, (i * i) >> 1);
                for (int j = i * i; j <= s; j += i << 1) {
                    sieve[j] = 1;
                }
            }
        }
        for (int l = 1; l <= r; l += s) {
            fill(sieve.begin(), sieve.end(), 0);
            for (auto& [p, idx] : cp) {
                for (int i = idx; i < s + l; idx = (i += p)) {
                    sieve[i - l] = 1;
                }
            }
            for (int i = 0, j = min(s, r - l); i < j; ++i) {
                if (!sieve[i]) {
                    primes.emplace_back((l + i) << 1 | 1);
                }
            }
        }
        return primes;
    }
    vector<int> get_factors(int MAX) {
        vector<int> f(MAX), primes;
        primes.reserve(MAX / log(MAX) * 1.1);
        for (int i = 2; i <= MAX; ++i) {
            if (f[i] == 0) {
                f[i] = i;
                primes.emplace_back(i);
            }
            for (const auto& p : primes) {
                if (p > f[i] || i * p > MAX) {
                    break;
                }
                f[i * p] = p;
            }
        }
        return f;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    constexpr int MAX = 1e5;
    const auto f = eratosthenes().get_factors(MAX + 1);
    vector<int> cnt(MAX + 1);
    int n;
    cin >> n;
    char op = '*';
    for (int i = 0, x; i < n; ++i) {
        if (i) {
            cin >> op;
        }
        cin >> x;
        x = abs(x);
        if (x == 0) {
            return cout << "mint chocolate", 0;
        }
        int sign = op == '*' ? 1 : -1;
        while (f[x]) {
            cnt[f[x]] += sign;
            x /= f[x];
        }
    }
    cout << (any_of(cnt.begin(), cnt.end(), [&](const auto& x) { return x < 0; })
                 ? "toothpaste"
                 : "mint chocolate");
}