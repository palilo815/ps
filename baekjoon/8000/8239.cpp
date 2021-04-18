#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int64_t m, d;
    int n;
    cin >> m >> d >> n;

    vector<int64_t> a(n);
    for (auto& x : a) cin >> x;

    sort(a.begin(), a.end(), greater<int64_t>());

    int64_t last_taxi;
    if (auto it = upper_bound(a.begin(), a.end(), m - d, greater<int64_t>()); it == a.begin())
        return cout << 0, 0;
    else {
        last_taxi = *prev(it);
        a.erase(prev(it));
    }
    int64_t mid = d - (last_taxi - (m - d)) / 2;

    int64_t pos = 0;
    int ans = 0;
    for (const auto& x : a) {
        if (pos >= mid) break;
        if (x <= d - pos) return cout << 0, 0;
        pos += x - (d - pos);
        ++ans;
    }
    cout << (pos < mid ? 0 : ans + (pos < m));
}