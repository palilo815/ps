#include <bits/stdc++.h>
using namespace std;

const int mxN = 1e6 + 1;

char a[mxN], b[mxN];
int dp[mxN];

inline bool same(char x, char y) {
    if (x == 'i')
        return y == 'i' || y == 'j' || y == 'l';
    if (x == 'v')
        return y == 'v' || y == 'w';
    return x == y;
}
int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int n, m;
    cin >> n >> m >> a >> b;

    iota(dp + 1, dp + m + 1, 1);
    for (int i = 0; a[i]; ++i) {
        int pre = dp[0];
        dp[0] = i + 1;

        for (int j = 0; b[j]; ++j) {
            int cur = dp[j + 1];
            dp[j + 1] = same(a[i], b[j]) ? pre : pre = min({pre, dp[j], dp[j + 1]}) + 1;
            pre = cur;
        }
    }
    cout << dp[m];
}