#include <stdio.h>
#define loop(i,n) for(int i=0;i<n;++i)
using namespace std;
const int MOD = 1000;
#define scanf scanf_s
int N;
void multiply(int A[][5], int B[][5])
{
    int C[5][5];
    loop(i, N) loop(j, N) {
        int x = 0;
        loop(a, N) x += A[i][a] * B[a][j];
        C[i][j] = x % MOD;
    }
    loop(i, 5) loop(j, 5) A[i][j] = C[i][j];
}
void power(int A[][5], long long p)
{
    if (p == 1) return;
    int tmp[5][5];
    loop(i, N) loop(j, N) tmp[i][j] = A[i][j];
    power(A, p / 2);
    multiply(A, A);
    if (p % 2 == 1) multiply(A, tmp);
}

int main()
{
    long long p;
    int A[5][5];
    scanf("%d %lld", &N, &p);
    loop(i, N) loop(j, N) scanf("%d", &A[i][j]);
    power(A, p);
    loop(i, N) {
        loop(j, N) printf("%d ", A[i][j] % MOD);
        putchar('\n');
    }
    return 0;
}