#include <bits/stdc++.h>
using namespace std;

const int mxN = 5e5;

int a[mxN], b[mxN], mn[mxN], mx[mxN];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;

    for (int i = 0; i < n; ++i)
        cin >> a[i] >> b[i];

    for (int i = 0; i < n; ++i)
        mn[i] = a[i] - b[i], mx[i] = a[i] + b[i];

    sort(mn, mn + n);
    sort(mx, mx + n);

    for (int i = 0; i < n; ++i)
        cout << lower_bound(mx, mx + n, a[i] - b[i]) - mx + 1 << ' ' << upper_bound(mn, mn + n, a[i] + b[i]) - mn << '\n';
}