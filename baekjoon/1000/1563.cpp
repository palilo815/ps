#include <cstdio>
#define loop(i,n) for(int i=0;i<n;++i)

const int mod = 1e6;
const int max_N = 1000;

int DP[max_N + 1][2][3];

int main() {
    int N; scanf("%d", &N);
    DP[0][0][0] = 1;
    for (int i = 1; i <= N; ++i) {
        // normal
        loop(late, 2) loop(absent, 3)
            DP[i][late][0] += DP[i - 1][late][absent];
        // late
        loop(absent, 3)
            DP[i][1][0] += DP[i - 1][0][absent];
        // absent
        loop(late, 2) loop(absent, 2)
            DP[i][late][absent + 1] += DP[i - 1][late][absent];
        loop(j, 2) loop(k, 3) DP[i][j][k] %= mod;
    }
    int ans = 0;
    loop(i, 2) loop(j, 3)
        ans += DP[N][i][j];
    printf("%d", ans % mod);
    return 0;
}