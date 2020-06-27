#include <cstdio>
#define loop(i,n) for(int i=0;i<n;++i)

const int M = 50;
const int mov[4][2] = { -1, 0, 0, -1, 0, 1, 1, 0};

int row, col;
bool mat[M][M];

void DFS(int r, int c) {
    mat[r][c] = 0;
    loop(i, 4) {
        int R = r + mov[i][0], C = c + mov[i][1];
        if (R < 0 || R >= row || C < 0 || C >= col || !mat[R][C]) continue;
        DFS(R, C);
    }
}
int main() {
    int T; scanf("%d", &T);
start:;
    int K; scanf("%d %d %d", &col, &row, &K);
    while (K--) {
        int c, r; scanf("%d %d", &c, &r);
        mat[r][c] = 1;
    }
    int ans = 0;
    loop(i, row) loop(j, col) if (mat[i][j]) {
        DFS(i, j);
        ++ans;
    }
    printf("%d\n", ans);
    if (--T) goto start;
    return 0;
}