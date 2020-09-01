#include <cstdio>
#include <cstring>
#define loop(i,n) for(int i=0;i<n;++i)

const int mxN = 34;

char mat[mxN][mxN + 1];
long long dp[mxN][mxN];

int main() {
    for (int N; scanf("%d", &N) && ~N; memset(dp, 0, sizeof(dp))) {
        dp[0][0] = 1;
        loop(i, N) scanf("%s", mat[i]);
        loop(i, N) loop(j, N) if (mat[i][j] ^ '0') {
            if (j + mat[i][j] - '0' < N) dp[i][j + mat[i][j] - '0'] += dp[i][j];
            if (i + mat[i][j] - '0' < N) dp[i + mat[i][j] - '0'][j] += dp[i][j];
        }
        printf("%lld\n", dp[N - 1][N - 1]);
    }
    return 0;
}