#include <bits/stdc++.h>
using namespace std;

const int mxN = 100000;

int dp[17][mxN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N, M;
    cin >> N >> M;

    for (int i = 0; i < N; ++i)
        cin >> dp[0][i];

    int R = 32 - __builtin_clz(N);
    for (int i = 1, k = 1; i < R; ++i, k <<= 1)
        for (int j = 0; j + (k << 1) <= N; ++j)
            dp[i][j] = min(dp[i - 1][j], dp[i - 1][j + k]);

    for (int l, r, k; M--;) {
        cin >> l >> r;
        --l;
        k = 31 - __builtin_clz(r - l);
        cout << min(dp[k][l], dp[k][r - (1 << k)]) << '\n';
    }
    return 0;
}