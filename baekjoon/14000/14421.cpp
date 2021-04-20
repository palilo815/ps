#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;

    vector<vector<int>> h(n, vector<int>(m));
    for (auto& v : h)
        for (auto& x : v)
            cin >> x;

    int mn_h = INT_MAX, mx_h = INT_MIN;
    for (const auto& v : h) {
        auto p = minmax_element(v.begin(), v.end());
        mn_h = min(mn_h, *p.first);
        mx_h = max(mx_h, *p.second);
    }

    auto ok = [&](int lim) {
        int64_t pivot = m;
        for (const auto& v : h) {
            pivot = find_if(v.begin(), v.begin() + pivot, [&](auto& x) { return x > mn_h + lim; }) - v.begin();
            if (any_of(v.begin() + pivot, v.end(), [&](auto& x) { return x < mx_h - lim; }))
                return false;
        }
        return true;
    };

    int ans = mx_h - mn_h;
    for (int t = 0; t < 4; ++t) {
        if (t & 1)
            for (auto& v : h)
                reverse(v.begin(), v.end());
        else if (t == 2)
            reverse(h.begin(), h.end());

        int lo = 0, hi = ans;
        while (lo != hi) {
            int mid = (lo + hi) >> 1;
            ok(mid) ? hi = mid : lo = mid + 1;
        }
        ans = min(ans, lo);
    }
    cout << ans;
}