#include <bits/stdc++.h>
using namespace std;

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifdef home
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, k;
    cin >> n >> k;

    vector<int> a(n);
    for (auto& x : a) cin >> x;

    sort(a.begin(), a.end());

    vector<int> l(n), r(n);
    for (int i = 0, j = 0; i < n; ++i) {
        while (j < n && a[j] - a[i] <= k) ++j;
        l[i] = j - i;
    }
    for (int i = n - 1, j = n; j--;) {
        while (~i && a[j] - a[i] <= k) --i;
        r[j] = j - i;
    }

    for (int i = n - 2; i >= 0; --i)
        l[i] = max(l[i], l[i + 1]);
    for (int i = 1; i < n; ++i)
        r[i] = max(r[i], r[i - 1]);

    int ans = 0;
    for (int i = 0; i < n - 1; ++i)
        ans = max(ans, r[i] + l[i + 1]);
    cout << ans;
}