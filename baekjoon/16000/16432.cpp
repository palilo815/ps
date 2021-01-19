#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e3;

int dp[mxN + 1][9];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n;
    cin >> n;

    memset(dp[1], -1, sizeof(dp[0]) * n);
    for (int i = 0, m, x; i < n; ++i) {
        for (cin >> m; m--;) {
            cin >> x, --x;
            for (int j = 0; j < 9; ++j)
                if (j != x && ~dp[i][j]) {
                    dp[i + 1][x] = j;
                    break;
                }
        }
    }

    int x = find_if(dp[n], dp[n + 1], [&](auto& x) { return ~x; }) - dp[n];
    if (x == 9) return cout << -1, 0;

    vector<int> ans(n);
    for (int i = n; i; x = dp[i--][x])
        ans[i - 1] = x + 1;

    for (auto& x : ans)
        cout << x << '\n';
}