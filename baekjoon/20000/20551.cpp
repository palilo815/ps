#include <bits/stdc++.h>
using namespace std;

const int mxN = 2e5;

int a[mxN + 1];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m;
    cin >> n >> m;

    for (int i = 0; i < n; ++i)
        cin >> a[i];

    sort(a, a + n);
    a[n] = INT_MAX;

    for (int x, i; m--;) {
        cin >> x;
        i = lower_bound(a, a + n, x) - a;
        cout << (a[i] == x ? i : -1) << '\n';
    }
}