#include <bits/stdc++.h>
using namespace std;

const int mxN = 25e4;

int a[mxN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, Q;
    cin >> N >> Q;
    for (int i = N - 1; ~i; --i)
        cin >> a[i];

    for (int x, y, ans; Q--;) {
        cin >> x >> y;
        y = N - y;
        ans = a[y] < x ? 0 : (a[y] - x + 1);
        cout << ans + y - (lower_bound(a, a + y, x) - a) << '\n';
    }
    return 0;
}