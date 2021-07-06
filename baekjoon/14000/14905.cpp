#include <bits/stdc++.h>
using namespace std;

template <int MAX>
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

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    const auto primes = get_primes<int(1e8 + 1)>();
    for (int n; cin >> n;) {
        if (n < 8) {
            cout << "Impossible.\n";
            continue;
        }
        cout << 2 << ' ' << (2 + (n & 1)) << ' ';
        n -= 4 + (n & 1);
        for (int st = 0, ed = primes.size();; ++st) {
            while (primes[st] + primes[ed - 1] > n) {
                --ed;
            }
            if (primes[st] + primes[ed - 1] == n) {
                cout << primes[st] << ' ' << primes[ed - 1] << '\n';
                break;
            }
        }
    }
}