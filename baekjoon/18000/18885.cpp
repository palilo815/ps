#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5;

int mn[mxN], mx[mxN], buf[mxN];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;

    for (int i = 0, l; i < n; ++i) {
        cin >> l;
        for (int j = 0; j < l; ++j)
            cin >> buf[j];
        if (is_sorted(buf, buf + l, greater<int>()))
            mx[i] = buf[0], mn[i] = buf[l - 1];
        else
            mx[i] = 1e9, mn[i] = -1;
    }

    sort(mn, mn + n);

    int64_t ans = 0;
    for (int i = 0; i < n; ++i)
        ans += lower_bound(mn, mn + n, mx[i]) - mn;
    cout << ans;
}