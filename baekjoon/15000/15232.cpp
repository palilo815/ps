#include <stdio.h>
#define loop(i,n) for(int i=0;i<n;++i)

int main() {
    int row, col;
    scanf("%d %d", &row, &col);
    loop(i, row) {
        loop(j, col) putchar('*');
        putchar('\n');
    }
    return 0;
}