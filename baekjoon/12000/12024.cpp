#include <stdio.h>
#define loop(i,n) for(int i=0;i<n;++i)
const int max_N = 250;

int A[max_N][max_N];
int B[max_N][max_N];

int main() {
    int N; scanf("%d", &N);
    loop(i, N) loop(j, N)
        scanf("%d", &A[i][j]);

    loop(i, N) loop(j, N) {
        int x = 0;
        loop(k, N) x += A[i][k] * A[k][j];
        B[i][j] = x;
    }

    long long ans = 0;
    loop(i, N) loop(j, N) if (i != j)
        ans += B[i][j] * (B[i][j] - 1);
    printf("%lld", ans);
    return 0;
}