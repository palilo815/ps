#include <cstdio>
#define loop(i,n) for(int i=0;i<n;++i)

const int mov[8][2] = { -1,-1,-1,0,-1,1,0,-1,0,1,1,-1,1,0,1,1 };

int row, col;
int h[100][70];
bool v[100][70];

int DFS(int r, int c) {
    int ret = 1;
    v[r][c] = true;
    loop(i, 8) {
        int R = r + mov[i][0], C = c + mov[i][1];
        if (R < 0 || R >= row || C < 0 || C >= col || h[R][C] < h[r][c]) continue;
        if (h[R][C] > h[r][c]) ret = 0;
        else if (!v[R][C]) ret &= DFS(R, C);
    }
    return ret;
}
int main() {
    scanf("%d %d", &row, &col);
    loop(i, row) loop(j, col) scanf("%d", &h[i][j]);

    int ans = 0;
    loop(i, row) loop(j, col) if (!v[i][j])
        ans += DFS(i, j);
    printf("%d", ans);
    return 0;
}