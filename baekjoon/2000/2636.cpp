#include <cstdio>
#define loop(i,n) for(int i=0;i<n;++i)

const int mov[4][2] = { -1,0,1,0,0,-1,0,1 };

int row, col;
int mat[100][100];

void DFS(int r, int c) {
    mat[r][c] = -1;
    loop(i, 4) {
        int R = r + mov[i][0], C = c + mov[i][1];
        if (R < 0 || R >= row || C < 0 || C >= col || mat[R][C]) continue;
        DFS(R, C);
    }
}
bool melt(int r, int c) {
    loop(i, 4) {
        int R = r + mov[i][0], C = c + mov[i][1];
        if (mat[R][C] == -1) return true;
    }
    return false;
}
int main() {
    int cheese = 0;
    scanf("%d %d", &row, &col);
    loop(i, row) loop(j, col) {
        scanf("%d", &mat[i][j]);
        if (mat[i][j]) ++cheese;
    }

    DFS(0, 0);
    // matrix 설명
    // 1 : 치즈  0 : 공기  -1 : "외부" 공기
    // 2 : 방금 전에 녹은 치즈

    int ans = 0, prev = 0;
    while (cheese) {
        loop(i, row) loop(j, col)
            if (mat[i][j] == 1 && melt(i, j))
                mat[i][j] = 2;
        prev = cheese;
        loop(i, row) loop(j, col)
            if (mat[i][j] == 2) {
                DFS(i, j);
                --cheese;
            }
        ++ans;
    }
    printf("%d\n%d", ans, prev);
    return 0;
}