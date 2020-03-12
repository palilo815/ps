#include <stdio.h>
#include <string.h>
#define loop(i,n) for(int i=0;i<n;++i)
typedef long long ll;

const int mod = 1000000007;
const int N = 8;

ll mat[N][N] = {
{0,1,0,1,0,0,0,0},
{1,0,1,1,0,0,0,0},
{0,1,0,1,1,1,0,0},
{1,1,1,0,0,1,0,0},
{0,0,1,0,0,1,1,0},
{0,0,1,1,1,0,0,1},
{0,0,0,0,1,0,0,1},
{0,0,0,0,0,1,1,0}
};

void multiply(ll A[][N], ll B[][N]) {
    ll tmp[N][N];
    loop(i, N) loop(j, N) {
        ll x = 0;
        loop(k, N) x += (A[i][k] * B[k][j]) % mod;
        tmp[i][j] = x % mod;
    }
    memcpy(A, tmp, sizeof(tmp));
}
void power(int D) {
    if (D == 1) return;
    ll tmp[N][N];
    memcpy(tmp, mat, sizeof(mat));
    power(D / 2);
    multiply(mat, mat);
    if (D % 2) multiply(mat, tmp);
}
int main() {
    int D; scanf("%d", &D);
    power(D);
    printf("%lld", mat[0][0]);
    return 0;
}