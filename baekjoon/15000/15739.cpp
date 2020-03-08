#include <stdio.h>
#define loop(i,n) for(int i=0;i<n;++i)
const int max_N = 100;

int mat[max_N][max_N];
bool check[max_N * max_N + 1];

bool correct(int N) {
    loop(i, N) loop(j, N) {
        if (check[mat[i][j]]) return false;
        check[mat[i][j]] = true;
    }
    int sum = N * (N * N + 1) / 2, tmp;
    loop(i, N) {
        tmp = 0;
        loop(j, N) tmp += mat[i][j];
        if (tmp != sum) return false;
    }
    loop(j, N) {
        tmp = 0;
        loop(i, N) tmp += mat[i][j];
        if (tmp != sum) return false;
    }
    tmp = 0;
    loop(i, N) tmp += mat[i][i];
    if (tmp != sum) return false;
    tmp = 0;
    loop(i, N) tmp += mat[i][N - 1 - i];
    if (tmp != sum) return false;
    return true;
}
int main() {
    int N; scanf("%d", &N);
    loop(i, N) loop(j, N) scanf("%d", &mat[i][j]);
    printf("%s", correct(N) ? "TRUE" : "FALSE");
    return 0;
}