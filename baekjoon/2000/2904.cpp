#include <bits/stdc++.h>
using namespace std;

template <int MAX>
class eratosthenes {
public:
    vector<int> get_primes() {
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
        array<bool, s> block;
        for (int l = 1; l <= r; l += s) {
            block.fill(false);
            for (auto& [p, idx] : cp) {
                for (int i = idx; i < s + l; idx = (i += p)) {
                    block[i - l] = true;
                }
            }
            for (int i = 0, j = min(s, r - l); i < j; ++i) {
                if (!block[i]) {
                    primes.emplace_back((l + i) << 1 | 1);
                }
            }
        }
        return primes;
    }
};

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    constexpr int MAX = 1e6;
    const auto primes = eratosthenes<MAX + 1>().get_primes();
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) {
        cin >> x;
    }
    int ans = 1, mov = 0;
    vector<int> cnt(n);
    for (const auto& p : primes) {
        fill(cnt.begin(), cnt.end(), 0);
        for (int i = 0; i < n; ++i) {
            while (a[i] % p == 0) {
                ++cnt[i], a[i] /= p;
            }
        }
        auto x = accumulate(cnt.begin(), cnt.end(), 0) / n;
        for (int i = 0; i < x; ++i) {
            ans *= p;
        }
        for (int i = 0; i < n; ++i) {
            mov += max(0, x - cnt[i]);
        }
    }
    cout << ans << ' ' << mov;
}