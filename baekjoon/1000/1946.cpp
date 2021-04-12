#include <bits/stdc++.h>
using namespace std;

void solve() {
    int n;
    cin >> n;

    vector<int> a(n);
    for (int i = 0, x, y; i < n; ++i) {
        cin >> x >> y, --x, --y;
        a[x] = y;
    }

    int ans = 0, mn_y = INT_MAX;
    for (const auto& y : a) {
        if (y > mn_y) continue;
        ++ans;
        mn_y = y;
    }
    cout << ans << '\n';
}
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int T;
    cin >> T;
    while (T--) solve();
}