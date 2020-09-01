#include <cstdio>

const int mxN = 1e4;

long long dp[mxN + 1];

int main() {
    int V, N; scanf("%d%d", &V, &N);
    dp[0] = 1;
    for (int c; V; --V) {
        scanf("%d", &c);
        for (int i = 0; i <= N - c; ++i)
            if (dp[i])
                dp[i + c] += dp[i];
    }
    printf("%lld", dp[N]);
    return 0;
}