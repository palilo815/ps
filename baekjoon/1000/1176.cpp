#include <cstdio>
#define loop(i,n) for(int i=0;i<n;++i)
typedef long long ll;

const int M = 16;

int K;
ll DP[M][1 << M];
int h[M];

int hard(int i, int j) {
    int gap = h[i] - h[j];
    return gap > K || gap < -K;
}
int main() {
    int N; scanf("%d %d", &N, &K);
    loop(i, N) scanf("%d", &h[i]);
    loop(i, N) DP[i][1 << i] = 1;
    for (int n = 1; n < N; ++n) {
        int c = (1 << n) - 1, C = (1 << N) - 1;
        while (c <= C) {
            int mask = c;
            while (mask) {
                int j = mask & -mask;
                int i = __builtin_ctz(j);
                loop(k, N) if (!(c & (1 << k)) && hard(i, k))
                    DP[k][c | (1 << k)] += DP[i][c];
                mask -= j;
            }
            int t = c | (c - 1);
            c = (t + 1) | (((~t & -~t) - 1) >> (__builtin_ctz(c) + 1));
        }
    }

    ll ans = 0;
    loop(i, N) ans += DP[i][(1 << N) - 1];
    printf("%lld", ans);
    return 0;
}