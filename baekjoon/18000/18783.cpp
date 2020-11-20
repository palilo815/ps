#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5;

int a[mxN], jump[2][mxN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m, k;
    cin >> n >> m >> k;

    iota(a, a + n, 0);
    move(a, a + n, jump[0]);

    for (int l, r; m--;) {
        cin >> l >> r;
        reverse(jump[0] + l - 1, jump[0] + r);
    }

    if (k & 1)
        for (int i = 0; i < n; ++i)
            a[i] = jump[0][a[i]];
    k >>= 1;

    for (int i = 1, j = 0; k; k >>= 1, i ^= 1, j ^= 1) {
        for (int k = 0; k < n; ++k)
            jump[i][k] = jump[j][jump[j][k]];
        if (k & 1)
            for (int k = 0; k < n; ++k)
                a[k] = jump[i][a[k]];
    }

    for (int i = 0; i < n; ++i)
        cout << a[i] + 1 << '\n';
}