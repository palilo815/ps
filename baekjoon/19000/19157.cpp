#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5;

int a[mxN + 1], b[mxN + 1];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, Q;
    cin >> N >> Q;

    for (int i = 1; i <= N; ++i)
        cin >> a[i];
    for (int i = 1; i <= N; ++i)
        cin >> b[i];

    partial_sum(a, a + N + 1, a, [&](int& a, int& b) {
        return a + (b & 1);
    });
    partial_sum(b, b + N + 1, b, [&](int& a, int& b) {
        return a + (b & 1);
    });

    for (int r1, c1, r2, c2; Q--;) {
        cin >> r1 >> c1 >> r2 >> c2;
        if (r1 > r2) swap(r1, r2);
        if (c1 > c2) swap(c1, c2);

        if (a[r1] - a[r1 - 1])
            cout << (a[r2] - a[r1 - 1] == r2 - r1 + 1 && b[c2] - b[c1 - 1] == c2 - c1 + 1 ? "YES\n" : "NO\n");
        else
            cout << (a[r2] - a[r1 - 1] || b[c2] - b[c1 - 1] ? "NO\n" : "YES\n");
    }
    return 0;
}