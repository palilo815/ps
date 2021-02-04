#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;

    vector<pair<int, int>> a(n + 1);
    for (int i = 0; i < n; ++i)
        cin >> a[i].first >> a[i].second;
    a[n].first = INT_MAX; // sentinel

    sort(a.begin(), a.end(), [&](auto& a, auto& b) {
        return a.first < b.first;
    });

    int ans = 0;
    for (int i = 0, j, r; i < n; i = j) {
        for (j = i + 1, r = a[i].second; a[j].first <= r; ++j)
            r = max(r, a[j].second);
        ans += r - a[i].first;
    }
    cout << ans;
}