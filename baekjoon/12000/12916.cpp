#include <cstdio>
#include <cstring>
#define loop(i,n) for(int i=0;i<n;++i)
typedef long long ll;

const int M = 100;
const int mod = 1000000007;

int N;
ll A[M][M];
ll B[M][M];
ll res[M][M];

void multiply(ll x[][M], ll y[][M]) {
    memset(B, 0, sizeof(B));
    loop(i, N) loop(k, N) loop(j, N) {
        B[i][j] += x[i][k] * y[k][j];
        B[i][j] %= mod;
    }
    memcpy(x, B, sizeof(B));
}
int main() {
    int K; scanf("%d %d", &N, &K);
    loop(i, N) loop(j, N) scanf("%d", &A[i][j]);
    loop(i, N) res[i][i] = 1;

    while (K) {
        if (K & 1) multiply(res, A);
        multiply(A, A);
        K /= 2;
    }

    ll ans = 0;
    loop(i, N) loop(j, N) ans += res[i][j];
    printf("%lld", ans % mod);
    return 0;
}