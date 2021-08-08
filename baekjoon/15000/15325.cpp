#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef palilo
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    int64_t k;
    cin >> n >> k;
    const int sz_l = n / 2, sz_r = n - sz_l;
    vector<pair<int, int>> l(sz_l), r(sz_r);
    for (auto& [h, g] : l) cin >> h >> g;
    for (auto& [h, g] : r) cin >> h >> g;
    vector<vector<int64_t>> dp_l(sz_l), dp_r(sz_r);
    for (int i = 0; i < sz_l; ++i) {
        dp_l[i].emplace_back(l[i].second);
        for (int j = 0; j < i; ++j) {
            if (l[j].first <= l[i].first) {
                transform(dp_l[j].begin(), dp_l[j].end(), back_inserter(dp_l[i]), [&](const auto& x) {
                    return x + l[i].second;
                });
            }
        }
    }
    for (int i = sz_r; i--;) {
        dp_r[i].emplace_back(r[i].second);
        for (int j = i + 1; j < sz_r; ++j) {
            if (r[i].first <= r[j].first) {
                transform(dp_r[j].begin(), dp_r[j].end(), back_inserter(dp_r[i]), [&](const auto& x) {
                    return x + r[i].second;
                });
            }
        }
    }
    for (auto& dp : dp_l) sort(dp.begin(), dp.end());
    for (auto& dp : dp_r) sort(dp.begin(), dp.end());
    auto f = [&](const int64_t& sum, const vector<int64_t>& dp) {
        return sum + (dp.end() - lower_bound(dp.begin(), dp.end(), k));
    };
    int64_t ans = accumulate(dp_l.begin(), dp_l.end(), accumulate(dp_r.begin(), dp_r.end(), int64_t(0), f), f);
    for (int i = 0; i < sz_l; ++i) {
        for (int j = 0; j < sz_r; ++j) {
            if (l[i].first > r[j].first) continue;
            auto it = lower_bound(dp_l[i].begin(), dp_l[i].end(), k - dp_r[j].back());
            for (auto jt = dp_r[j].end() - 1; it != dp_l[i].end(); ++it) {
                while (jt != dp_r[j].begin() && *it + *prev(jt) >= k) --jt;
                ans += dp_r[j].end() - jt;
            }
        }
    }
    cout << ans;
}