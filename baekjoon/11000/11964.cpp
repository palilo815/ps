#include <cstdio>
#define min(a,b) (a<b?a:b)

const int mxT = 5e6;

bool dp[mxT + 2];

int main() {
    int T, A, B;
    scanf("%d%d%d", &T, &A, &B);

    dp[0] = true;
    for (int i = 0; i < T; ++i)
        if (dp[i]) {
            if (i + A <= T) dp[i + A] = true;
            if (i + B <= T) dp[i + B] = true;
        }

    int ans = 0;
    for (int i = 0, j = T; i <= T; i += 2)
        if (dp[i] | dp[i | 1]) {
            j = min(j, T - (i >> 1));
            while (!dp[j]) --j;
            if (j + (i >> 1) > ans)
                ans = j + (i >> 1);
        }
    printf("%d", ans);
    return 0;
}