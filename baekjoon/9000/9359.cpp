#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int tt;
    cin >> tt;
    for (int t = 1, n; t <= tt; ++t) {
        int64_t a, b;
        cin >> a >> b >> n, --a;
        int64_t ans = b - a;

        vector<int> f;
        for (int i = 2; i * i <= n; ++i)
            if (n % i == 0) {
                f.emplace_back(i);
                while (n % i == 0) n /= i;
            }
        if (n != 1) f.emplace_back(n);

        const int sz = f.size();
        for (int i = 1; i < 1 << sz; ++i) {
            int64_t x = 1;
            for (int j = 0; j < sz; ++j)
                if (i >> j & 1)
                    x *= f[j];

            int64_t cnt = b / x - a / x;
            ans += __builtin_parity(i) ? -cnt : +cnt;
        }

        cout << "Case #" << t << ": " << ans << '\n';
    }
}