#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    constexpr int MX_N = 12;
    constexpr int64_t mod = 1e8;

    array<int64_t, 1 << MX_N> dp, prv;
    dp.fill(0);
    dp[0] = 1;

    int n, m;
    cin >> n >> m;

    vector<int> invalid(n);
    for (auto& x : invalid) {
        for (int i = 0, c; i < m; ++i) {
            x <<= 1;
            cin >> c;
            x |= !c;
        }
    }

    for (int i = 0; i < n; ++i) {
        dp.swap(prv);
        dp.fill(0);
        for (int mask = 0; mask < 1 << m; ++mask) {
            if (mask & invalid[i] || mask & mask << 1) continue;
            const int prv_full = ~mask & ((1 << m) - 1);
            for (int prv_mask = prv_full;; --prv_mask &= prv_full) {
                dp[mask] += prv[prv_mask];
                dp[mask] %= mod;
                if (!prv_mask) break;
            }
        }
    }
    cout << accumulate(dp.begin(), dp.end(), 0ll) % mod;
}