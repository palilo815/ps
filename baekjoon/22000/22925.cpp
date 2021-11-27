#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (auto& x : a) {
        cin >> x;
    }
    sort(a.begin(), a.end());
    vector dp(n, vector<int64_t>(n));
    vector prv(n, vector<int64_t>(n));
    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            dp[i][j] = 1;
        }
    }
    for (k -= 2; k--;) {
        dp.swap(prv);
        for (auto& x : dp) {
            fill(x.begin(), x.end(), 0);
        }
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                for (int k = j + 1; k < n; ++k) {
                    if (a[i] + a[j] >= a[k]) {
                        dp[j][k] += prv[i][j];
                    }
                }
            }
        }
    }
    cout << accumulate(dp.begin(), dp.end(), 0ll, [&](const auto& sum, const auto& vt) {
        return sum + accumulate(vt.begin(), vt.end(), 0ll);
    });
}