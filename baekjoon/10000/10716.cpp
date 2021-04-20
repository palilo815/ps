#include <bits/stdc++.h>
using namespace std;

constexpr int INF = 7e8;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;

    vector<int> a(n - m), base(n), ord(n);
    for (int i = 0, pos; i < m; ++i) {
        cin >> ord[i] >> pos;
        base[n - pos] = ord[i];
    }
    for (auto& x : a) cin >> x;

    copy(a.begin(), a.end(), ord.begin() + m);
    sort(ord.begin(), ord.end());
    ord.erase(unique(ord.begin(), ord.end()), ord.end());

    vector<int> psum(ord.size() + 1);
    for (auto& x : a)
        ++psum[lower_bound(ord.begin(), ord.end(), x) - ord.begin() + 1];
    for (int i = 1; i < int(psum.size()); ++i)
        psum[i] += psum[i - 1];

    vector<int> dp(n + (n >> 1));
    fill(dp.begin() + (n >> 1), dp.end(), 1);

    // children of i = { 3i + 1, 3i + 2, 3i + 3 }
    // leaf nodes = [n >> 1, n + (n >> 1))
    auto need = [&](int want) {
        for (int i = 0; i < n; ++i)
            if (base[i])
                dp[i + (n >> 1)] = base[i] < want ? INF : 0;

        for (int i = (n >> 1); i--;) {
            dp[i] = dp[3 * i + 1] + dp[3 * i + 2] + dp[3 * i + 3] -
                    max({dp[3 * i + 1], dp[3 * i + 2], dp[3 * i + 3]});
            if (dp[i] >= INF) dp[i] = INF;
        }
        return dp[0];
    };

    int lo = 0, hi = ord.size() - 1;
    while (lo != hi) {
        int mid = (lo + hi + 1) >> 1;
        need(ord[mid]) <= n - m - psum[mid] ? lo = mid : hi = mid - 1;
    }
    cout << ord[lo];
}