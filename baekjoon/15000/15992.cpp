#include <stdio.h>
#define loop(i,n) for(int i=0;i<n;++i)
#define scanf scanf_s

const int mod = 1000000009;
const int max_N = 1000;
const int max_M = 1000;

int DP[max_N + 3][max_M + 1];

int main() {
    DP[0][0] = 1;
    loop(m, max_M) loop(n, max_N)
        if (DP[n][m]) {
            DP[n + 1][m + 1] += DP[n][m], DP[n + 1][m + 1] %= mod;
            DP[n + 2][m + 1] += DP[n][m], DP[n + 2][m + 1] %= mod;
            DP[n + 3][m + 1] += DP[n][m], DP[n + 3][m + 1] %= mod;
        }
    int T; scanf("%d", &T);
    while (T--) {
        int n, m; scanf("%d %d", &n, &m);
        printf("%d\n", DP[n][m]);
    }
    return 0;
}