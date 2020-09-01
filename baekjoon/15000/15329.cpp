#include <cstdio>

const int mxL = 100;

long long dp[mxL + 1];

int main() {
    int l, k; scanf("%d%d", &l, &k);
    dp[1] = dp[k] = 1;

    long long ans = 0;
    for (int i = 1; i <= l; ++i) {
        ans += dp[i];
        if (i + 2 <= l) dp[i + 2] += dp[i];
        if (i + k + 1 <= l) dp[i + k + 1] += dp[i];
    }

    printf("%lld", ans);
    return 0;
}