#include <bits/stdc++.h>
using namespace std;

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
    vector<char> block(s);
    for (int l = 1; l <= r; l += s) {
        memset(block.data(), 0, s);
        for (auto& [p, idx] : cp) {
            for (int i = idx; i < s + l; idx = (i += p)) {
                block[i - l] = 1;
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
    auto primes = get_primes(50000);
    vector<int> a;
    for (int i = 0; i < int(primes.size()) - 1; ++i) {
        for (int j = i + 1; j < int(primes.size()); ++j) {
            unsigned r = primes[i] * primes[j];
            if (r > 100001) break;
            a.emplace_back(r);
        }
    }
    sort(a.begin(), a.end());
    int T;
    cin >> T;
    for (int k; T--;) {
        cin >> k;
        cout << *lower_bound(a.begin(), a.end(), k) << '\n';
    }
}