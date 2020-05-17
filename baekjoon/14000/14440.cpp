#include <cstdio>
#define loop(i,n) for(int i=0;i<n;++i)

const int mod = 100;

int A[2][2];
int B[2][2];
int res[2][2];

void multiply(int x[][2], int y[][2]) {
    B[0][0] = B[0][1] = B[1][0] = B[1][1] = 0;
    loop(i, 2) loop(k, 2) loop(j, 2) {
        B[i][j] += x[i][k] * y[k][j];
        B[i][j] %= mod;
    }
    x[0][0] = B[0][0], x[0][1] = B[0][1];
    x[1][0] = B[1][0], x[1][1] = B[1][1];
}
int main() {
    int x, y, a0, a1, n;
    scanf("%d %d %d %d %d", &x, &y, &a0, &a1, &n);

    res[0][0] = res[1][1] = 1;
    res[0][1] = res[1][0] = 0;

    A[0][0] = x, A[0][1] = y;
    A[1][0] = 1, A[1][1] = 0;

    --n;
    while (n > 0) {
        if (n & 1) multiply(res, A);
        multiply(A, A);
        n /= 2;
    }

    printf("%02d\n", (res[0][0] * a1 + res[0][1] * a0) % 100);
    return 0;
}