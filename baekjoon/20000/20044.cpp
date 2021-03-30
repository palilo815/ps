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

    vector<int> a(n << 1);
    for (auto& x : a) cin >> x;

    sort(a.begin(), a.end());

    int ans = INT_MAX;
    for (int i = 0; i < n; ++i)
        ans = min(ans, a[i] + a[n + n - i - 1]);
    cout << ans;
}