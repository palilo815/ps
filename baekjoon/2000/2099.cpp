#include <cstdio>
#include <cstring>
#define loop(i,n) for(int i=0;i<n;++i)
typedef long long ll;

const int M = 200;

int N;
bool A[M][M];
bool B[M][M];
bool res[M][M];

void multiply(bool x[][M], bool y[][M]) {
    memset(B, 0, sizeof(B));
    loop(i, N) loop(k, N) loop(j, N)
        B[i][j] |= x[i][k] & y[k][j];
    memcpy(x, B, sizeof(B));
}
int main() {
    int K, M; scanf("%d %d %d", &N, &K, &M);
    loop(i, N) {
        int a, b; scanf("%d %d", &a, &b);
        A[i][a - 1] = A[i][b - 1] = 1;
    }
    loop(i, N) res[i][i] = 1;

    while (K) {
        if (K & 1) multiply(res, A);
        multiply(A, A);
        K /= 2;
    }

    while (M--) {
        int u, v; scanf("%d %d", &u, &v);
        printf("%s\n", (res[u - 1][v - 1] ? "death" : "life"));
    }
    return 0;
}