#include <stdio.h>
#define loop(i,n) for(int i=0;i<n;++i)

char M[5][16];
int main()
{
    loop(i, 5)
        scanf("%s", &M[i]);
    loop(c, 15) loop(r, 5)
        if (M[r][c])
            putchar(M[r][c]);
    return 0;
}