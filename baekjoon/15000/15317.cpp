#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5;

int a[mxN], b[mxN];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m, x;
    cin >> n >> m >> x;

    for (int i = 0; i < n; ++i)
        cin >> a[i];
    for (int i = 0; i < m; ++i)
        cin >> b[i];

    sort(a, a + n);
    sort(b, b + m, greater<int>());

    auto valid = [&](int m) {
        int money = x;
        for (int i = 0; i < m; ++i)
            if (a[i] > b[m - 1 - i] && (money -= a[i] - b[m - 1 - i]) < 0)
                return false;
        return true;
    };

    int lo = 0, hi = min(n, m);
    while (lo != hi) {
        int m = (lo + hi + 1) >> 1;
        valid(m) ? lo = m : hi = m - 1;
    }
    cout << lo;
}