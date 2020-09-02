#include <cstdio>

int main() {
    int N; scanf("%d", &N);
    int dp[31] = {1, 1};
    for (int i = 2; i <= N; ++i)
        dp[i] = dp[i - 2] * 2 + dp[i - 1];
    printf("%d", (dp[N] + dp[N / 2 + !(N & 1)]) / 2);
    return 0;
}