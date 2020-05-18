#include <cstdio>
#include <cstring>
#define loop(i,n) for(int i=0;i<n;++i)

const int max_N = 50;

int N, M;
int mat[max_N][max_N];
int tmp[max_N][max_N];
int res[max_N][max_N];
int S[max_N];

void multiply(int x[][max_N], int y[][max_N]) {
    memset(tmp, 0, sizeof(tmp));
    loop(i, N) loop(k, N) loop(j, N) {
        tmp[i][j] += x[i][k] * y[k][j];
        tmp[i][j] %= M;
    }
    memcpy(x, tmp, sizeof(tmp));
}
int main() {
    int A, B, C, T;
START:;
    scanf("%d %d %d %d %d %d", &N, &M, &A, &B, &C, &T);
    if (!N) return 0;
    loop(i, N) scanf("%d", &S[i]);

    memset(res, 0, sizeof(res));
    loop(i, N) res[i][i] = 1;

    memset(mat, 0, sizeof(mat));
    loop(i, N) {
        if (i - 1 >= 0) mat[i][i - 1] = A;
        mat[i][i] = B;
        if (i + 1 < N) mat[i][i + 1] = C;
    }

    while (T) {
        if (T & 1) multiply(res, mat);
        multiply(mat, mat);
        T /= 2;
    }

    loop(i, N) {
        int ans = 0;
        loop(j, N) ans = (ans + res[i][j] * S[j]) % M;
        printf("%d ", ans);
    }
    putchar('\n');
    goto START;
    return 0;
}