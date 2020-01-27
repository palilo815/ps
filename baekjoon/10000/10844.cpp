#include <stdio.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define scanf scanf_s

const int MOD = 1000000000;
int DP[2][10];
int main()
{
    for (int i = 0;i < 10;++i)
        DP[0][i] = 1;
    int N; scanf("%d", &N);
    for (int i = 1; i < N; ++i) {
        int idx = i % 2;
        for (int j = 1;j < 9;++j)
            DP[idx][j] = (DP[1 - idx][j - 1] + DP[1 - idx][j + 1]) % MOD;
        DP[idx][0] = DP[1 - idx][1];
        DP[idx][9] = DP[1 - idx][8];
    }

    int idx = (N - 1) % 2, ans = 0;
    for (int i = 1;i < 10;++i)
        ans = (ans + DP[idx][i]) % MOD;
    printf("%d", ans);
    return 0;
}