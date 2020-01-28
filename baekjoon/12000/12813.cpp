#include <stdio.h>
#define loop(i,n) for(int i=0;i<n;++i)

const int len = 100000;
int A[len], B[len];
int main()
{
    loop(i, len) scanf("%1d", &A[i]);
    loop(i, len) scanf("%1d", &B[i]);

    loop(i, len) printf("%d", A[i] & B[i]);
    putchar('\n');
    loop(i, len) printf("%d", A[i] | B[i]);
    putchar('\n');
    loop(i, len) printf("%d", A[i] ^ B[i]);
    putchar('\n');
    loop(i, len) printf("%d", 1 - A[i]);
    putchar('\n');
    loop(i, len) printf("%d", 1 - B[i]);
    return 0;
}