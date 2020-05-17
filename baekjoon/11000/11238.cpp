#include <cstdio>
#define loop(i,n) for(int i=0;i<n;++i)
typedef long long ll;

const int mod = 1000000007;

ll A[2][2];
ll B[2][2];
ll res[2][2];

void multiply(ll x[][2], ll y[][2]) {
    B[0][0] = B[0][1] = B[1][0] = B[1][1] = 0;
    loop(i, 2) loop(k, 2) loop(j, 2) {
        B[i][j] += x[i][k] * y[k][j];
        B[i][j] %= mod;
    }
    x[0][0] = B[0][0], x[0][1] = B[0][1];
    x[1][0] = B[1][0], x[1][1] = B[1][1];
}
int main() {
    int T; scanf("%d", &T);
START:;
    ll n, m; scanf("%lld %lld", &n, &m);
    if (n > m) { ll tmp = n;n = m;m = tmp; }

    while (1) {
        ll r = m % n;
        if (!r) break;
        m = n, n = r;
    }

    res[0][0] = res[1][1] = 1;
    res[0][1] = res[1][0] = 0;

    A[0][0] = A[0][1] = A[1][0] = 1;
    A[1][1] = 0;

    while (n) {
        if (n & 1) multiply(res, A);
        multiply(A, A);
        n /= 2;
    }

    printf("%lld\n", res[0][1]);
    if (--T) goto START;
    return 0;
}