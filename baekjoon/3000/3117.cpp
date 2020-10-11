#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e5;

int a[mxN], nxt[2][mxN + 1];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, K, M;
    cin >> N >> K >> M;
    --M;

    for (int i = 0; i < N; ++i)
        cin >> a[i];

    for (int i = 1; i <= K; ++i)
        cin >> nxt[0][i];

    if (M & 1)
        for (int i = 0; i < N; ++i)
            a[i] = nxt[0][a[i]];
    M >>= 1;

    for (int i = 1, j = 0; M; M >>= 1, i ^= 1, j ^= 1) {
        for (int k = 1; k <= K; ++k)
            nxt[i][k] = nxt[j][nxt[j][k]];
        if (M & 1)
            for (int k = 0; k < N; ++k)
                a[k] = nxt[i][a[k]];
    }

    for (int i = 0; i < N; ++i)
        cout << a[i] << ' ';
    return 0;
}