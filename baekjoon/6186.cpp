#include <stdio.h>
#define loop(i,n) for(int i=0;i<n;++i)

char M[100][100];
int row, col, mov[4][2] = { -1,0,1,0,0,-1,0,1 };
void DFS(int r, int c)
{
    M[r][c] = '.';
    loop(i, 4) {
        int R = r + mov[i][0], C = c + mov[i][1];
        if (R < 0 || R >= row || C < 0 || C >= col) continue;
        if (M[R][C] == '#')
            DFS(R, C);
    }
}
int main()
{
    scanf("%d %d", &row, &col);
    loop(i, row) {
        getchar();
        loop(j, col)
            scanf("%c", &M[i][j]);
    }

    int ans = 0;
    loop(i, row) loop(j, col)
        if (M[i][j] == '#') {
            DFS(i, j);
            ans++;
        }
    printf("%d", ans);
    return 0;
}