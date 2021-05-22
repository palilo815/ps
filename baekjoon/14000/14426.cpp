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

    vector<string> a(n);
    for (auto& x : a) cin >> x;

    sort(a.begin(), a.end());

    int ans = 0;
    for (string k; m--;) {
        cin >> k;
        auto it = lower_bound(a.begin(), a.end(), k);
        ans += it != a.end() && mismatch(it->begin(), it->end(), k.begin()).second == k.end();
    }
    cout << ans;
}