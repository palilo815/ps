#include <bits/stdc++.h>
using namespace std;

constexpr int MAX = 1e8;

bitset<MAX + 1> sieve;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    uint32_t n;
    cin >> n;
    uint32_t ans = 1;
    for (uint32_t i = 2; i <= n; ++i) {
        if (sieve[i]) {
            continue;
        }
        for (uint64_t x = i; x <= n; x *= i)
            ans *= i;
        for (uint64_t j = uint64_t(i) * i; j <= n; j += i) {
            sieve._Unchecked_set(j);
        }
    }
    cout << ans;
}