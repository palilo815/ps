#include <stdio.h>
#define loop(i,n) for(int i=0;i<n;++i)

const int mod = 1000000009;
const int max_N = 100000;

int DP[max_N + 3][2];

int main() {
    DP[0][0] = 1;
    loop(i, max_N) for (int j = 1; j <= 3; ++j) {
        DP[i + j][1] = (DP[i + j][1] + DP[i][0]) % mod;
        DP[i + j][0] = (DP[i + j][0] + DP[i][1]) % mod;
    }

    int T; scanf("%d", &T);
    while (T--) {
        int N; scanf("%d", &N);
        printf("%d %d\n", DP[N][1], DP[N][0]);
    }
    return 0;
}