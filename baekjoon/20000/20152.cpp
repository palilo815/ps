#include <bits/stdc++.h>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif
    int S, D;
    cin >> S >> D;

    if (S > D) swap(S, D);

    vector<int64_t> dp(D + 1, 1);

    for (int i = S + 1; i <= D; ++i)
        for (int j = i; j <= D; ++j)
            if (i != j)
                dp[j] += dp[j - 1];
    cout << dp[D];
}