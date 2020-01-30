#include <stdio.h>
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    char x[2] = { '*','.' };
    int row, col;
    scanf("%d %d", &row, &col);
    loop(i, row) {
        loop(j, col) putchar(x[(i + j) % 2]);
        putchar('\n');
    }
    return 0;
}