#include <stdio.h>
#define loop(i,n) for(int i=0;i<n;++i)
int main()
{
    int row, col, Zr, Zc;
    scanf("%d %d %d %d", &row, &col, &Zr, &Zc);
    char news[50][50];

    loop(i, row) loop(j, col)
        scanf(" %c", &news[i][j]);

    loop(r, row) loop(i, Zr) {
        loop(c, col) loop(j, Zc)
            printf("%c", news[r][c]);
        putchar('\n');
    }
    return 0;
}