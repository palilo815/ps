#include <cstdio>

bool dp[1004];

int main() {
    int N; scanf("%d", &N);
    for (int i = 0; i < N; ++i)
        if (!dp[i])
            dp[i + 1] = dp[i + 3] = dp[i + 4] = true;
    puts(dp[N] ? "SK" : "CY");
    return 0;
}