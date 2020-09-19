#include <bits/stdc++.h>
#define loop(i, n) for (int i = 0; i < n; ++i)
using namespace std;

const int mxN = 16;

int w[mxN][mxN], dp[1 << mxN][mxN];

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int N;
    cin >> N;
    loop(i, N) loop(j, N) cin >> w[i][j];

    memset(dp, 0x3f, sizeof(dp));
    dp[1][0] = 0;
    loop(mask, 1 << N) loop(u, N) if (mask & (1 << u))
        loop(v, N) if (!(mask & (1 << v)) && w[u][v])
            dp[mask | (1 << v)][v] = min(dp[mask | (1 << v)][v], dp[mask][u] + w[u][v]);

    int ans = INT_MAX;
    loop(i, N) if (w[i][0])
        ans = min(ans, dp[(1 << N) - 1][i] + w[i][0]);
    cout << ans;
    return 0;
}