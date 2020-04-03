#include <cstdio>

const int max_N = 1000;
const int mod = 1234567;

int DP[max_N + 1][10];

int main() {
    for (int i = 0; i < 10; ++i)
        DP[1][i] = 1;
    for (int i = 2; i <= max_N; ++i) {
        DP[i][0] += DP[i - 1][7];
        DP[i][1] += DP[i - 1][2] + DP[i - 1][4];
        DP[i][2] += DP[i - 1][1] + DP[i - 1][3] + DP[i - 1][5];
        DP[i][3] += DP[i - 1][2] + DP[i - 1][6];
        DP[i][4] += DP[i - 1][1] + DP[i - 1][5] + DP[i - 1][7];
        DP[i][5] += DP[i - 1][2] + DP[i - 1][4] + DP[i - 1][6] + DP[i - 1][8];
        DP[i][6] += DP[i - 1][3] + DP[i - 1][5] + DP[i - 1][9];
        DP[i][7] += DP[i - 1][4] + DP[i - 1][8] + DP[i - 1][0];
        DP[i][8] += DP[i - 1][5] + DP[i - 1][7] + DP[i - 1][9];
        DP[i][9] += DP[i - 1][6] + DP[i - 1][8];
        for (int j = 0; j < 10; ++j)
            DP[i][j] %= mod;
    }
    int T; scanf("%d", &T);
    while (T--) {
        int N; scanf("%d", &N);
        int ans = 0;
        for (int i = 0; i < 10; ++i)
            ans += DP[N][i];
        printf("%d\n", ans % mod);
    }
    return 0;
}