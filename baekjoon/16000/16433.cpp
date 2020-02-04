#include <stdio.h>
#define loop(i,n) for(int i=0;i<n;++i)

int main()
{
    int n, r, c;
    scanf("%d %d %d", &n, &r, &c);
    int pos = (r + c) % 2;
    loop(i, n) {
        loop(j, n) {
            if ((i + j) % 2 == pos) putchar('v');
            else putchar('.');
        }
        putchar('\n');
    }
    return 0;
}