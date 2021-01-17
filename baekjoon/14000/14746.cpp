#include <bits/stdc++.h>
using namespace std;

const int mxN = 5e5;

int a[mxN], b[mxN + 1];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m, c1, c2;
    cin >> n >> m >> c1 >> c2;

    for (int i = 0; i < n; ++i)
        cin >> a[i];
    for (int i = 0; i < m; ++i)
        cin >> b[i];

    sort(a, a + n);
    sort(b, b + m);
    b[m] = INT_MAX;

    int ans = INT_MAX, cnt = 0;
    for (int i = 0, j = 0; i < n;) {
        // b[m] is sentinel
        int d = abs(a[i] - b[j]);
        if (d < ans)
            ans = d, cnt = 1;
        else if (d == ans)
            ++cnt;
        a[i] < b[j] ? ++i : ++j;
    }
    cout << ans + abs(c1 - c2) << ' ' << cnt;
}