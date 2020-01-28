#include <stdio.h>

const int max_N = 1024;
int psum[max_N+1][max_N+1];
int main()
{
    int N, M; scanf("%d %d", &N, &M);
    int x;
    for (int i = 1;i <= N;++i) for (int j = 1;j <= N;++j) {
        scanf("%d", &x);
        psum[i][j] = x + psum[i - 1][j] + psum[i][j - 1] - psum[i - 1][j - 1];
    }
    int y1, x1, y2, x2;
    while (M--) {
        scanf("%d %d %d %d", &y1, &x1, &y2, &x2);
        printf("%d\n", psum[y2][x2] - psum[y2][x1 - 1] - psum[y1 - 1][x2] + psum[y1 - 1][x1 - 1]);
    }
    return 0;
}