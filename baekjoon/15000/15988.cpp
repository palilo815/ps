#include <bits/stdc++.h>
using namespace std;

const int mod = 1e9 + 9;
const int mxN = 1e6;

int dp[mxN + 4];

int main() {
    cin.tie(nullptr)->sync_with_stdio(false);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    dp[0] = 1;
    for (int i = 0; i < mxN; ++i)
        for (int j = i + 1; j < i + 4; ++j)
            dp[j] = (dp[j] + dp[i]) % mod;

    int t;
    cin >> t;
    for (int n; t--;) {
        cin >> n;
        cout << dp[n] << '\n';
    }
}