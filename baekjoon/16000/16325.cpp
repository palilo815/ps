#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    constexpr int64_t mod = 1e9 + 7;

    auto pow = [&](int64_t x, int p) -> int64_t {
        int64_t r = 1;
        while (p) {
            if (p & 1) r = r * x % mod;
            x = x * x % mod;
            p >>= 1;
        }
        return r;
    };

    int n, k;
    cin >> n >> k;

    vector<int> inv(k + 1);
    inv[1] = 1;
    for (int i = 2; i <= k; ++i)
        inv[i] = (mod - mod / i * inv[mod % i] % mod) % mod;

    int64_t ans = 0, com = 1;
    for (int i = 1; i <= k; ++i) {
        com = com * (k - i + 1) % mod * inv[i] % mod;
        ans += ((k - i) & 1 ? -1 : 1) * (com * i % mod * pow(i - 1, n - 1) % mod) + mod;
        ans %= mod;
    }
    cout << ans;
}