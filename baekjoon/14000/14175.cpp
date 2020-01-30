#include <stdio.h>
#define loop(i,n) for(int i=0;i<n;++i)

char M[10][10];
int main()
{
    int row, col, k;
    scanf("%d %d %d", &row, &col, &k);
    getchar();
    loop(i, row) {
        loop(j, col) M[i][j] = getchar();
        getchar();
    }
    loop(i, row) loop(x, k) {
        loop(j, col) loop(y, k) putchar(M[i][j]);
        putchar('\n');
    }
    return 0;
}