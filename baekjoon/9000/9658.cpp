#include <cstdio>

bool dp[1004];

int main() {
#ifndef ONLINE_JUDGE
    freopen("in", "r", stdin);
    freopen("out", "w", stdout);
#endif

    int N;
    scanf("%d", &N);

    dp[0] = true;
    for (int i = 1; i < N; ++i)
        if (!dp[i])
            dp[i + 1] = dp[i + 3] = dp[i + 4] = true;
    puts(dp[N] ? "SK" : "CY");
    return 0;
}