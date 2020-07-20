#include <cstdio>
#define loop(i,n) for(int i=0;i<n;++i)
using ll = long long;

const int M = 15;

char a[M][51];
int len[M], num[M];
ll dp[1 << M][100];

ll _gcd(ll a, ll b) {
    if (a < b) return _gcd(b, a);
    if (a % b == 0) return b;
    return _gcd(b, a % b);
}
int main() {
    int N; scanf("%d", &N);
    loop(i, N) scanf("%s", a[i]);
    int K; scanf("%d", &K);

    loop(i, N) len[i] = 1;
    loop(i, N) for (int j = 0; a[i][j]; ++j) {
        num[i] = (num[i] * 10 + a[i][j] - '0') % K;
        len[i] = len[i] * 10 % K;
    }
    loop(i, N) dp[1 << i][num[i]] = 1;

    const int max_p = (1 << N) - 1;
    for (int c = 1, t; c < N; ++c)
        for (int p = (1 << c) - 1; p <= max_p; p = (t + 1) | (((~t & -~t) - 1) >> (__builtin_ctz(p) + 1))) {
            loop(k, K) if (dp[p][k])
                loop(i, N) if (!(p & (1 << i)))
                    dp[p | 1 << i][(k * len[i] + num[i]) % K] += dp[p][k];
            t = p | (p - 1);
        }

    if (!dp[(1 << N) - 1][0]) {puts("0/1"); return 0;}

    ll total = 1;
    for (int i = 1; i <= N; ++i)
        total *= i;
    ll g = _gcd(dp[(1 << N) - 1][0], total);
    printf("%lld/%lld", dp[(1 << N) - 1][0] / g, total / g);
    return 0;
}