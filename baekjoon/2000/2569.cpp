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

    vector<pair<int, int>> a(n);
    for (int i = 0; i < n; ++i)
        cin >> a[i].first, a[i].second = i;

    sort(a.begin(), a.end(), [&](auto& a, auto& b) {
        return a.first < b.first;
    });

    int ans = 0;
    vector<bool> done(n);
    for (int i = 0; i < n; ++i) {
        if (done[i]) continue;

        int cnt = 0;
        for (int j = i; !done[j]; j = a[j].second) {
            ans += a[j].first;
            cnt += 1;
            done[j] = true;
        }
        ans += min((cnt - 2) * a[i].first, a[i].first + (cnt + 1) * a[0].first);
    }
    cout << ans;
}