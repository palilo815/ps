#include <cstdio>
#include <cstring>
#define loop(i,n) for(int i=0;i<n;++i)
typedef long long ll;

const int mod = 100000007;
const int max_K = 11;
const size_t sz = sizeof(ll) * max_K * max_K;

ll A[max_K][max_K];
ll B[max_K][max_K];
ll res[max_K][max_K];

void multiply(ll x[][max_K], ll y[][max_K], int K) {
    memset(B, 0, sz);
    loop(i, K) loop(k, K) loop(j, K) {
        B[i][j] += x[i][k] * y[k][j];
        B[i][j] %= mod;
    }
    memcpy(x, B, sz);
}
int power(int N) {
    ll ret = 1, x = 2;
    while (N) {
        if (N & 1) ret = ret * x % mod;
        x = x * x % mod;
        N /= 2;
    }
    return ret;
}
int main() {
    int T; scanf("%d", &T);
    while (T--) {
        int K, N; scanf("%d %d", &K, &N);
        if (K == 0) {
            printf("%d\n", power(N));
            continue;
        }

        ++K;
        memset(res, 0, sz);
        loop(i, K) res[i][i] = 1;

        memset(A, 0, sz);
        A[0][0] = A[0][K - 1] = 1;
        loop(i, K - 1) A[i + 1][i] = 1;

        N -= K - 1;
        while (N > 0) {
            if (N & 1) multiply(res, A, K);
            multiply(A, A, K);
            N /= 2;
        }

        ll ans = 0;
        loop(i, K) ans = (ans + res[0][i]) % mod;
        printf("%lld\n", ans);
    }
    return 0;
}