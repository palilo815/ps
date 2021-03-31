#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, k;
    cin >> n >> k;

    vector<int64_t> a(k);
    for (auto& x : a) cin >> x;

    int ans = 0;
    for (int i = 1; i < 1 << k; ++i) {
        int64_t num = 1;
        for (int j = 0; j < k; ++j)
            if (i >> j & 1) {
                num = lcm(num, a[j]);
                if (num > n) break;
            }

        int cnt = n / num;
        ans += __builtin_parity(i) ? cnt : -cnt;
    }
    cout << ans;
}