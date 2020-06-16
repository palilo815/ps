#include <cstdio>
#include <cstring>
#define loop(i,n) for(int i=0;i<n;++i)
using ll = long long;

const int mod = 1000000007;
const int N = 8;

ll A[N][N] = {
    {0, 1, 0, 1, 0, 0, 0, 0},
    {1, 0, 1, 1, 0, 0, 0, 0},
    {0, 1, 0, 1, 1, 1, 0, 0},
    {1, 1, 1, 0, 0, 1, 0, 0},
    {0, 0, 1, 0, 0, 1, 1, 0},
    {0, 0, 1, 1, 1, 0, 0, 1},
    {0, 0, 0, 0, 1, 0, 0, 1},
    {0, 0, 0, 0, 0, 1, 1, 0}
};
ll B[N][N], res[N][N];

void mul(ll x[][N], ll y[][N]) {
    memset(B, 0, sizeof(B));
    loop(i, N) loop(k, N) loop(j, N) {
        B[i][j] += x[i][k] * y[k][j];
        B[i][j] %= mod;
    }
    memmove(x, B, sizeof(B));
}
int main() {
    int D; scanf("%d", &D);
    loop(i, N) res[i][i] = 1;
    while (D) {
        if (D & 1) mul(res, A);
        mul(A, A);
        D /= 2;
    }
    printf("%lld", res[0][0]);
    return 0;
}