#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, q;
    cin >> n >> q;
    vector<pair<int, int>> a(n);
    for (auto& [x, y] : a) {
        cin >> x >> y;
    }
    sort(a.begin(), a.end(), [&](const auto& lhs, const auto& rhs) {
        return lhs.second < rhs.second;
    });
    vector<int64_t> pref_sum(n + 1);
    vector<int> pref_cnt(n + 1);
    for (int i = 0; i < n; ++i) {
        pref_sum[i + 1] = pref_sum[i] + a[i].first * int64_t(a[i].second);
        pref_cnt[i + 1] += pref_cnt[i] + a[i].first;
    }
    for (int64_t x; q--;) {
        cin >> x;
        auto it = lower_bound(a.begin(), a.end(), x, [&](const auto& elem, const auto& x) {
            return elem.second < x;
        }) - a.begin();
        int64_t ans = 0;
        ans += x * pref_cnt[it] - pref_sum[it];
        ans += (pref_sum[n] - pref_sum[it]) - x * (pref_cnt[n] - pref_cnt[it]);
        cout << ans << '\n';
    }
}