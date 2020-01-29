#include <stdio.h>
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    int row, col;
    scanf("%d %d", &row, &col);
    int R, G, B, I;
    char x;
    loop(i, row){
        loop(j, col) {
            scanf("%d %d %d", &R, &G, &B);
            I = 2126 * R + 7152 * G + 722 * B;
            if (I < 510000) x = '#';
            else if (I < 1020000) x = 'o';
            else if (I < 1530000) x = '+';
            else if (I < 2040000) x = '-';
            else x = '.';
            putchar(x);
        }
        putchar('\n');
    }
    return 0;
}