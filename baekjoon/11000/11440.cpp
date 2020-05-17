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
ll fibo(ll p) {
    res[0][0] = res[1][1] = 1;
    res[0][1] = res[1][0] = 0;

    A[0][0] = A[0][1] = A[1][0] = 1;
    A[1][1] = 0;

    while (p) {
        if (p & 1) multiply(res, A);
        multiply(A, A);
        p /= 2;
    }
    return res[0][1];
}
int main() {
    ll n; scanf("%lld", &n);
    printf("%lld", fibo(n) * fibo(n + 1) % mod);
    return 0;
}