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
    int n;
    cin >> n;
    vector<int> a(n);
    for (auto& x : a) {
        cin >> x;
    }
    sort(a.begin(), a.end());
    const auto sum = accumulate(a.begin(), a.end(), 0);
    vector<int64_t> dp(sum + 1);
    dp[0] = 1;
    for (int i = 0, j; i < n; i = j) {
        for (j = i + 1; j < n && a[i] == a[j]; ++j) {
            ;
        }
        for (int s = sum; ~s; --s) {
            int64_t tmp = 0;
            for (int cnt = 1; cnt <= j - i && s - cnt * a[i] >= 0; ++cnt) {
                tmp += dp[s - cnt * a[i]];
            }
            dp[s] += tmp;
        }
    }
    auto primes = eratosthenes<500001>().get_primes();
    primes.erase(upper_bound(primes.begin(), primes.end(), sum), primes.end());
    cout << accumulate(primes.begin(), primes.end(), 0ll, [&](const auto& sum, const auto& p) {
        return sum + dp[p];
    });
}