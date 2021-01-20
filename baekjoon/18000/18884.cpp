#include <bits/stdc++.h>
using namespace std;

const int mxN = 20;

char a[mxN][11], b[mxN][11];

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
    for (int i = 0; i < m; ++i)
        cin >> b[i];

    int q;
    cin >> q;

    for (int y; q--;) {
        cin >> y;
        cout << a[(y - 1) % n] << b[(y - 1) % m] << '\n';
    }
}