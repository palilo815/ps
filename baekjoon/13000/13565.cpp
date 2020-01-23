#include <stdio.h>
#define loop(i,n) for(int i=0;i<n;++i)

char M[1000][1000];
int row, col, mov[4][2] = { -1,0,1,0,0,-1,0,1 };
bool DFS(int r, int c)
{
    if (r == row - 1) return true;
    M[r][c] = '1';
    bool ret = false;
    loop(i, 4) {
        int R = r + mov[i][0], C = c + mov[i][1];
        if (R < 0 || R >= row || C < 0 || C >= col || M[R][C] == '1') continue;
        ret |= DFS(R, C);
    }
    return ret;
}
int main()
{
    scanf("%d %d", &row, &col);
    loop(i, row) {
        getchar();
        loop(j, col) scanf("%c", &M[i][j]);
    }

    bool ans = false;
    loop(j, col)
        if (M[0][j] == '0' && DFS(0, j)) {
            ans = true;
            break;
        }
    if (ans) printf("YES");
    else printf("NO");
    return 0;
}